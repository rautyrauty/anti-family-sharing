#ifndef AFS_H
#define AFS_H

#include <string>
#include <stdexcept>

#include <boost/asio.hpp>
#include <boost/asio/ssl.hpp>
#include <boost/beast.hpp>

#include "json.hpp"

class AntiFamilySharing
{
public:
    static void init(std::string steam_web_api_key)
    {
      getInstanceImpl(&steam_web_api_key);
    }

private:
    static AntiFamilySharing& getInstanceImpl(std::string* steam_web_api_key = nullptr)
    {
        static AntiFamilySharing instance{ steam_web_api_key };
        return instance;
    }

public:
    AntiFamilySharing(std::string* steam_web_api_key) :
        m_kSteamWebApiKey{ steam_web_api_key ? move(*steam_web_api_key) : std::string{} }
    {
        if (nullptr == steam_web_api_key) throw std::runtime_error{ "Questionnary not initialized" };
    }

    static AntiFamilySharing& getInstance()
    {
        return getInstanceImpl();
    }

    AntiFamilySharing(const AntiFamilySharing&) = delete;
    void operator = (const AntiFamilySharing&) = delete;

    // in cpp
    bool IsUsingFamilySharing(const std::string& steamid64);

private:
    const std::string m_kSteamWebApiKey;
};

#endif // AFS_H
