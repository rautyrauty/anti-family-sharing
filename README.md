# Multithreaded Anti Family Sharing

## Install

Move gmsv_AntiFamilySharing_win32.dll to \garrysmod\lua\bin (create if it doesn't exist)

Move sv_anti-family-sharing.lua to \garrysmod\lua\autorun\server (same)


## Preparation for Build
Clone [gmod-module-base-development](https://github.com/Facepunch/gmod-module-base/tree/development)

Install [Boost C++ Libraries](boost) and [OpenSSL](https://www.openssl.org/) for x32 (because all gmod servers are running on this bit depth)

Override OPENSSL_ROOT_DIR,BOOST_ROOT and GMOD_MODULE_BASE_DIR in [CMakeLists.txt](https://github.com/rautyrauty/multithreaded-anti-family-sharing/blob/main/CMakeLists.txt#L10)

## Credits
I am grateful to the creators of the following open source libraries:
  - [Boost C++ Libraries](http://www.boost.org/) (Boost Software License)
  - [OpenSSL](https://www.openssl.org/) (Apache License 2.0)
  - [mINI](https://github.com/pulzed/mINI) (MIT License)
  - [json](https://github.com/nlohmann/json) (MIT License)

