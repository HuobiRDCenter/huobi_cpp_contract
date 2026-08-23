#include <string>
using std::string;

#include <cstdlib>
using std::getenv;

#include <map>
using std::map;
using std::pair;

map<string, string> config;

// V5 key 从环境变量读取（HTX_ACCESS_KEY / HTX_SECRET_KEY），
// key 只放 /tmp/htx_keys.env（仓库外），代码零明文。
// 缺失时回退占位值，让无 key 也能编译跑只读/公开测试。
void init_config()
{
    config.insert(pair<string, string>("Host", "api.hbdm.com"));

    const char *ak = getenv("HTX_ACCESS_KEY");
    const char *sk = getenv("HTX_SECRET_KEY");
    config.insert(pair<string, string>("AccessKey", ak ? ak : "x-x-x-x"));
    config.insert(pair<string, string>("SecretKey", sk ? sk : "x-x-x-x"));

    const char *aid = getenv("HTX_ACCOUNT_ID");
    config.insert(pair<string, string>("AccountId", aid ? aid : "xxxxxxxx"));

    const char *sub = getenv("HTX_SUB_UID");
    config.insert(pair<string, string>("SubUid", sub ? sub : "xxxxxxxx"));
}