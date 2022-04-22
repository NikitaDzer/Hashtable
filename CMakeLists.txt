cmake_minimum_required(VERSION 3.16)
project(Hashtable C ASM)

set(CMAKE_C_STANDARD 11)
SET(MYCOMPILE_FLAGS "-O3 -mavx2 -mavx -msse2")
SET(CMAKE_C_FLAGS  "${MYCOMPILE_FLAGS}" )

add_executable(Hashtable main.c src/list.c src/dump.c src/hashtable.c src/hash.c src/store.s include/dump.h include/hashtable.h include/config.h include/dump.h include/hash.h include/hashtable.h include/htdef.h include/htindex.h include/list.h test/test.c test/test.h)
