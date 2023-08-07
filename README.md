# Multithreaded Anti Family Sharing

A cross-platform dynamic library or a binary module for Garry's Mod game servers that provides protection from family sharing.

Family Sharing is a steam feature that allows you to distribute your game to other accounts. The person was denied access to the server, he creates a new account, distributes the game and logs on to the server. To find out whether the player is the true owner of the game is possible only with the help of the web steam api. There were already Lua solutions, but they all had one problem - single-threaded processing.

## Installation

1. Install [gmod_require](https://github.com/danielga/gmod_require) (to save your nerves):
Download https://github.com/danielga/gmod_require/releases/tag/v1 and move it to /garrysmod/lua/bin/
Download https://github.com/danielga/gmod_require/tree/master/includes/modules (both) and move them to /garrysmod/lua/includes/modules
2. Install [OpenSSL](https://www.openssl.org/)
For Windows:
Download https://slproweb.com/products/Win32OpenSSL.html and move libcrypto.dll to ./bin (or in another way garrysmod/../bin, not garrysmod/lua/bin)
For Linux (perhaps it is possible without -dev, but I have not checked):
```
sudo apt-get install libssl-dev
```
3. Move gmsv_AntiFamilySharing_platform.dll to /garrysmod/lua/bin
4. Create .lua file in garrysmod/lua/autorun/server with this code:
```lua
require("require")
require("AntiFamilySharing")
```

## Credits
I am grateful to the creators of the following open source libraries:
  - [Boost C++ Libraries](http://www.boost.org/) (Boost Software License)
  - [OpenSSL](https://www.openssl.org/) (Apache License 2.0)
  - [mINI](https://github.com/pulzed/mINI) (MIT License)
  - [json](https://github.com/nlohmann/json) (MIT License)
  - [gmod_require](https://github.com/danielga/gmod_require)
