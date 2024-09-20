#include <dirent.h>
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


// Основная программа
int main(int argc, char *argv[]) {
    int num_not_empty = 0;
    int num_all = 0;
    int end_symb = 0;
    int opt;

    // Обработка опций с помощью getopt
    while ((opt = getopt(argc, argv, "bEn")) != -1) {
        switch (opt) {
            case 'b':
                num_not_empty = 1;
                break;
            case 'n':
                num_all = 1;
                break;
            case 'E':
                end_symb = 1;
                break;
            default:
                fprintf(stderr, "Usage: %s [-n] [-b] [-E]\n", argv[0]);
                exit(EXIT_FAILURE);
        }
    }

    // Если директория не указана, использовать текущую
    if (optind >= argc) {
        fprintf(stderr, "No input", argv[0]);
        exit(EXIT_FAILURE);
    } else {
        // Вывод содержимого указанных директорий
        for (int i = optind; i < argc; i++) {
            printf("%s:\n", argv[i]);
            print_to_file(argv[i], show_all, long_format);
        }
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
