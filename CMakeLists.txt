cmake_minimum_required(VERSION 3.20)
project(Hashtable C)

SET(MYCOMPILE_FLAGS "-g3 -O0")
SET(CMAKE_C_FLAGS "${MYCOMPILE_FLAGS}")

set(CMAKE_C_STANDARD 11)

add_executable(Hashtable main.c src/list.c include/list.h src/hashtable.c src/hash.c include/hashtable.h include/hash.h src/dump.c include/dump.h include/htdef.h include/settings.h)
