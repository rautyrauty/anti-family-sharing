#include "anti-family-sharing.h"

void AntiFamilySharing::init(std::string steam_web_api_key)
{
    getInstanceImpl(&steam_web_api_key);
}

AntiFamilySharing& AntiFamilySharing::getInstance()
{
    return getInstanceImpl();
}

void AntiFamilySharing::PushPlayerToCheck(const PlayerInfo& p)
{
    m_to_check.push_back(p);
}

bool AntiFamilySharing::HavePlayerToKick() const
{
    return not( m_userid_to_kick.empty() );
}

std::string AntiFamilySharing::GetPlayerToKick()
{
    std::string r = std::move(m_userid_to_kick.front());
    m_userid_to_kick.pop_front();
    return r;
}


AntiFamilySharing::AntiFamilySharing(std::string* steam_web_api_key) :
    m_kSteamWebApiKey( steam_web_api_key ? move(*steam_web_api_key) : std::string{} )
{
    if (nullptr == steam_web_api_key) throw std::runtime_error{ "AntiFamilySharing not initialized" };

    std::thread([this]{
        while(true)
        {
            std::this_thread::sleep_for(std::chrono::microseconds(100));
            if (m_to_check.empty()) continue;

            if (IsUsingFamilySharing(m_to_check.front().steamid64))
            {

                m_userid_to_kick.push_back(m_to_check.front().userid);
            }

            m_to_check.pop_front();
        }

    }).detach();
}

AntiFamilySharing &AntiFamilySharing::getInstanceImpl(std::string *steam_web_api_key)
{
    static AntiFamilySharing instance(steam_web_api_key);
    return instance;
}

bool AntiFamilySharing::IsUsingFamilySharing(const std::string& steamid64)
{
    using namespace boost::beast;
    using namespace boost::asio;

    const std::string host = "api.steampowered.com";
    const std::string target = "/IPlayerService/GetOwnedGames/v1/?key=" + m_kSteamWebApiKey + "&steamid=" + steamid64 + "&include_appinfo=false&include_played_free_games=false&appids_filter=0";

    io_context ioc;

    ip::tcp::resolver resolver(ioc);
    ip::tcp::socket socket(ioc);

    connect(socket, resolver.resolve(host, "80"));

    http::request<http::string_body> req(http::verb::get, target, 11);
    req.set(http::field::host, host);
    req.set(http::field::user_agent, BOOST_BEAST_VERSION_STRING);
    req.set(boost::beast::http::field::content_type, "application/json");

    http::write(socket, req);
    nlohmann::json responseJson;

    {
        boost::beast::flat_buffer buffer;
        http::response<http::string_body> res;
        http::read(socket, buffer, res);

        responseJson = nlohmann::json::parse(res.body());
    }
    socket.shutdown(boost::asio::ip::tcp::socket::shutdown_both);
    nlohmann::json object = responseJson["response"]["games"];
    int game_count = responseJson["response"]["game_count"];
    for(int i = 0; i < game_count; i+=1)
    {
        if (object[i]["appid"] == 4000) return false;
    }
    return true;
}
