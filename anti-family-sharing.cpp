#include "anti-family-sharing.h"

bool AntiFamilySharing::IsUsingFamilySharing(const std::string& steamid64)
{
    using namespace boost::beast;
    using namespace boost::asio;

    const std::string host = "api.steampowered.com";//https://api.steampowered.com/IPlayerService/GetOwnedGames/v1/?key=152BF4894662E499CAC9490922325590&steamid=76561199439175858&include_appinfo=false&include_played_free_games=false&appids_filter=0
    const std::string target = "/IPlayerService/GetOwnedGames/v1/?key=" + m_kSteamWebApiKey + "&steamid=" + steamid64 + "&include_appinfo=false&include_played_free_games=false&appids_filter=0";

    io_context ioc;

    ip::tcp::resolver resolver(ioc);
    ip::tcp::socket socket(ioc);

    connect(socket, resolver.resolve(host, "80"));

    http::request<http::string_body> req(http::verb::get, target, 11);
    req.set(http::field::host, host);
    req.set(http::field::user_agent, BOOST_BEAST_VERSION_STRING);

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
