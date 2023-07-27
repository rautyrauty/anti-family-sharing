require("AntiFamilySharing")
hook.Add(
    "PlayerAuthed", 
    "CheckFamilySharing", 
    function(ply)
        LuaAntiFamilySharing(ply:SteamID64(),ply:UserID())
    end
    )