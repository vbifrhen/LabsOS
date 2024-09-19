#include <dirent.h>
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void output_string(int simb, int flag_V, int onlyE, int onlyT);
void print_to_file(FILE *file, int option);

int main(int argc, char *argv[]) {
  int option;

  static const struct option long_options[] = {
      {"number-nonblank", no_argument, NULL, 'b'},
      {"number", no_argument, NULL, 'n'},
      {"squeeze-blank", no_argument, NULL, 's'},
      {NULL, 0, NULL, 0},
  };

  option = getopt_long(argc, argv, "+beEnvstT", long_options, NULL);
  FILE *file = fopen(argv[optind], "r");
  if (!file) {
    printf("Error opening file\n");
    return 1;
  }
  if (option != -1) {
    print_to_file(file, option);
    fclose(file);
  } else {
    print_to_file(file, option);
    fclose(file);
  }
  return 0;
}

void print_to_file(FILE *file, int option) {
  char txt_file[1000];
  int counter = 0;
  int ch;
  switch (option) {
    case 'b':
      while (fgets(txt_file, 1000, file) != NULL) {
        if (txt_file[0] != '\n') {
          counter++;
          printf("%6d\t%s", counter, txt_file);
        } else {
          printf("%s", txt_file);
        }
      }
      break;
    case 'e':
      ch = fgetc(file);
      while (ch != EOF) {
        output_string(ch, 1, 1, 0);
        ch = fgetc(file);
      }
      break;

    case 'n':
      while (fgets(txt_file, 1000, file) != NULL) {
        counter++;
        printf("%6d\t%s", counter, txt_file);
      }
      break;

    case 's':
      while (fgets(txt_file, 1000, file) != NULL) {
        if (txt_file[0] != '\n') {
          counter = 0;
          printf("%s", txt_file);
        } else if (counter < 1) {
          printf("%s", txt_file);
          counter++;
        }
      }
      break;

    case 't':
      ch = fgetc(file);
      while (ch != EOF) {
        output_string(ch, 1, 0, 1);
        ch = fgetc(file);
      }
      break;

    case 'v':
      ch = fgetc(file);
      while (ch != EOF) {
        output_string(ch, 1, 0, 0);
        ch = fgetc(file);
      }
      break;

    case 'E':
      ch = fgetc(file);
      while (ch != EOF) {
        output_string(ch, 0, 1, 0);
        ch = fgetc(file);
      }
      break;

    case 'T':
      ch = fgetc(file);
      while (ch != EOF) {
        output_string(ch, 0, 0, 1);
        ch = fgetc(file);
      }
      break;

    default:
      while (fgets(txt_file, 256, file) != NULL) {
        printf("%s", txt_file);
      }
  }
}

void output_string(int simb, int flag_V, int flag_E, int flag_T) {
  if ('\t' == simb && flag_T) {
    printf("^");
    simb += 64;
  }
  if ('\n' == simb && flag_E) {
    printf("$");
  }
  if (flag_V) {
    if (simb > 127 && simb < 160)
      printf("M-^");
    else if ((simb < 32 && simb != '\n' && simb != '\t') || simb == 127)
      printf("^");
    if ((simb < 32 || (simb > 126 && simb < 160)) && simb != '\n' &&
        simb != '\t')
      simb = simb > 126 ? simb - 128 + 64 : simb + 64;
  }

  printf("%c", simb);
}
