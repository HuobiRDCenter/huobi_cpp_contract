#pragma once
#include <string>
using std::string;

#include <list>
using std::list;

#include <vector>
using std::vector;

#include "huobi_futures/wsbase/WebSocket.hpp"
typedef huobi_futures::wsbase::WebSocket WebSocket;

#include "huobi_futures/url_base/HttpRequest.hpp"
typedef huobi_futures::url_base::HttpRequest HttpRequest;

#include "huobi_futures/utils/const_val.hpp"

#include <sstream>
using std::stringstream;

#include "huobi_futures/utils/Signer.hpp"
#include "huobi_futures/utils/gzip.hpp"

#include "huobi_futures/nlohmann_json/json.hpp"

#include <ctime>
#include <thread>
#include <chrono>
#include <mutex>
using std::mutex;

#include <map>
using std::map;
using std::pair;

#include <atomic>
using std::atomic;

// V5 交易回调：收到应答帧（非 ping）时回调，参数为明文 JSON 字符串
// 应答帧无 op 字段时也回调，caller 用应答里的 cid 关联请求
typedef std::function<void(const string &)> _v5_trade_fun;

namespace huobi_futures
{
    namespace linear_swap
    {
        namespace ws
        {
            // V5 合约 WebSocket 交易客户端（下单/撤单）
            // 地址 wss://api.hbdm.com/linear-swap-trade，5 个 op：place_order/place_batch_orders/cancel_order/cancel_batch_orders/cancel_all_orders
            // 请求帧 {op, cid, data}，应答帧靠 cid 关联（无 op 字段），鉴权与回报均为明文文本帧
            class WSSwapTradeClient
            {
            public:
                WSSwapTradeClient(const string &access_key, const string &secret_key,
                                  const string &host = utils::DEFAULT_HOST)
                {
                    this->host = host;
                    this->path = utils::V5_WS_TRADE_PATH;
                    this->ak = access_key;
                    this->sk = secret_key;
                    can_work = false;
                    authed = false;
                    cid_seq = 0;
                }

                ~WSSwapTradeClient()
                {
                    Disconnect();
                }

                // 连接并鉴权。callback 接收所有非 ping 应答帧
                bool Connect(_v5_trade_fun callback)
                {
                    p_ws = new WebSocket();
                    p_ws->OnOpen = std::bind(&WSSwapTradeClient::WsOnOpen, this);
                    p_ws->OnClose = std::bind(&WSSwapTradeClient::WsOnClose, this);
                    p_ws->OnMsg = std::bind(&WSSwapTradeClient::WsOnMsg, this, std::placeholders::_1, std::placeholders::_2, callback);

                    stringstream str_buf;
                    str_buf << "wss://" << host << path;
                    string url = str_buf.str();
                    LOG(INFO) << url;
                    bool con_ok = p_ws->Connect(url);
                    if (!con_ok)
                    {
                        return false;
                    }
                    std::thread t1([&] { p_ws->RunForever(); });
                    t1.detach();
                    return true;
                }

                // 5 个 op：data 为 JSON 对象字符串，place_batch_orders 为数组字符串
                string PlaceOrder(const string &data)
                {
                    return SendOp("place_order", data);
                }

                string PlaceBatchOrders(const string &data)
                {
                    return SendOp("place_batch_orders", data);
                }

                string CancelOrder(const string &data)
                {
                    return SendOp("cancel_order", data);
                }

                string CancelBatchOrders(const string &data)
                {
                    return SendOp("cancel_batch_orders", data);
                }

                string CancelAllOrders(const string &data)
                {
                    return SendOp("cancel_all_orders", data);
                }

                void Disconnect()
                {
                    if (p_ws == NULL)
                    {
                        return;
                    }
                    delete p_ws;
                    p_ws = NULL;
                }

            private:
                // 发送 op 帧，返回本次 cid 供 caller 关联应答
                string SendOp(const string &op, const string &data)
                {
                    if (!can_work || !authed)
                    {
                        LOG(ERROR) << "ws not ready, op:" << op;
                        return "";
                    }
                    string cid = std::to_string(cid_seq.fetch_add(1) + 1);
                    // data 已是 JSON 字符串（对象或数组），直接拼入
                    stringstream ss;
                    ss << "{\"op\":\"" << op << "\",\"cid\":\"" << cid << "\",\"data\":" << data << "}";
                    p_ws->SendMsg(ss.str());
                    LOG(INFO) << "send:" << ss.str();
                    return cid;
                }

                void WsOnOpen()
                {
                    LOG(INFO) << "V5 trade WebSocket opened";
                    can_work = true;
                    if (ak == "" || sk == "")
                    {
                        return;
                    }
                    AddAuth();
                }

                void WsOnClose()
                {
                    LOG(INFO) << "V5 trade WebSocket close.";
                    can_work = false;
                    authed = false;
                }

                // V5 trade 帧分发：先判断 gzip magic，文本帧直用；ping 回 pong，其余全交 callback
                void WsOnMsg(const char *data, int len, _v5_trade_fun callback)
                {
                    string plaintext;
                    if (len >= 2 && (unsigned char)data[0] == 0x1f && (unsigned char)data[1] == 0x8b)
                    {
                        char buf[utils::WS_RECV_BUF_SIZE] = {0};
                        int ret = utils::DecompressString(data, len, buf, utils::WS_RECV_BUF_SIZE);
                        if (ret > 0)
                        {
                            plaintext = string(buf);
                        }
                        else
                        {
                            LOG(ERROR) << "V5 trade gzip decompress failed, ret=" << ret;
                            return;
                        }
                    }
                    else
                    {
                        plaintext = string(data, len);
                    }

                    nlohmann::json jdata;
                    try
                    {
                        jdata = nlohmann::json::parse(plaintext);
                    }
                    catch (...)
                    {
                        LOG(ERROR) << "V5 trade parse json failed:" << plaintext;
                        return;
                    }

                    if (jdata.contains("op") && jdata["op"].get<string>() == "ping")
                    {
                        nlohmann::json pong;
                        pong["op"] = "pong";
                        if (jdata.contains("ts"))
                        {
                            pong["ts"] = jdata["ts"];
                        }
                        p_ws->SendMsg(pong.dump());
                        return;
                    }

                    // 其余帧（auth ack / 应答 / notify）全交 callback，caller 用 cid 关联
                    if (jdata.contains("op") && jdata["op"].get<string>() == "auth")
                    {
                        LOG(INFO) << "recv auth:" << plaintext;
                        if (jdata.contains("err-code") && jdata["err-code"].get<int>() == 0)
                        {
                            authed = true;
                        }
                        else
                        {
                            LOG(ERROR) << "V5 trade auth failed:" << plaintext;
                            Disconnect();
                        }
                        return;
                    }

                    if (callback)
                    {
                        callback(plaintext);
                    }
                }

                void AddAuth()
                {
                    time_t now;
                    time(&now);
                    char pchar_time[sizeof "2011-10-08T07:07:09"];
                    strftime(pchar_time, sizeof pchar_time, "%FT%T", gmtime(&now));

                    stringstream para;
                    para << "AccessKeyId=" << ak << "&SignatureMethod=HmacSHA256&SignatureVersion=2&Timestamp=" << HttpRequest::Instance().UrlEncode(pchar_time);

                    string signature = utils::Signer::CreateSignature("GET", host, path, para.str(), sk);

                    nlohmann::json auth;
                    auth["op"] = "auth";
                    auth["type"] = "api";
                    auth["AccessKeyId"] = ak;
                    auth["SignatureMethod"] = "HmacSHA256";
                    auth["SignatureVersion"] = "2";
                    auth["Timestamp"] = string(pchar_time);
                    auth["Signature"] = signature;
                    p_ws->SendMsg(auth.dump());
                    LOG(INFO) << "send auth:" << auth.dump();
                }

                string host;
                string path;
                WebSocket *p_ws = NULL;
                string ak;
                string sk;

                bool can_work;
                bool authed;
                atomic<long> cid_seq;

                mutex mtx;
            };
        } // namespace ws
    }     // namespace linear_swap
} // namespace huobi_futures