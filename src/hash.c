#include "../include/hash.h"

hash_t qhash(const void *const buffer, const size_t buffer_bytes)
{
   const char       *byte     = (char *)buffer;
   const char *const lastByte = byte + buffer_bytes;
   hash_t            hash     = 0xDED007;
   
   while (byte < lastByte)
      hash = ((hash << 0x8) + (hash >> 0x8)) ^ *byte++;
   
   return hash;
}