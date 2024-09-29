#include "grep_lib.h"
#include <unistd.h>

int main(int argc, char* argv[]) {
  struct flags flags_and_index = parsingProcess(argc, argv);
  grepFileManager(argc, argv, flags_and_index);
  return 0;
}

struct flags parsingProcess(int argc, char* argv[]) {
  struct flags buffer = {0};
  const char* short_opts = "+eivclnshfo";
  int opt;
  while ((opt = getopt(argc, argv, short_opts)) != -1) {
    if (opt == 'e') {
      buffer.e = 1;
    } else if (opt == 'i') {
      buffer.i = 1;
      buffer.e = 1;
    } else if (opt == 'v') {
      buffer.v = 1;
    } else if (opt == 'c') {
      buffer.c = 1;
    } else if (opt == 'l') {
      buffer.l = 1;
    } else if (opt == 'n') {
      buffer.n = 1;
      buffer.e = 1;
    } else if (opt == 'h') {
      buffer.h = 1;
      buffer.e = 1;
    } else if (opt == 's') {
      buffer.s = 1;
    } else if (opt == 'f') {
      buffer.f = 1;
    } else if (opt == 'o') {
      buffer.o = 1;
    }
  }
  buffer.index = optind;  // index argv[]
  return buffer;
}

void grepFileManager(int argc, char* argv[], struct flags opts) {
    int file_numbers = 0;
    // Проверка, поступают ли данные через стандартный ввод
    if (isatty(STDIN_FILENO) == 0) {
        searchForMatches(stdin, NULL, 0, opts, argv[opts.index]);
        return;
    }

    if (opts.index + 2 < argc) {
        file_numbers = 1;
    }
    if (opts.e + opts.c + opts.l + opts.v + opts.f + opts.o == 0) {
        opts.e = 1;
    }
    if (opts.v == 1) {
        opts.o = 0;
    }
    if ((opts.c == 1) && (opts.h == 1)) {
        opts.h = 0;
        file_numbers = 0;
    }
    if (opts.f == 1) {
        FILE* fp;
        if ((fp = fopen(argv[opts.index], "r+")) != NULL) {
            char* templates = templatesCreator(fp);
            for (int i = opts.index + 1; i < argc; i++) {
                step(argv[i], file_numbers, opts, templates);
            }
            free(templates);
            fclose(fp);
        } else {
            printf("grep: %s: No such file or directory\n", argv[opts.index]);
        }
    } else {
        char* template = argv[opts.index];
        for (int i = opts.index + 1; i < argc; i++) {
            step(argv[i], file_numbers, opts, template);
        }
    }
}

void step(char* filename, int file_numbers, struct flags opts, char* template) {
  FILE* fp;
  if ((fp = fopen(filename, "r+")) != NULL) {
    searchForMatches(fp, filename, file_numbers, opts, template);
    fclose(fp);
  } else if (opts.s == 0) {
    printf("grep: %s: No such file or directory\n", filename);
  }
}

char* templatesCreator(FILE* fp) {  //Функция создания шаблонов из файла. Читает
                                    //строки из файла и объединяет их в одну
                                    //строку, разделенную вертикальными чертами
  char* templates = calloc(10000, sizeof(char));
  char buffer[1000];
  while (fgets(buffer, 1000, fp) != NULL) {
    if (buffer[strlen(buffer) - 1] == '\n') {
      buffer[strlen(buffer) - 1] = '\0';
    }
    if (strlen(templates) > 0) {
      strcat(templates, "|");
    }
    strcat(templates, buffer);
  }
  return templates;
}

void searchForMatches(
    FILE* fp, char* filename, int file_numbers, struct flags opts,
    char* template) {
  regex_t regex;
  regmatch_t pmatch[1];
  regmatch_t matches[1];
  int search_strings = 0;
  int number = 1;
  int sign = 0;  // str printed
  char buffer[1000];
  
  // Компиляция регулярного выражения
  regcomp(
      &regex, template,
      REG_EXTENDED | (opts.i ? REG_ICASE : 0));  // если есть опция игнорирования регистра

  while ((fgets(buffer, 1000, fp)) != NULL) {
    int res = regexec(&regex, buffer, 0, pmatch, 0);
    if (opts.v == 1) {
      res = !res;
    }
    if (res == 0) {
      search_strings++;
    }
    if ((res == 0) && (opts.c == 0) && (opts.l == 0)) {
      if ((opts.h == 0) && (file_numbers == 1)) {
        printf("%s:", filename);
      }
      if (opts.n == 1) {
        printf("%d:", number);
      }
      
      // Если используется флаг `-o`, выводим только совпадения с подсветкой
      char* buffer_o = buffer;
      if (opts.o == 1) {
        while ((regexec(&regex, buffer_o, 1, matches, 0) == 0)) {
          // Печать с выделением цветом
          printf("%.*s\033[31m%.*s\033[0m", (int)(matches[0].rm_so),
                 buffer_o, (int)(matches[0].rm_eo - matches[0].rm_so),
                 buffer_o + matches[0].rm_so);
          buffer_o += matches[0].rm_eo;
          printf("\n");
        }
      } else {
        // Печать всей строки с выделением найденного совпадения
        char* ptr = buffer;
        while (regexec(&regex, ptr, 1, matches, 0) == 0) {
          // Печать до совпадения
          printf("%.*s", (int)(matches[0].rm_so), ptr);
          // Печать совпадения с красным цветом
          printf("\033[1;31m%.*s\033[0m", (int)(matches[0].rm_eo - matches[0].rm_so),
                 ptr + matches[0].rm_so);
          ptr += matches[0].rm_eo;
        }
        printf("%s", ptr);  // Печать остатка строки после последнего совпадения
        sign = 1;
      }

      // Если строка не закончилась переносом строки, добавляем его
      if ((strchr(buffer, '\n') == NULL) && (sign == 1)) {
        printf("\n");
      }
    }
    sign = 0;
    number++;
  }

  // Вывод результата для флагов `-c` и `-l`
  if (opts.c == 1) {
    if ((opts.l == 1) && (search_strings != 0)) {
      search_strings = 1;
    }
    if (file_numbers == 0) {
      printf("%i\n", search_strings);
    } else {
      printf("%s:%i\n", filename, search_strings);
    }
  }
  if ((opts.l == 1) && (search_strings != 0)) {
    printf("%s\n", filename);
  }
  
  // Освобождение памяти, выделенной под регулярное выражение
  regfree(&regex);
}