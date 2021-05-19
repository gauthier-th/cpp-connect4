# C++ Connect4

## Installation

This project is build with Visual C++ 2019 (MSVC++ 14.2).

You need to [download SFML 2.5.1](https://www.sfml-dev.org/download/sfml/2.5.1/) and put it in the named "SFML-2.5.1\".

You also need to [download boost library](https://www.boost.org/users/history/version_1_75_0.html) and put it in a folder named "boost\boost_1_75_0\". Then you will need to build boost with the following:
 - Run `bootstrap.bat` to build b2.exe
 - Run `b2 --toolset=msvc-10.0 --build-type=complete architecture=x86 address-model=64 stage`