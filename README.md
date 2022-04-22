# HT - Hashtable library

A powerful hashtable library with call logging system and error handler.
***
## Description
HT is written in C (C11 standard). The library provides a hashtable data structure and fast and safe API to work with it.
> For better performance **library uses AVX2 instructions**, so your CPU must support them. <br> 
The library can be used only on X64 systems.

## Features
* Handler for error processing

* 3 hashtable modes for different data amount
* Smart logging system for tracking API functions calls
> The logging system is not provided, if you are using MSVC.

## Installation

* Clone the repository:

  `git clone https://github.com/NikitaDzer/Hashtable.git`
* Or download and unzip archive:

  `https://github.com/NikitaDzer/Hashtable/archive/refs/heads/main.zip`

☼ From this moment HT library is ready for your using. ☼


## Usage
Include hashtable library and construct new hashtable.

```c 
HtHashtable *ht_hashtable = construct_hashtable();
```
The library provides 3 functions to operate with data in hashtable: **insert, remove, search**. <br>
Code sample:

```c
const char bro_key[HT_MAX_N_KEY_CHARS] = "bro"; // 32-byte key buffer
HtValue *bro = NULL;

hashtable_insert(ht_hashtable, bro_key, &(HtValue){ .nickname = "Roflan" }); // inserts value with associated key to the hashtable
bro = hashtable_search(ht_hashtable, transform_key("bro"));                  // searches value with passed key

if (control_hashtable() == HT_BAD_KEY) // checks if the key is not found
    printf("No bro in hashtable...\n");
else
{
    printf("My bro's nickname is %s\n.", bro->nickname);
    hashtable_remove(ht_hashtable, transform_key("bro")); // removes key "bro" from the hashtable
}
```
> Hashtable **keys must be in 32-byte buffers with null-terminal chars after the content part** of keys. For example: <br>
> ```bro_key[HT_MAX_N_KEY_CHARS] = "bro"``` <br>
or <br>
```bro_key[32] = ['b','r','o','\0','\0'...'\0']```, where **32 - 3 = 29** null-terminal chars. <br> 
So if you don't provide 32-byte keys, you should to use wrapper ```const char* transform_key(const char *key)```, which is defined in the library.
For better performance we recommend using your own 32-bytes keys, than calling **transform_key**.

The function ```HtResult control_hashtable(void)``` is used to get report about the latest call of any hashtable functions: **construct, destruct, insert, remove, search**. 
In our case we check if such a key exists at all. As a result, the program should print **"My bro's nickname is Roflan."** .

After using a hashtable, you need to clear it with the destructor.

```c
destruct_hashtable(ht_hashtable);
```

***
## Who? 
HT Hashtable library is made by [Nikita Dzer](https://vk.com/id188977770). <br>
With Love ♥.
