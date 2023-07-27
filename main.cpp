#include <deque>
#include <thread>

#include "GarrysMod/Lua/Interface.h"
#include "ini.h"
#include "anti-family-sharing.h"

std::deque<std::string> userid_to_kick;

LUA_FUNCTION(EmptyFunc)
{
    return 0;
}

LUA_FUNCTION(LuaAntiFamilySharing)
{
    std::string steamid64 = LUA->GetString(1);
    std::string userid   = LUA->GetString(2);
    std::thread([steamid64,userid](){
        if(AntiFamilySharing::getInstance().IsUsingFamilySharing(steamid64)) userid_to_kick.push_back(userid);
    }).detach();
    return 0;
}

LUA_FUNCTION(KickFamilySharingUsers)
{
    if(not userid_to_kick.empty())
    {
        LUA->PushSpecial(GarrysMod::Lua::SPECIAL_GLOB); // Fetch the global table
        LUA->GetField(-1, "game");

        while(not userid_to_kick.empty())
        {
            LUA->GetField(-1, "KickID");
            LUA->PushString(userid_to_kick.front().c_str());
            LUA->PushString("Anti Family Sharing kick response");
            LUA->Call(2, 0);
            userid_to_kick.pop_front();
        }

        LUA->Pop(); // Pop global table
    }


    return 0;
}

GMOD_MODULE_OPEN()
{
    LUA->PushSpecial( GarrysMod::Lua::SPECIAL_GLOB );

    mINI::INIFile file("AntiFamilySharing.ini");
    mINI::INIStructure ini;

    if( file.read(ini) and not(std::string(ini["options"]["web_steam_api_key"]).empty()) )
    {
        LUA->GetField(-1, "print");
        LUA->PushString("Binary module Anti Family Sharing is running");
        LUA->Call(1, 0);

        LUA->PushCFunction( LuaAntiFamilySharing );
        LUA->SetField( -2, "LuaAntiFamilySharing" );

        LUA->GetField(-1, "hook");
        LUA->GetField(-1, "Add");
        LUA->PushString("Think");
        LUA->PushString("KickFamilySharingUsers");
        LUA->PushCFunction( KickFamilySharingUsers );
        LUA->Call(3, 0);

        AntiFamilySharing::init(ini["options"]["web_steam_api_key"]);
    }
    else
    {
        ini["options"]["web_steam_api_key"] = "";
        file.generate(ini);
        LUA->GetField(-1, "print");
        LUA->PushString("The Anti Family Sharing binary module is not running. Enter web steam api key in the AntiFamilySharing.ini file");
        LUA->Call(1, 0);
        LUA->PushCFunction( EmptyFunc );
        LUA->SetField( -2, "LuaAntiFamilySharing" );
    }
    LUA->Pop();

    return 0;
}


GMOD_MODULE_CLOSE()
{
    return 0;
}
