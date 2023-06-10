local webApiKey = "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX"

local function CheckFamilySharing(ply)
	http.Fetch
    (
        string.format(
            "https://partner.steam-api.com/ISteamUser/CheckAppOwnership/v2/?key=%s&steamid=%s&appid=4000",
            webApiKey,
            ply:SteamID64()
        ),

        function(body)
            if (not util.JSONToTable(body).permanent) then
                ply:Kick("You kicked by AntiFamilySharing")
            end
        end,

        function(code)
            error(string.format("FamilySharing: Failed API call for %s | %s (Error: %s)\n", ply:Nick(), ply:SteamID(), code))
        end
	)
end
hook.Add("PlayerAuthed", "CheckFamilySharing", CheckFamilySharing)
