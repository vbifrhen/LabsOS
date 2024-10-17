#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

    for (int i = 0; mode_str[i]; i++) {
        char who = mode_str[i];
        mode_t who_mask = 0;

        if (who == 'u') who_mask = S_IRWXU;
        else if (who == 'g') who_mask = S_IRWXG;
        else if (who == 'o') who_mask = S_IRWXO;

        i++;
        char operation = mode_str[i];

        i++;
        char perm = mode_str[i];
        mode_t perm_mask = 0;

        if (perm == 'r') perm_mask = S_IRUSR | S_IRGRP | S_IROTH;
        else if (perm == 'w') perm_mask = S_IWUSR | S_IWGRP | S_IWOTH;
        else if (perm == 'x') perm_mask = S_IXUSR | S_IXGRP | S_IXOTH;

        if (operation == '+') mode |= who_mask & perm_mask;
        else if (operation == '-') mode &= ~(who_mask & perm_mask);
    }

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
