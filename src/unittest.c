#include "hashtable.h"
#include "philphix.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>

void testStringHashAlphaNumeric() {
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
    if (hc1 != hc2) fprintf(stderr, "error: hc1 != hc2\n");
    if (hc1 == hc3) fprintf(stderr, "error: hc1 == hc3\n");
    if (hc3 == hc4) fprintf(stderr, "error: hc3 == hc4\n");
    if (hc4 != hc5) fprintf(stderr, "error: hc4 != hc5\n");
}

void testStringHashZeroAndSameLeadingChar() {
    char str1[] = "xxx00abc";
    char str2[] = "xxx00456";
    char str3[] = "xxx00hello";
    unsigned int hc1 = stringHash(str1);
    unsigned int hc2 = stringHash(str2);
    unsigned int hc3 = stringHash(str3);
    assert(!(hc1 == hc2 || hc1 == hc3 || hc2 == hc3));
}

void testStringHashLargeInput() {
    char longStr[] = "fhjksldbnjfsdbfjkl2b3ru329rh89pgh89dgf"
    "h8sd0fbd89fs0h8942b0f809vbd8g0ah8f9sfhnd9sbf8sd9f0b8s9af"
    "bd8s9afb8sd9fbd8s9afbds89fbadgff3b4fuheufbhsjakdb293fb20"
    "8453920f57480g7df0vgbd7f8gb0sa7g80bsad7sf80safb7s80fb748"
    "30b478305b73840br7e80bfd7s80abf74097943895732957r8767d6s6d6f67s86792990";
    stringHash(longStr);
}

void testStringEqualsNumeric() {
    char str1[] = "123456";
    char str2[] = "123456";
    char str3[] = "234567";
    char str4[] = "1234567";
    assert(stringEquals(str1, str2));
    assert(!stringEquals(str1, str3));
    assert(!stringEquals(str1, str4));
}

void testStringEqualsAlphanumeric() {
    char str1[] = "alpha1beta2charlie3";
    char str2[] = "alpha1beta2charlie3";
    char str3[] = "a1b2c3";
    char str4[] = "alphabetacharlie";
    assert(stringEquals(str1, str2));
    assert(!stringEquals(str1, str3));
    assert(!stringEquals(str1, str4));
}

void testInsertDataBasic() {
    // numeric, alphanumeric string, non-whitespace printable character
    HashTable *table = createHashTable(100, &stringHash, &stringEquals);
    char key1[] = "abc123";
    char data1[] = "123abc";
    int key2 = 555;
    int data2 = 5;
    char key3[] = "anyPrintableChar";
    char data3[] = "}}~!@#><?|%%";

    insertData(table, key1, data1);
    insertData(table, &key2, &data2);
    insertData(table, key3, data3);

    assert(!strcmp(findData(table, key1), data1));
    assert(!strcmp(findData(table, &key2), (char *) &data2));
    assert(!strcmp(findData(table, key3), data3));
    
    free(table->data);
    free(table);
}

void testInsertDataLongInput() {
    HashTable *table = createHashTable(100, &stringHash, &stringEquals);
    char key1[] = "abc123dddddddddddddh44354jjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjhjkkkk"
                "fdsfffffffffffffffffffffffffffhwhgiofrgenjknjkhjknjknkjnjkh3uiohu33"
                "89y89hdfh2jhjkbjkbjfkdbsjkfba89832983989899999fdsajfbbbbm3b2rbwwwss";
    char data1[] = "hello";
    insertData(table, key1, data1);
    assert(!strcmp(findData(table, key1), data1));
    free(table->data);
    free(table);
}

void testInsertDataDup() {
    HashTable *table = createHashTable(100, &stringHash, &stringEquals);
    char key1[] = "abc123";
    char data1[] = "123abc";
    int data2 = 5;
    insertData(table, key1, data1);
    insertData(table, key1, &data2);
    assert(!strcmp(findData(table, key1), data1));
    free(table->data);
    free(table);
}

void testInsertDataLargeArrayofInput() {
    FILE *fp = fopen("./tests/unittest/largeInput.txt", "r");
    if (!fp) {
        fprintf(stderr, "Error in opening input file\n");
        exit(61);
    }

    HashTable *table = createHashTable(100, &stringHash, &stringEquals);
    char input[500000];
    if (fgets(input, sizeof(input), fp)) {
        const char *d = ": ";
        char *key;
        int swt = 0;
        char *token = strtok(input, d);
        while (token) {
            if (!swt) { key = token; } else { insertData(table, key, token); };
            swt = 1 - swt;
            token = strtok(NULL, d);
        }
    } else {
        fprintf(stderr, "error in getting input");
        return; }
    fclose(fp);

    char *checkKey = "check";
    char *checkData = "check123";
    char *search = findData(table, checkKey); 
    assert(search);
    assert(!strcmp(search, checkData));
    free(table->data);
    free(table);
}

char dictDir[18] = "./tests/unittest/";
char *al    = "abcde";
char *num   = "01234";
char *alNum = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
char *nonWs = "!@#&()-[{}]:;,?/~$^+=<>\\*'\"";
char *longKey = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789"
                "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789"
                "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789"
                "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789"
                "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789"
                "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789"
                "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789"
                "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789"
                "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789"
                "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";                    ;

void testReadDictionaryBasic() {
    dictionary = createHashTable(100, &stringHash, &stringEquals);
    char fn[100] = "";
    readDictionary(strcat(strcpy(fn, dictDir), "basicDict.txt"));
    assert(!strcmp(findData(dictionary, "al"), al));
    assert(!strcmp(findData(dictionary, "num"), num));
    assert(!strcmp(findData(dictionary, "alNum"), alNum));
    assert(!strcmp(findData(dictionary, "nonWs"), nonWs));
    free(dictionary->data);
    free(dictionary);
}

void testReadDictionaryNoNewlineEnding() {
    dictionary = createHashTable(100, &stringHash, &stringEquals);
    char fn[100] = "";
    readDictionary(strcat(strcpy(fn, dictDir), "dictNoNewlineEnding.txt"));
    assert(!strcmp(findData(dictionary, "al"), al));
    assert(!strcmp(findData(dictionary, "num"), num));
    assert(!strcmp(findData(dictionary, "alNum"), alNum));
    assert(!strcmp(findData(dictionary, "nonWs"), nonWs));
    free(dictionary->data);
    free(dictionary);
}

void testReadDictionaryNonExistentFile() {
    fprintf(stderr, "testing with file that does not exist should print"
                    " a one-line error statemet: \n");
    dictionary = createHashTable(100, &stringHash, &stringEquals);
    char fn[100] = "";
    readDictionary(strcat(strcpy(fn, dictDir), "ne"));
    free(dictionary->data);
    free(dictionary);
}


void testReadDictionaryDupKeys() {
    dictionary = createHashTable(100, &stringHash, &stringEquals);
    char fn[100] = "";
    readDictionary(strcat(strcpy(fn, dictDir), "dictDupKeys.txt"));
    assert(!strcmp(findData(dictionary, "alNum"), alNum));
    free(dictionary->data);
    free(dictionary);
}

void testReadDictionaryInconsistentSpace() {
    dictionary = createHashTable(100, &stringHash, &stringEquals);
    char fn[100] = "";
    readDictionary(strcat(strcpy(fn, dictDir), "dictInconsistentSpace.txt"));
    assert(!strcmp(findData(dictionary, "al"), al));
    assert(!strcmp(findData(dictionary, "num"), num));
    assert(!strcmp(findData(dictionary, "alNum"), alNum));
    assert(!strcmp(findData(dictionary, "nonWs"), nonWs));
    free(dictionary->data);
    free(dictionary);
}

void testReadDictionaryLongKeyValue() {
    dictionary = createHashTable(100, &stringHash, &stringEquals);
    char fn[100] = "";
    readDictionary(strcat(strcpy(fn, dictDir), "dictLongKeyValue.txt"));
    assert(!strcmp(findData(dictionary, longKey), longKey));
    assert(!strcmp(findData(dictionary, "al"), al));
    assert(!strcmp(findData(dictionary, "num"), num));
    free(dictionary->data);
    free(dictionary);
}

void testReadDictionaryMultipleEntries() {
    dictionary = createHashTable(100, &stringHash, &stringEquals);
    char fn[100] = "";
    readDictionary(strcat(strcpy(fn, dictDir), "dictMultipleEntries.txt"));
    assert(!strcmp(findData(dictionary, "check1"), "check123"));
    assert(!strcmp(findData(dictionary, "check5"), "check567"));
    free(dictionary->data);
    free(dictionary);
}

int unittest(){
    testStringHashAlphaNumeric();
    testStringHashZeroAndSameLeadingChar();
    testStringHashLargeInput();
    testStringEqualsNumeric();
    testStringEqualsAlphanumeric();
    testInsertDataBasic();
    testInsertDataLongInput();
    testInsertDataDup();
    testInsertDataLargeArrayofInput();
    testReadDictionaryBasic();
    testReadDictionaryNoNewlineEnding();
    // testReadDictionaryNonExistentFile();
    testReadDictionaryDupKeys();
    testReadDictionaryInconsistentSpace();
    testReadDictionaryLongKeyValue();
    testReadDictionaryMultipleEntries();
    return 0;
}