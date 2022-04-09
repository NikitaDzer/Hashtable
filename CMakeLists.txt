cmake_minimum_required(VERSION 3.20)
project(HashTable C)

set(CMAKE_C_STANDARD 11)

add_executable(HashTable main.c list/src/list.c list/include/list.h src/hashTable.c src/hash.c include/hashTable.h include/hash.h include/ht_value.h)
