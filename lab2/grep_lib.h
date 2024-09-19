#ifndef GREP_LIB_H
#define GREP_LIB_H

#include <getopt.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct flags {
  int e;
  int i;
  int v;
  int c;
  int l;
  int n;
  int h;
  int s;
  int f;
  int o;
  int index;  // for file reading
};

struct flags parsingProcess(int argc, char* argv[]);
void grepFileManager(int argc, char* argv[], struct flags opts);
void step(char* filename, int file_numbers, struct flags opts, char* template);
char* templatesCreator(FILE* fp);
void searchForMatches(FILE* fp, char* filename, int file_numbers,
                      struct flags opts, char* template);

#endif
