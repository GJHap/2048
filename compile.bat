@echo off
set PATH=%cd:~0,1%:\PortableSoftware\MinGW\bin;%PATH%
g++ -Wall -Wextra -Werror -Wpedantic -std=c++1z 2048.cpp Main.cpp -o 2048 -I E:\PortableSoftware\MinGW\external\include -L E:\PortableSoftware\MinGW\external\lib\static -lpdcurses