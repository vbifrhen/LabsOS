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

// Структура для хранения информации о файлах
typedef struct {
    char *name;
    struct stat file_stat;
} file_info;

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
void print_long_format(const file_info* file, int max_size_length, int max_nlink_length) {
    struct passwd *pw = getpwuid(file->file_stat.st_uid);
    struct group  *gr = getgrgid(file->file_stat.st_gid);
    char timebuf[80];
    time_t now;
    time(&now);
    // Если дата создания более чем 6 месяцев
    if (file->file_stat.st_mtime > now - 6*30*24*60*60) {
        strftime(timebuf, sizeof(timebuf), "%b %d %H:%M", localtime(&file->file_stat.st_mtime));
    } 
    else {
        strftime(timebuf, sizeof(timebuf), "%b %d  %Y", localtime(&file->file_stat.st_mtime));
    }
    
    print_permissions(file->file_stat.st_mode);
    printf("%*ld %s %s %*ld %s ", max_nlink_length, file->file_stat.st_nlink, pw->pw_name, gr->gr_name,
           max_size_length, file->file_stat.st_size, timebuf);
}

// Функция для вывода имени файла с цветами и обработкой символических ссылок
void print_name_with_color(const char *name, const struct stat *file_stat, const char *path, int long_format) {
    char full_path[1024];
    snprintf(full_path, sizeof(full_path), "%s/%s", path, name);

    // Если это символическая ссылка
    if (S_ISLNK(file_stat->st_mode)) {
        char target[1024];
        int len = readlink(full_path, target, sizeof(target) - 1);
        if (len == -1) {
            perror("readlink");
            printf(COLOR_LINK "%s" COLOR_NORMAL, name);
            return;
        }
        target[len] = '\0';  // Завершаем строку        

        // Выводим символическую ссылку с цветом
        printf(COLOR_LINK "%s" COLOR_NORMAL, name);

        // Если формат длинный, выводим, куда ведёт ссылка
        if (long_format) {
            struct stat target_stat;
            stat(target, &target_stat);
            printf(" -> ");
            if (S_ISDIR(target_stat.st_mode)) {
                printf(COLOR_DIR "%s" COLOR_NORMAL, target);
            } else if (target_stat.st_mode & S_IXUSR) {
                printf(COLOR_EXEC "%s" COLOR_NORMAL, target);
            } else {
                printf("%s", target);
            }
        }
    } else if (S_ISDIR(file_stat->st_mode)) {
        // Директория
        printf(COLOR_DIR "%s" COLOR_NORMAL, name);
    } else if (file_stat->st_mode & S_IXUSR) {
        // Исполняемый файл
        printf(COLOR_EXEC "%s" COLOR_NORMAL, name);
    } else {
        // Обычный файл
        printf("%s", name);
    }
}


// Функция для сортировки файлов по имени
int compare_files(const void *a, const void *b) {
    file_info *file_a = (file_info *)a;
    file_info *file_b = (file_info *)b;
    return strcmp(file_a->name, file_b->name);
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

    // Массив для хранения информации о файлах
    file_info *files = NULL;
    int count = 0;
    int st_block = 0;
    int max_size_length = 0;
    int max_nlink_length = 0;

    // Чтение содержимого директории
    while ((entry = readdir(dp)) != NULL) {
        // Пропуск скрытых файлов, если опция -a не включена
        if (!show_all && entry->d_name[0] == '.') continue;

        // Формирование полного пути к файлу
        char full_path[1024];
        snprintf(full_path, sizeof(full_path), "%s/%s", path, entry->d_name);

        // Получение информации о файле
        if (lstat(full_path, &file_stat) == -1) {
            perror("lstat");
            continue;
        }

        // Запоминание информации о файле
        files = realloc(files, sizeof(file_info) * (count + 1));
        files[count].name = strdup(entry->d_name);
        files[count].file_stat = file_stat;

        // Вычисление максимальной длины размера файла для выравнивания
        int size_length = snprintf(NULL, 0, "%ld", file_stat.st_size);
        if (size_length > max_size_length) {
            max_size_length = size_length;
        }

        // Вычисление максимальной длины размера файла для выравнивания
        int nlink_length = snprintf(NULL, 0, "%ld", file_stat.st_nlink);
        if (nlink_length > max_nlink_length) {
            max_nlink_length = nlink_length;
        }

        count++;
        st_block = st_block + file_stat.st_blocks / 2;
    }

    // Закрытие директории
    closedir(dp);

    // Сортировка файлов по имени
    qsort(files, count, sizeof(file_info), compare_files);

    // Вывод места на диске
    printf("total %d\n", st_block);

    // Вывод файлов
    for (int i = 0; i < count; i++) {
        if (long_format) {
            print_long_format(&files[i], max_size_length, max_nlink_length);
        }

        print_name_with_color(files[i].name, &files[i].file_stat, path, long_format);

        if (long_format) {
            printf("\n");
        } else {
            printf("  ");
        }

        free(files[i].name);
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
