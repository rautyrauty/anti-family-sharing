# Multithreaded Anti Family Sharing

## Install

Move gmsv_AntiFamilySharing_win32.dll to \garrysmod\lua\bin (create if it doesn't exist)

Move sv_anti-family-sharing.lua to \garrysmod\lua\autorun\server (same)


## Preparation for Build
Clone [gmod-module-base-development](https://github.com/Facepunch/gmod-module-base/tree/development)

Install [Boost C++ Libraries](boost) and [OpenSSL](https://www.openssl.org/) for x32 (because all gmod servers are running on this bit depth)

Override OPENSSL_ROOT_DIR,BOOST_ROOT and GMOD_MODULE_BASE_DIR in [CMakeLists.txt](https://github.com/rautyrauty/multithreaded-anti-family-sharing/blob/main/CMakeLists.txt#L10)

## Build Linux(Ubuntu 22.04.2)

0. Install [CMake](https://cmake.org/)

```bash
sudo apt-get install cmake
```

1. Install [Boost C++ Libraries](boost) and [OpenSSL](https://www.openssl.org/)

```bash
sudo apt-get install libboost-all-dev
sudo apt-get install libssl-dev
```

2. Build
```
cd [root-directory-of-project]
cmake .
cmake --build ./
```
If OpenSSL or Boost is installed in a non-standard location u can overwrite OPENSSL_ROOT_DIR and BOOST_ROOT in CMakeLists.txt or just
```
set OPENSSL_ROOT_DIR=some_dir
set BOOST_ROOT=some_dir
```


## Credits
I am grateful to the creators of the following open source libraries:
  - [Boost C++ Libraries](http://www.boost.org/) (Boost Software License)
  - [OpenSSL](https://www.openssl.org/) (Apache License 2.0)
  - [mINI](https://github.com/pulzed/mINI) (MIT License)
  - [json](https://github.com/nlohmann/json) (MIT License)

## Сделать

- Залить билд для линукса
- Изменить с создания новых потоков на передачу в один существующий