#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <getopt.h>
#include <errno.h>

// Цвета для разных типов файлов
#define COLOR_NORMAL "\x1B[0m"
#define COLOR_DIR "\x1B[34m"   // синий
#define COLOR_EXEC "\x1B[32m"  // зелёный
#define COLOR_LINK "\x1B[36m"  // бирюзовый

// Функция для вывода прав доступа в формате rwxr-xr-x
void print_permissions(mode_t mode) {
    char permissions[11] = "----------";

    if (S_ISDIR(mode)) permissions[0] = 'd';
    if (S_ISLNK(mode)) permissions[0] = 'l';

    permissions[1] = (mode & S_IRUSR) ? 'r' : '-';
    permissions[2] = (mode & S_IWUSR) ? 'w' : '-';
    permissions[3] = (mode & S_IXUSR) ? 'x' : '-';
    permissions[4] = (mode & S_IRGRP) ? 'r' : '-';
    permissions[5] = (mode & S_IWGRP) ? 'w' : '-';
    permissions[6] = (mode & S_IXGRP) ? 'x' : '-';
    permissions[7] = (mode & S_IROTH) ? 'r' : '-';
    permissions[8] = (mode & S_IWOTH) ? 'w' : '-';
    permissions[9] = (mode & S_IXOTH) ? 'x' : '-';

    printf("%s ", permissions);
}

// Функция для вывода информации в стиле `-l`
void print_long_format(const char* path, const struct stat* file_stat) {
    struct passwd *pw = getpwuid(file_stat->st_uid);
    struct group  *gr = getgrgid(file_stat->st_gid);
    char timebuf[80];
    strftime(timebuf, sizeof(timebuf), "%b %d %H:%M", localtime(&file_stat->st_mtime));

    print_permissions(file_stat->st_mode);
    printf("%ld %s %s %ld %s ", file_stat->st_nlink, pw->pw_name, gr->gr_name, file_stat->st_size, timebuf);
}

// Функция для вывода имени файла с цветами
void print_name_with_color(const char *name, const struct stat *file_stat) {
    if (S_ISDIR(file_stat->st_mode)) {
        printf(COLOR_DIR "%s" COLOR_NORMAL, name);
    } else if (S_ISLNK(file_stat->st_mode)) {
        printf(COLOR_LINK "%s" COLOR_NORMAL, name);
    } else if (file_stat->st_mode & S_IXUSR) {
        printf(COLOR_EXEC "%s" COLOR_NORMAL, name);
    } else {
        printf("%s", name);
    }
}

// Основная функция для вывода списка файлов
void list_directory(const char *path, int show_all, int long_format) {
    struct dirent *entry;
    struct stat file_stat;
    DIR *dp = opendir(path);

    if (dp == NULL) {
        perror("opendir");
        return;
    }

    // Массив для хранения имён файлов
    char **files = NULL;
    int count = 0;

    // Чтение содержимого директории
    while ((entry = readdir(dp)) != NULL) {
        // Пропуск скрытых файлов, если опция -a не включена
        if (!show_all && entry->d_name[0] == '.') continue;

        files = realloc(files, sizeof(char*) * (count + 1));
        files[count] = strdup(entry->d_name);
        count++;
    }

    // Закрытие директории
    closedir(dp);

    // Сортировка имён файлов
    qsort(files, count, sizeof(char*), (int (*)(const void *, const void *))strcmp);

    // Вывод файлов
    for (int i = 0; i < count; i++) {
        char full_path[1024];
        snprintf(full_path, sizeof(full_path), "%s/%s", path, files[i]);

        if (stat(full_path, &file_stat) == -1) {
            perror("stat");
            free(files[i]);
            continue;
        }

        if (long_format) {
            print_long_format(full_path, &file_stat);
        }

        print_name_with_color(files[i], &file_stat);

        if (long_format) {
            printf("\n");
        } else {
            printf("  ");
        }

        free(files[i]);
    }

    free(files);

    if (!long_format) {
        printf("\n");
    }
}

// Основная программа
int main(int argc, char *argv[]) {
    int long_format = 0;
    int show_all = 0;
    int opt;

    // Обработка опций с помощью getopt
    while ((opt = getopt(argc, argv, "la")) != -1) {
        switch (opt) {
            case 'l':
                long_format = 1;
                break;
            case 'a':
                show_all = 1;
                break;
            default:
                fprintf(stderr, "Usage: %s [-l] [-a] [directory...]\n", argv[0]);
                exit(EXIT_FAILURE);
        }
    }

    // Если директория не указана, использовать текущую
    if (optind >= argc) {
        list_directory(".", show_all, long_format);
    } else {
        // Вывод содержимого указанных директорий
        for (int i = optind; i < argc; i++) {
            printf("%s:\n", argv[i]);
            list_directory(argv[i], show_all, long_format);
        }
    }

    return 0;
}
