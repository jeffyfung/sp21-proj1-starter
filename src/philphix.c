/*
 * Include the provided hash table library.
 */
#include "hashtable.h"

/*
 * Include the header file.
 */
#include "philphix.h"

/*
 * Standard IO and file routines.
 */
#include <stdio.h>

/*
 * General utility routines (including malloc()).
 */
#include <stdlib.h>

/*
 * Character utility routines.
 */
#include <ctype.h>

/*
 * String utility routines.
 */
#include <string.h>

#include "unittest.h"
#include <assert.h>

/*
 * This hash table stores the dictionary.
 */
HashTable *dictionary;

/*
 * The MAIN routine.  You can safely print debugging information
 * to standard error (stderr) as shown and it will be ignored in 
 * the grading process.
 */
int main(int argc, char **argv) {
  if (argc == 1) { 
    unittest();
    return 0; 
  }

  if (argc != 2) {
    fprintf(stderr, "Specify a dictionary\n");
    return 1;
  }
  /*
   * Allocate a hash table to store the dictionary.
   */
  fprintf(stderr, "Creating hashtable\n");
  dictionary = createHashTable(0x61C, &stringHash, &stringEquals);

  fprintf(stderr, "Loading dictionary %s\n", argv[1]);
  readDictionary(argv[1]);
  fprintf(stderr, "Dictionary loaded\n");

  fprintf(stderr, "Processing stdin\n");
  processInput();
  /*
   * The MAIN function in C should always return 0 as a way of telling
   * whatever program invoked this that everything went OK.
   */
  return 0;
}

/*
 * This should hash a string to a bucket index.  Void *s can be safely cast
 * to a char * (null terminated string)
 */
unsigned int stringHash(void *s) {
  // -- TODO --
  int sum = 0;
  char *str = (char *) s;
  while (*str != '\0') {
    sum = sum * 31 + *str;
    str++;
  }
  return abs(sum); // base 31 number
}

/*
 * This should return a nonzero value if the two strings are identical 
 * (case sensitive comparison) and 0 otherwise.
 */
int stringEquals(void *s1, void *s2) {
  // -- TODO --
  return !strcmp((char *) s1, (char *) s2);
}

/*
 * This function should read in every word and replacement from the dictionary
 * and store it in the hash table.  You should first open the file specified,
 * then read the words one at a time and insert them into the dictionary.
 * Once the file is read in completely, return.  You will need to allocate
 * (using malloc()) space for each word.  As described in the spec, you
 * can initially assume that no word is longer than 60 characters.  However,
 * for the final bit of your grade, you cannot assumed that words have a bounded
 * length.  You CANNOT assume that the specified file exists.  If the file does
 * NOT exist, you should print some message to standard error and call exit(61)
 * to cleanly exit the program.
 */
void readDictionary(char *dictName) {
  // -- TODO --
  FILE *fp = fopen(dictName, "r");
  if (!fp) {
    fprintf(stderr, "Error in opening file: %s\n", dictName);
    exit(61);
  }
  int wordLen = 16;
  int targetLen = 0;
  char *key = NULL;
  char *word = calloc(wordLen, sizeof(char));
  char c = '\0';
  while ((c = fgetc(fp))) {
    if (c == ' ' || c == '\t') {
      if (*word) {
        key = word;
        word = calloc(wordLen, sizeof(char)); 
      }
      continue;
    }
    if (c == '\n' || c == '\r' || c == EOF) {
      if (*word) {
        insertData(dictionary, key, word);
        word = calloc(wordLen, sizeof(char));
      }
      if (c == EOF) { break; }
      continue;
    }
    targetLen = strlen(word);
    if (targetLen + 1 == wordLen) {
      wordLen *= 2;
      word = realloc(word, wordLen);
    }
    word[targetLen] = c;
    word[targetLen + 1] = '\0';
  }
  if (!*word) { free(word); }
  fclose(fp);
}

void writeWordToStdout(char *word) {
  while (*word) {
    if (putchar(*word) == EOF) { fprintf(stderr, "error when writing to stdout"); }
    word++;
  }
}

/*
 * This should process standard input (stdin) and perform replacements as 
 * described by the replacement set then print either the original text or 
 * the replacement to standard output (stdout) as specified in the spec (e.g., 
 * if a replacement set of `taest test\n` was used and the string "this is 
 * a taest of  this-proGram" was given to stdin, the output to stdout should be 
 * "this is a test of  this-proGram").  All words should be checked
 * against the replacement set as they are input, then with all but the first
 * letter converted to lowercase, and finally with all letters converted
 * to lowercase.  Only if all 3 cases are not in the replacement set shoud 
 * it report the original word.
 *
 * Since we care about preserving whitespace and pass through all non alphabet
 * characters untouched, scanf() is probably insufficent (since it only considers
 * whitespace as breaking strings), meaning you will probably have
 * to get characters from stdin one at a time.
 *
 * Do note that even under the initial assumption that no word is longer than 60
 * characters, you may still encounter strings of non-alphabetic characters (e.g.,
 * numbers and punctuation) which are longer than 60 characters. Again, for the 
 * final bit of your grade, you cannot assume words have a bounded length.
 */
void processInput() {
  // -- TODO --
  // cannot extract from stdin more than once
  // 1) store the whole text
  // 2) store the sentence (and get maxSentenceLen / maxWordLen) and parse immediately
  // 3) wordLen *= 2; realloc(target, wordLen*2)
  char c = '\0';
  int wordLen = 16;
  int targetLen = 0;
  char *target = calloc(wordLen, sizeof(char));
  char *targetTrailingLc = calloc(wordLen, sizeof(char));
  char *targetLc = calloc(wordLen, sizeof(char));
  char *replacement;
  while ((c = fgetc(stdin))) {
    // reallocate memory with more space when necessary
    if ((strlen(target) + 1) == wordLen) { 
      wordLen *= 2;
      assert(target = realloc(target, wordLen));
      assert(targetTrailingLc = realloc(targetTrailingLc, wordLen));
      assert(targetLc = realloc(targetLc, wordLen));
    }
    // non-alnum entails the end of a possiblly replacable word; reset memory of targets
    if (!isalnum(c)) {
      writeWordToStdout(target);
      if (c == EOF) { break; }
      putchar(c);
      memset(target, 0, wordLen * sizeof(char));
      memset(targetTrailingLc, 0, wordLen * sizeof(char));
      memset(targetLc, 0, wordLen * sizeof(char));
      continue;
    }
    // improvement: start chopping the target from the beginning
    char *targetPtr = target;
    char *targetTrailingLcPtr = targetTrailingLc;
    char *targetLcPtr = targetLc;
    targetLen = strlen(target);
    target[targetLen] = c;
    target[targetLen + 1] = '\0';
    targetLc[targetLen] = tolower(c);
    targetLc[targetLen + 1] = '\0';
    targetTrailingLc[targetLen] = tolower(c);
    targetTrailingLc[targetLen + 1] = '\0';

    for (int i = 0; i <= targetLen; i++) {
      targetTrailingLcPtr[0] = targetPtr[0];
      if ((replacement = findData(dictionary, targetPtr))) {
        for (int n = 0; n < i; n++) { putchar(target[n]); }
        writeWordToStdout(replacement);
      } else if ((replacement = findData(dictionary, targetTrailingLcPtr))) {
        for (int n = 0; n < i; n++) { putchar(target[n]); }
        writeWordToStdout(replacement);
      } else if ((replacement = findData(dictionary, targetLcPtr))) {
        for (int n = 0; n < i; n++) { putchar(target[n]); }
        writeWordToStdout(replacement);
      }
      if (replacement) {
        memset(target, 0, wordLen * sizeof(char));
        memset(targetTrailingLc, 0, wordLen * sizeof(char));
        memset(targetLc, 0, wordLen * sizeof(char));
        i = targetLen + 1;
      } else {
        targetTrailingLcPtr[0] = targetLcPtr[0];
        targetPtr++;
        targetTrailingLcPtr++;
        targetLcPtr++;
      }
    }
  }
  free(target);
  free(targetTrailingLc);
  free(targetLc);
}
