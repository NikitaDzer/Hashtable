# HT - Hashtable library

Powerful hashtable library with logsystem and error controller.
***
## Description
HT is written in C (C11 standard). The library provides a hashtable data structure and fast and safe API to work with it.
> For better performance **library uses AVX2 instructions**, so your PC must support them. <br> 
The library can be used only on X64 systems.

## Features
* Smart logsystem for tracking API calls
* Controller for error processing
* Provided 3 hashtable modes for different data amount

## Installation
> **Attention!**
Your **compiler has to support С11 standard** for using the library. <br>
Logsystem is not provided, if you are using MSVC.
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

Library provides 3 methods to operate with data in hashtable: **insert, remove, search**. <br>
Sample:

```c
const char bro_key[HT_MAX_N_KEY_CHARS] = "bro";
HtValue *bro = NULL;

hashtable_insert(ht_hashtable, bro_key, &(HtValue){.age = 18 });
bro = hashtable_search(ht_hashtable, transform_key("bro"));

if (bro == NULL)
{
    if (control_hashtable() == HT_BAD_KEY)
    printf("No bro in hashtable...");
}
else
{
    printf("My bro is %ld\n.", bro->age);
    hashtable_remove(ht_hashtable, transform_key("bro"));
}
```
> Hashtable keys must be in 32-byte buffer with null-terminal chars after the content part of the key.
For example: ```bro_key[32] = ['b','r','o','\0','\0'...'\0']```, where **32 - 3 = 29** null-terminal chars.
<br> So if you don't provide 32-byte keys, you should to use wrapper ```transform_key(const char *key)```, which is defined in the library.
For better performance **we recommend using your own 32-bytes keys, than calling transform_key**.

Function ```control_hashtable(void)``` is used to get report about the latest call of any hashtable functions: **construct, destruct, insert, remove, search**. In our case if we don't get the value by the key, then we will check if such a key exists at all. As a result, the program should print **"My bro is 18."** .

After using a hashtable, you need to clear it (using **remove** for each key) and call the destructor.

```c
destruct_hashtable(ht_hashtable);
```

***
## Who? 
HT Hashtable library is made by [Nikita Dzer](https://vk.com/id188977770). <br>
With Love ♥.
