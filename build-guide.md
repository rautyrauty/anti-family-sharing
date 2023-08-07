# Build Linux(Ubuntu 22.04.2 / Debian 12)

0. Install [CMake](https://cmake.org/), g++, git and clone repositories

```
sudo apt-get update
```
```
sudo apt-get install g++
```
```
sudo apt-get install cmake
```
```
sudo apt-get install git
```
```
sudo git clone https://github.com/rautyrauty/test-task-ALT
```
```
sudo git clone https://github.com/Facepunch/gmod-module-base.git -b development
```

1. Install [Boost C++ Libraries](boost) and [OpenSSL](https://www.openssl.org/)

```
sudo apt-get install libboost-all-dev
```
```
sudo apt-get install libssl-dev
```

2. Build
```
cd multithreaded-anti-family-sharing
```
```
sudo cmake .
```
```
sudo cmake --build ./ 
```
If OpenSSL or Boost or [gmod module base](https://github.com/Facepunch/gmod-module-base/tree/development) is installed in a non-standard location you can set options:
```
sudo cmake --build ./ -DOPENSSL_ROOT_DIR=some_dir -DBOOST_ROOT=some_dir -DGMOD_MODULE_BASE_DIR=some_dir
```
or (recommended) overwrite OPENSSL_ROOT_DIR,BOOST_ROOT and GMOD_MODULE_BASE_DIR in [CMakeLists.txt](https://github.com/rautyrauty/multithreaded-anti-family-sharing/blob/main/CMakeLists.txt#L10)


to get the paths to boost and openssl, use the "whereis" command:
```
whereis boost
```
```
whereis openssl
```
