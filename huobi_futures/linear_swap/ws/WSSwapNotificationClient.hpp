#pragma once
#include <string>
using std::string;

#include <list>
using std::list;

#include <vector>
using std::vector;

#include <algorithm>

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

#include <future>

// V5 推送回调：收到 notify 帧时回调，参数为明文 JSON 字符串
typedef std::function<void(const string &)> _v5_notify_fun;

namespace huobi_futures
{
    namespace linear_swap
    {
        namespace ws
        {
            // V5 合约订单/资产/持仓推送客户端
            // 地址 wss://api.hbdm.com/ws/v5/notification，7 个 topic：orders/trade/trade_detail/positions/account/match_orders/algo_orders
            // 推送为明文文本帧（非 gzip），鉴权 ack/sub ack 也为文本帧；市场类帧为 gzip。
            class WSSwapNotificationClient
            {
            public:
                WSSwapNotificationClient(const string &access_key, const string &secret_key,
                                         const string &host = utils::DEFAULT_HOST)
                {
                    this->host = host;
                    this->path = utils::V5_WS_NOTIFICATION_PATH;
                    this->ak = access_key;
                    this->sk = secret_key;
                    can_work = false;
                    authed = false;
                }

                ~WSSwapNotificationClient()
                {
                    Disconnect();
                }

                // 连接并鉴权，鉴权成功后可 Sub
                bool Connect()
                {
                    p_ws = new WebSocket();
                    p_ws->OnOpen = std::bind(&WSSwapNotificationClient::WsOnOpen, this);
                    p_ws->OnClose = std::bind(&WSSwapNotificationClient::WsOnClose, this);
                    p_ws->OnMsg = std::bind(&WSSwapNotificationClient::WsOnMsg, this, std::placeholders::_1, std::placeholders::_2);

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
                    run_thread = std::move(t1);
                    return true;
                }

                // 订阅 topic，鉴权成功后发送。topic 例：orders / trade / positions 等
                // V5 推送 sub 帧：{"op":"sub","topic":"orders","contract_code":"SPX500-USDT"}（对齐 Java doSub）
                bool Sub(const vector<string> &topics, const string &contract_code, _v5_notify_fun fun)
                {
                    while (!can_work)
                    {
                        std::this_thread::sleep_for(std::chrono::milliseconds(10));
                    }

                    for (auto &topic : topics)
                    {
                        sub_map_call_fun[topic] = fun;
                        stringstream ss;
                        ss << "{\"op\":\"sub\",\"topic\":\"" << topic << "\"";
                        if (!contract_code.empty())
                        {
                            ss << ",\"contract_code\":\"" << contract_code << "\"";
                        }
                        ss << "}";
                        p_ws->SendMsg(ss.str());
                        LOG(INFO) << "send:" << ss.str();
                    }
                    return true;
                }

                bool Unsub(const vector<string> &topics, const string &contract_code = "")
                {
                    while (!can_work)
                    {
                        std::this_thread::sleep_for(std::chrono::milliseconds(10));
                    }

                    for (auto &topic : topics)
                    {
                        stringstream ss;
                        ss << "{\"op\":\"unsub\",\"topic\":\"" << topic << "\"";
                        if (!contract_code.empty())
                        {
                            ss << ",\"contract_code\":\"" << contract_code << "\"";
                        }
                        ss << "}";
                        p_ws->SendMsg(ss.str());
                        LOG(INFO) << "send:" << ss.str();
                        sub_map_call_fun.erase(topic);
                    }
                    return true;
                }

                void Disconnect()
                {
                    if (p_ws == NULL)
                    {
                        return;
                    }
                    p_ws->Stop();
                    if (run_thread.joinable())
                    {
                        run_thread.join();
                    }
                    delete p_ws;
                    p_ws = NULL;
                }

            private:
                void WsOnOpen()
                {
                    LOG(INFO) << "V5 notification WebSocket opened";
                    can_work = true;
                    if (ak == "" || sk == "")
                    {
                        return;
                    }
                    AddAuth();
                }

                void WsOnClose()
                {
                    LOG(INFO) << "V5 notification WebSocket close.";
                    can_work = false;
                    authed = false;
                }

                // V5 帧分发：先判断 gzip magic（0x1f 0x8b），gzip 帧解压，文本帧直用
                void WsOnMsg(const char *data, int len)
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
                            LOG(ERROR) << "V5 gzip decompress failed, ret=" << ret;
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
                        LOG(ERROR) << "V5 parse json failed:" << plaintext;
                        return;
                    }

                    if (!jdata.contains("op"))
                    {
                        return;
                    }
                    string op = jdata["op"].get<string>();

                    if (op == "ping")
                    {
                        // V5 心跳：回 pong 带 ts
                        nlohmann::json pong;
                        pong["op"] = "pong";
                        if (jdata.contains("ts"))
                        {
                            pong["ts"] = jdata["ts"];
                        }
                        p_ws->SendMsg(pong.dump());
                    }
                    else if (op == "auth")
                    {
                        LOG(INFO) << "recv auth:" << plaintext;
                        if (jdata.contains("err-code") && jdata["err-code"].get<int>() == 0)
                        {
                            authed = true;
                        }
                        else
                        {
                            LOG(ERROR) << "V5 auth failed:" << plaintext;
                            Disconnect();
                        }
                        // auth ack 也按 topic 路由交 callback（测试用于判断鉴权就绪）
                        for (auto &kv : sub_map_call_fun)
                        {
                            if (kv.second) kv.second(plaintext);
                        }
                    }
                    else if (op == "notify")
                    {
                        // 推送数据帧，按 topic 路由回调
                        string topic = jdata.contains("topic") ? jdata["topic"].get<string>() : "";
                        _v5_notify_fun fun = NULL;
                        if (sub_map_call_fun.find(topic) != sub_map_call_fun.end())
                        {
                            fun = sub_map_call_fun[topic];
                        }
                        if (fun == NULL)
                        {
                            LOG(ERROR) << "no callback for topic:" << topic << " data:" << plaintext;
                            return;
                        }
                        fun(plaintext);
                    }
                    else if (op == "sub" || op == "unsub")
                    {
                        LOG(INFO) << "recv " << op << ":" << plaintext;
                        // sub/unsub ack 按 topic 路由交 callback（测试用于判断订阅就绪）
                        string topic = jdata.contains("topic") ? jdata["topic"].get<string>() : "";
                        auto it = sub_map_call_fun.find(topic);
                        if (it != sub_map_call_fun.end() && it->second)
                        {
                            it->second(plaintext);
                        }
                    }
                    else if (op == "pong")
                    {
                        // pong 应答，忽略
                    }
                    else
                    {
                        LOG(INFO) << "V5 notification unknown op:" << plaintext;
                    }
                }

                // V5 鉴权：签 GET\nhost\npath\n鉴权4参数，然后 {op:auth, type:api, AccessKeyId, SignatureMethod, SignatureVersion, Timestamp, Signature}
                // 注：参数值必须 URL 编码（特别是时间戳的冒号 ':' → '%3A'），对参数按 ASCII 排序
                void AddAuth()
                {
                    time_t now;
                    time(&now);
                    char pchar_time[sizeof "2011-10-08T07:07:09"];
                    strftime(pchar_time, sizeof pchar_time, "%FT%T", gmtime(&now));

                    // 构建参数并按 ASCII 排序（C++ map 默认按 key 排序）
                    map<string, string> params;
                    params["AccessKeyId"] = ak;
                    params["SignatureMethod"] = "HmacSHA256";
                    params["SignatureVersion"] = "2";
                    params["Timestamp"] = string(pchar_time);

                    // 按排序顺序构建参数字符串，每个值 URL 编码
                    stringstream para;
                    bool first = true;
                    for (auto &p : params) {
                        if (!first) para << "&";
                        para << p.first << "=" << HttpRequest::Instance().UrlEncode(p.second);
                        first = false;
                    }

                    // host 需转小写（参考 Java ApiSignature）
                    string hostLower = host;
                    std::transform(hostLower.begin(), hostLower.end(), hostLower.begin(), ::tolower);

                    string signature = utils::Signer::CreateSignature("GET", hostLower, path, para.str(), sk);

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
                std::thread run_thread;
                string ak;
                string sk;

                bool can_work;
                bool authed;

                mutex mtx;
                map<string, _v5_notify_fun> sub_map_call_fun;
            };
        } // namespace ws
    }     // namespace linear_swap
} // namespace huobi_futures