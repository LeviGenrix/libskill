#! /bin/bash
rm -f libskill.so
rm -f main.o
g++ -m32 -std=c++11 main.cpp -O1 -fPIC -c -w -fwide-exec-charset=UTF16LE -finput-charset="utf-8" -fshort-wchar -fpermissive -fvisibility=hidden -static-libgcc -fno-omit-frame-pointer  -I/root/lua/src -I/root/LuaBridge/Source 2> ./errors.log
cat ./errors.log
g++ -m32 -std=c++11 main.o -shared -rdynamic -o libskill.so liblua.a -ldl 
