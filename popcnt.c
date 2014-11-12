/*
 * File:   newmain.c
 * Author: nekottyo
 *
 * Created on 2014/11/04, 16:56
 */

#include <stdio.h>
#include <smmintrin.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>

/*
 *
 */

int popCnt64(unsigned long long int vector);
int hammingdist(char* vector1, char* vector2);
unsigned long long int ascii_to_hex(const char *s);


int main(void) {
    int pop = _mm_popcnt_u64(0xf0f0f0f0f0f0f0f0ULL);


    printf("pop = %d\n", pop);

    char c1[] = "ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff";
    char c2[] = "ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff";


    unsigned long long int i1 = ascii_to_hex(c1);
    unsigned long long int i2 = ascii_to_hex(c2);
    printf("%llx", i1);
    clock_t start, end;
    start = clock();

//    for (int i = 1; i < 100000000; i++) {
        popCnt64(i1 ^ i2);
//    }
    end = clock();
    printf("%.2f秒かかりました\n", (double) (end - start) / CLOCKS_PER_SEC);
    return 0;
}

int popCnt64(unsigned long long int vector) {
    return _mm_popcnt_u64(vector);
}

int hammingdist(char* vector1, char* vector2) {
    return popCnt64(ascii_to_hex(vector1)^ascii_to_hex(vector2));
}

int hammingdist_ull(unsigned long long int vector1, char *vector2) {
    return popCnt64(vector1^ascii_to_hex((vector2)));
}

unsigned long long int ascii_to_hex(const char *s) {
    static const char table[256] = {
        ['0'] = 0,
        ['1'] = 1,
        ['2'] = 2,
        ['3'] = 3,
        ['4'] = 4,
        ['5'] = 5,
        ['6'] = 6,
        ['7'] = 7,
        ['8'] = 8,
        ['9'] = 9,
        ['A'] = 10,
        ['B'] = 11,
        ['C'] = 12,
        ['D'] = 13,
        ['E'] = 14,
        ['F'] = 15,
        ['a'] = 10,
        ['b'] = 11,
        ['c'] = 12,
        ['d'] = 13,
        ['e'] = 14,
        ['f'] = 15,
    };
    unsigned long long int result = 0;
    int c;

    for (const char *ss = s; (c = (unsigned char) *ss) != '\0'; ss++) {
        result = (result << 4) + table[c];
    }
    return result;
}

