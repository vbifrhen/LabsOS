#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <time.h>
#include <errno.h>
#include <utime.h>
#include <libgen.h> 

#define MAX_FILENAME 256

// Структура для хранения метаданных файла
typedef struct {
    char filename[MAX_FILENAME];
    off_t filesize;
    mode_t mode;
    time_t atime;
    time_t mtime;
} FileMetadata;

// Вывод справки
void print_help() {
    printf("Usage:\n");
    printf("  ./archiver arch_name -i(--input) file1        Add file to archive\n");
    printf("  ./archiver arch_name -e(--extract) file1      Extract file from archive\n");
    printf("  ./archiver arch_name -s(--stat)               Show archive status\n");
    printf("  ./archiver -h(--help)                         Show help\n");
}

// Добавление файла в архив
int add_file_to_archive(const char *archive_name, const char *file_path) {
    int archive_fd = open(archive_name, O_WRONLY | O_CREAT | O_APPEND, 0644);
    if (archive_fd == -1) {
        perror("Error opening archive");
        return -1;
    }

    int input_fd = open(file_path, O_RDONLY);
    if (input_fd == -1) {
        perror("Error opening input file");
        close(archive_fd);
        return -1;
    }

    struct stat file_stat;
    if (fstat(input_fd, &file_stat) == -1) {
        perror("Error getting file metadata");
        close(input_fd);
        close(archive_fd);
        return -1;
    }

    // Получаем только имя файла из пути
    const char *file_name = basename((char *)file_path);

    FileMetadata metadata;
    strncpy(metadata.filename, file_name, sizeof(metadata.filename) - 1);
    metadata.filename[sizeof(metadata.filename) - 1] = '\0'; // Страхуемся от переполнения
    metadata.filesize = file_stat.st_size;
    metadata.mode = file_stat.st_mode;
    metadata.atime = file_stat.st_atime;
    metadata.mtime = file_stat.st_mtime;

    if (write(archive_fd, &metadata, sizeof(metadata)) != sizeof(metadata)) {
        perror("Error writing metadata to archive");
        close(input_fd);
        close(archive_fd);
        return -1;
    }

    // Записываем содержимое файла
    char buffer[1024];
    ssize_t bytes_read;
    while ((bytes_read = read(input_fd, buffer, sizeof(buffer))) > 0) {
        if (write(archive_fd, buffer, bytes_read) != bytes_read) {
            perror("Error writing file data to archive");
            close(input_fd);
            close(archive_fd);
            return -1;
        }
    }

    if (bytes_read == -1) {
        perror("Error reading input file");
    }

    close(input_fd);
    close(archive_fd);
    return 0;
}


// Извлечение файла из архива
int extract_file_from_archive(const char *archive_name, const char *file_name) {
    int archive_fd = open(archive_name, O_RDONLY);
    if (archive_fd == -1) {
        perror("Error opening archive");
        return -1;
    }

    FileMetadata metadata;
    int file_found = 0;

    // Проход по файлам в архиве, чтение метаданных каждого файла
    while (read(archive_fd, &metadata, sizeof(metadata)) == sizeof(metadata)) {
        if (strcmp(metadata.filename, file_name) == 0) {
            // Если нашли нужный файл
            file_found = 1;

            // Создаем новый файл с извлекаемыми данными
            int output_fd = open(file_name, O_WRONLY | O_CREAT | O_TRUNC, metadata.mode);
            if (output_fd == -1) {
                perror("Error creating extracted file");
                close(archive_fd);
                return -1;
            }

            // Чтение содержимого файла из архива и запись в новый файл
            char buffer[1024];
            ssize_t bytes_to_read = metadata.filesize;
            ssize_t bytes_read;

            while (bytes_to_read > 0) {
                bytes_read = read(archive_fd, buffer, sizeof(buffer));
                if (bytes_read <= 0) {
                    perror("Error reading from archive");
                    close(output_fd);
                    close(archive_fd);
                    return -1;
                }
                if (write(output_fd, buffer, bytes_read) != bytes_read) {
                    perror("Error writing to extracted file");
                    close(output_fd);
                    close(archive_fd);
                    return -1;
                }
                bytes_to_read -= bytes_read;
            }

            // Восстановление временных меток
            struct utimbuf new_times;
            new_times.actime = metadata.atime;
            new_times.modtime = metadata.mtime;
            utime(file_name, &new_times);

            close(output_fd);
            break; // Файл найден и извлечен, выходим из цикла
        } else {
            // Пропускаем данные файла, чтобы перейти к следующему файлу в архиве
            if (lseek(archive_fd, metadata.filesize, SEEK_CUR) == -1) {
                perror("Error seeking to next file in archive");
                close(archive_fd);
                return -1;
            }
        }
    }

    close(archive_fd);

    if (!file_found) {
        fprintf(stderr, "File not found in archive\n");
        return -1;
    }

    return 0;
}




// Показать содержимое архива
int show_archive_status(const char *archive_name) {
    int archive_fd = open(archive_name, O_RDONLY);
    if (archive_fd == -1) {
        perror("Error opening archive");
        return -1;
    }

    FileMetadata metadata;
    printf("Archive contents:\n");
    while (read(archive_fd, &metadata, sizeof(metadata)) == sizeof(metadata)) {
        printf("File: %s, Size: %ld bytes, Mode: %o\n",
               metadata.filename, metadata.filesize, metadata.mode);
        lseek(archive_fd, metadata.filesize, SEEK_CUR);
    }

    close(archive_fd);
    return 0;
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        print_help();
        return 1;
    }

    const char *archive_name = argv[1];
    const char *command = argv[2];

    if (strcmp(command, "-i") == 0 || strcmp(command, "--input") == 0) {
        if (argc < 4) {
            fprintf(stderr, "File name missing for input\n");
            return 1;
        }
        add_file_to_archive(archive_name, argv[3]);
    } else if (strcmp(command, "-e") == 0 || strcmp(command, "--extract") == 0) {
        if (argc < 4) {
            fprintf(stderr, "File name missing for extraction\n");
            return 1;
        }
        extract_file_from_archive(archive_name, argv[3]);
    } else if (strcmp(command, "-s") == 0 || strcmp(command, "--stat") == 0) {
        show_archive_status(archive_name);
    } else if (strcmp(command, "-h") == 0 || strcmp(command, "--help") == 0) {
        print_help();
    } else {
        fprintf(stderr, "Unknown command\n");
        print_help();
        return 1;
    }

    return 0;
}
