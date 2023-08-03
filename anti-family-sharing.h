#ifndef AFS_H
#define AFS_H

#include <deque>
#include <thread>
#include <string>
#include <stdexcept>

#include <boost/asio.hpp>
#include <boost/asio/ssl.hpp>
#include <boost/beast.hpp>

#include "json.hpp"

class AntiFamilySharing
{
public:
    struct PlayerInfo
    {
        std::string userid;
        std::string steamid64;
    };

    static void init(std::string steam_web_api_key);
    static AntiFamilySharing& getInstance();

    AntiFamilySharing(const AntiFamilySharing&) = delete;
    void operator = (const AntiFamilySharing&) = delete;

    void PushPlayerToCheck(const PlayerInfo&);
    bool HavePlayerToKick() const;;
    std::string GetPlayerToKick();

    std::deque<std::string> m_messages;

private:
    AntiFamilySharing(std::string* steam_web_api_key);
    static AntiFamilySharing& getInstanceImpl(std::string* steam_web_api_key = nullptr);

    bool IsUsingFamilySharing(const std::string& steamid64);

    std::deque<std::string> m_userid_to_kick;
    std::deque<PlayerInfo> m_to_check;

    const std::string m_kSteamWebApiKey;
};

#endif // AFS_H
