#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <sys/stat.h>


mode_t parse_numeric_mode(const char *mode_str) {
    // Проверяем, что строка длиной 3 или 4 символа и содержит только цифры
    if ((strlen(mode_str) != 3 && strlen(mode_str) != 4) || !isdigit(mode_str[0]) || !isdigit(mode_str[1]) || !isdigit(mode_str[2])) {
        fprintf(stderr, "Error: Invalid numeric mode format. Must be a 3-digit or 4-digit number.\n");
        exit(EXIT_FAILURE);
    }

    // Преобразуем строку в восьмеричное число
    return strtol(mode_str, NULL, 8);
}


void apply_symbolic_mode(const char *mode_str, const char *file) {
    struct stat file_stat;
    if (stat(file, &file_stat) != 0) {
        perror("stat");
        exit(EXIT_FAILURE);
    }
    mode_t mode = file_stat.st_mode;

    int i = 0;
    while (mode_str[i]) {
        mode_t who_mask = 0;
        int who_specified = 0;  // Флаг, указывающий, что хотя бы одна категория указана

        // Проверяем категории (u, g, o) и строим маску
        while (mode_str[i] == 'u' || mode_str[i] == 'g' || mode_str[i] == 'o') {
            if (mode_str[i] == 'u') who_mask |= S_IRWXU;
            if (mode_str[i] == 'g') who_mask |= S_IRWXG;
            if (mode_str[i] == 'o') who_mask |= S_IRWXO;
            who_specified = 1;
            i++;
        }

        // Если не указано, к кому применять права, применяем ко всем (u, g, o)
        if (!who_specified) {
            who_mask = S_IRWXU | S_IRWXG | S_IRWXO;
        }

        // Проверяем операцию (+ или -)
        char operation = mode_str[i++];
        if (operation != '+' && operation != '-') {
            fprintf(stderr, "Error: Invalid operation. Use + or -.\n");
            exit(EXIT_FAILURE);
        }

        // Определяем права (r, w, x)
        while (mode_str[i] == 'r' || mode_str[i] == 'w' || mode_str[i] == 'x') {
            mode_t perm_mask = 0;
            if (mode_str[i] == 'r') perm_mask = S_IRUSR | S_IRGRP | S_IROTH;
            if (mode_str[i] == 'w') perm_mask = S_IWUSR | S_IWGRP | S_IWOTH;
            if (mode_str[i] == 'x') perm_mask = S_IXUSR | S_IXGRP | S_IXOTH;

            // Применяем операцию
            if (operation == '+') {
                mode |= who_mask & perm_mask;
            } else if (operation == '-') {
                mode &= ~(who_mask & perm_mask);
            }

            i++;
        }
    }

    // Применяем изменённые права к файлу
    if (chmod(file, mode) != 0) {
        perror("chmod");
        exit(EXIT_FAILURE);
    }
}



int main(int argc, char *argv[]) {
    if (argc != 3) {
        return EXIT_FAILURE;
    }

    const char *mode_str = argv[1];
    const char *file = argv[2];

    // Если права цифрами
    if (isdigit(mode_str[0])) {
        mode_t mode = parse_numeric_mode(mode_str);
        if (chmod(file, mode) != 0) {
            perror("chmod");
            return EXIT_FAILURE;
        }
    } else {
        // Права символами
        apply_symbolic_mode(mode_str, file);
    }

    return EXIT_SUCCESS;
}
