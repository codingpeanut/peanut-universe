#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void get_source_file(char *source) {
    FILE *src;
    do {
        printf("輸入來源文件名稱: ");
        fgets(source, 100, stdin);
        source[strcspn(source, "\n")] = 0; // 去除換行符
        src = fopen(source, "rb");
        if (src == NULL) {
            printf("文件未找到。請重新輸入或輸入 'q' 退出。\n");
        }
    } while (src == NULL && source[0] != 'q');

    if (source[0] == 'q') {
        exit(0);
    }
}

void get_destination_file(char *destination) {
    FILE *dest;
    do {
        printf("輸入目標文件名稱: ");
        fgets(destination, 100, stdin);
        destination[strcspn(destination, "\n")] = 0; // 去除換行符
        dest = fopen(destination, "rb");
        if (dest != NULL) {
            printf("文件已存在。選擇一個選項:\n");
            printf("(a) 輸入新名稱 (b) 覆蓋 (c) 退出\n");
            char option;
            scanf(" %c", &option);
            getchar(); // 清除緩衝區中的換行符
            if (option == 'a') {
                continue;
            } else if (option == 'b') {
                fclose(dest); // 關閉已存在的文件
                break;
            } else {
                exit(0);
            }
        } else {
            break;
        }
    } while (1);
}

void copy_file(const char *source, const char *destination) {
    FILE *src = fopen(source, "rb");
    FILE *dest = fopen(destination, "wb");
    
    size_t chunk_size = 1024;
    char buffer[chunk_size];
    int bytes_copied;

    while ((bytes_copied = fread(buffer, 1, chunk_size, src)) > 0) {
        fwrite(buffer, 1, bytes_copied, dest);
    }

    fclose(src);
    fclose(dest);
}

int main() {
    char source[100], destination[100];

    // 獲取來源文件名稱
    get_source_file(source);

    // 獲取目標文件名稱
    get_destination_file(destination);

    // 複製文件
    copy_file(source, destination);

    printf("文件複製成功！\n");
    return 0;
}
