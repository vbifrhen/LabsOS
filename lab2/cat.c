#include <dirent.h>
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void output_string(int simb, int flag_V, int onlyE, int onlyT);
void print_to_file(FILE *file, int flag_b, int flag_n, int flag_s, int flag_e, int flag_t, int flag_v);

int main(int argc, char *argv[]) {
  int opt;
  int flag_b = 0, flag_n = 0, flag_s = 0, flag_e = 0, flag_t = 0, flag_v = 0;

  static const struct option long_options[] = {
      {"number-nonblank", no_argument, NULL, 'b'},
      {"number", no_argument, NULL, 'n'},
      {"squeeze-blank", no_argument, NULL, 's'},
      {NULL, 0, NULL, 0},
  };

   while ((opt = getopt_long(argc, argv, "benstvET", long_options, NULL)) != -1) {
    switch (opt) {
      case 'b':
        flag_b = 1;
        break;
      case 'n':
        flag_n = 1;
        break;
      case 's':
        flag_s = 1;
        break;
      case 'e':
        flag_e = 1;
        flag_v = 1;
        break;
      case 't':
        flag_t = 1;
        flag_v = 1;
        break;
      case 'v':
        flag_v = 1;
        break;
      case 'E':
        flag_e = 1;
        break;
      case 'T':
        flag_t = 1;
        break;
      default:
        fprintf(stderr, "Unknown option '-%c'\n", opt);
        return 1;
    }
  }
  if (optind < argc) {
    for (int i = optind; i < argc; i++) {
      FILE *file = fopen(argv[i], "r");
      if (!file) {
        fprintf(stderr, "Error opening file: %s\n", argv[i]);
        return 1;
      }
      print_to_file(file, flag_b, flag_n, flag_s, flag_e, flag_t, flag_v);
      fclose(file);
    }
  } else {
    // Если файл не указан, читаем из стандартного ввода
    print_to_file(stdin, flag_b, flag_n, flag_s, flag_e, flag_t, flag_v);
  }

  return 0;
}

void print_to_file(FILE *file, int flag_b, int flag_n, int flag_s, int flag_e, int flag_t, int flag_v) {
  char line[1000];
  int counter = 0;
  int blank_line_counter = 0;
  int ch;

  while (fgets(line, sizeof(line), file) != NULL) {
    // Squeeze blank lines
    if (flag_s && line[0] == '\n') {
      if (blank_line_counter > 0) {
        continue;
      }
      blank_line_counter++;
    } else {
      blank_line_counter = 0;
    }

    if (flag_b && line[0] != '\n') {
      counter++;
      printf("%6d\t", counter);
    } else if (flag_n) {
      counter++;
      printf("%6d\t", counter);
    }

    for (int i = 0; line[i] != '\0'; i++) {
      ch = line[i];
      output_string(ch, flag_v, flag_e, flag_t);
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