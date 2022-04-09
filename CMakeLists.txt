cmake_minimum_required(VERSION 3.20)
project(Hashtable C)

SET(MYCOMPILE_FLAGS "-g -O1")
SET(CMAKE_C_FLAGS "${MYCOMPILE_FLAGS}")

set(CMAKE_C_STANDARD 11)

add_executable(Hashtable main.c list/src/list.c list/include/list.h src/hashTable.c src/hash.c include/hashTable.h include/hash.h include/ht_value.h src/dump.c include/dump.h)
