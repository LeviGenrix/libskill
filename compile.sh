#!/bin/bash

# Очистка предыдущих файлов
rm -f libskill.so main.o errors.log

# Пути к Lua 5.4.3
LUA_DIR="/root/lua-5.4.3"

# Компиляция с оптимизацией O2 и правильными флагами
g++ -m32 -std=c++11 main.cpp -O1 -fPIC -c -w \
    -fwide-exec-charset=UTF16LE \
    -finput-charset="utf-8" \
    -fshort-wchar \
    -fpermissive \
    -fvisibility=hidden \
    -static-libgcc \
    -I$LUA_DIR/src \
    -I/root/LuaBridge/Source \
    2> ./errors.log

# Проверка ошибок компиляции
if [ $? -ne 0 ]; then
    echo "Compilation errors:"
    cat ./errors.log
    exit 1
fi

# Линковка с оптимизацией размера
g++ -m32 -std=c++11 main.o -shared -o libskill.so \
    $LUA_DIR/src/liblua.a -ldl \
    -Wl,--strip-debug -Wl,--gc-sections

# Дополнительная очистка
strip --strip-debug libskill.so

# Проверка результата
echo "Build completed. Checking results:"
ls -la libskill.so
echo "MD5: $(md5sum libskill.so)"
echo "SHA1: $(sha1sum libskill.so)"