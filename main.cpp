#include "GarrysMod/Lua/Interface.h"
#include "ini.h"
#include "anti-family-sharing.h"


LUA_FUNCTION(EmptyFunc)
{
    return 0;
}

LUA_FUNCTION(AFSCheckStart)
{
    AntiFamilySharing::PlayerInfo to_check;

    LUA->PushSpecial(GarrysMod::Lua::SPECIAL_GLOB);

        LUA->GetField(1, "SteamID64");
        LUA->Push( 1 );
        LUA->Call(1, 1);
    to_check.steamid64 = LUA->GetString(-1);

        LUA->GetField(1, "UserID");
        LUA->Push( 1 );
        LUA->Call(1, 1);
    to_check.userid    = LUA->GetString(-1);

        LUA->GetField(-3, "print");
        LUA->PushString(to_check.steamid64.c_str());
        LUA->PushString(to_check.userid.c_str());
        LUA->Call(2, 0);

    LUA->Pop();

    AntiFamilySharing::getInstance().PushPlayerToCheck(to_check);

    return 0;
}

LUA_FUNCTION(KickSharedPlayers)
{
    LUA->PushSpecial(GarrysMod::Lua::SPECIAL_GLOB);
    if(AntiFamilySharing::getInstance().HavePlayerToKick())
    {
        LUA->GetField(-1, "print");
        LUA->PushString("to_check.steamid64.c_str())");
        LUA->Call(1, 0);
        LUA->GetField(-1, "game");

        while(AntiFamilySharing::getInstance().HavePlayerToKick())
        {
            LUA->GetField(-1, "KickID");
            LUA->PushString(AntiFamilySharing::getInstance().GetPlayerToKick().c_str());
            LUA->PushString("Anti Family Sharing kick response");
            LUA->Call(2, 0);
        }

        LUA->Pop();
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

        LUA->GetField(-1, "hook");

            LUA->GetField(-1, "Add");
            LUA->PushString("Think");
            LUA->PushString("KickSharedPlayers");
            LUA->PushCFunction( KickSharedPlayers );
            LUA->Call(3, 0);


            LUA->GetField(-1, "Add");
            LUA->PushString("PlayerAuthed");
            LUA->PushString("AFSCheckStart");
            LUA->PushCFunction( AFSCheckStart );
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
