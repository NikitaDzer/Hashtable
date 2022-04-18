#define _CRT_SECURE_NO_WARNINGS


#include <stdio.h>

#include "include/hashtable.h"
#include "test/test.h"


int main(void)
{


    printf("%ld\n", bench_hashtable_lib("./HarryPotter.txt", 10, HT_TEST_REGULAR));
    printf("%ld\n", bench_hashtable_lib("./HarryPotter.txt", 10, HT_TEST_EXPANDED));
    printf("%ld\n", bench_hashtable_lib("./HarryPotter.txt", 10, HT_TEST_ALIGNED));

    return 0;
}