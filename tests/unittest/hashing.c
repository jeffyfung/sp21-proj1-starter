#include "hashtable.h"
#include "philphix.h"
#include <stdlib.h>
#include <stdio.h>

void testStringHashAlphaNumeric() {
    fprintf(stderr, "testing stringHash with basic alphanumeric\n");
    char str1[] = "HelloWorld";
    char str2[] = "HelloWorld";
    char str3[] = "Hello1World23";
    char str4[] = "123";
    char str5[] = "123";
    unsigned int hc1 = stringHash(str1);
    unsigned int hc2 = stringHash(str2);
    unsigned int hc3 = stringHash(str3);
    unsigned int hc4 = stringHash(str4);
    unsigned int hc5 = stringHash(str5);
    if (hc1 != hc2) fprintf(stderr, "error: hc1 != hc2");
    if (hc1 == hc3) fprintf(stderr, "error: hc1 == hc3");
    if (hc3 == hc4) fprintf(stderr, "error: hc3 == hc4");
    if (hc4 != hc5) fprintf(stderr, "error: hc4 != hc5");
    fprintf(stderr, "test completed; sample hashcode: %d", hc3);
}

void testStringHashZeroAndSameLeadingChar() {
    char str1[] = "xxx00abc";
    char str2[] = "xxx00456";
    char str3[] = "xxx00hello";
    unsigned int hc1 = stringHash(str1);
    unsigned int hc2 = stringHash(str2);
    unsigned int hc3 = stringHash(str3);
    if (hc1 == hc2 || hc1 == hc3 || hc2 == hc3) fprintf(stderr, "error: the hashcodes shouldnt be equal");
}

void testLargeInput() {
    char longStr[] = "fhjksldbnjfsdbfjkl2b3ru329rh89pgh89dgf
    h8sd0fbd89fs0h8942b0f809vbd8g0ah8f9sfhnd9sbf8sd9f0b8s9af
    bd8s9afb8sd9fbd8s9afbds89fbadgff3b4fuheufbhsjakdb293fb20
    8453920f57480g7df0vgbd7f8gb0sa7g80bsad7sf80safb7s80fb748
    30b478305b73840br7e80bfd7s80abf74097943895732957r8767d6s6d6f67s86792990";
    unsigned int hc = stringHash(longStr);
    if (hc >= NUM_BUCKET) { fprintf(stderr, "error: hc should be smaller than 32") }

    // check the entries in each bucket
}

int main(){
    testStringHashAlphaNumeric();
    testStringHashZeroAndSameLeadingChar();
    testLargeInput();
    return 0;
}