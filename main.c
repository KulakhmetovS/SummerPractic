#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    FILE *file;
    char string[256], item[8];
    int numbers[32], i = 0, n = 0, k = 0;

    //<----------- чтение из файла строки и её преобразование в массив чисел ---------->
    file = fopen("input.txt", "r");

    fgets(string, 256, file);
    printf("%s", string);

    fclose(file);

    while (1) {
        while ((string[i] != ',')) {
            item[k] = string[i];
            k++;
            i++;
            if (string[i] == '\n') {break;}
        }

        numbers[n] = atoi(item);

        printf("%d", numbers[n]);
        if (string[i] == '\n') break;
        n++;
        i++;
        k = 0;
        memset(item, 0, 8);
    }


    //<----------- запись в файл отсортированных чисел ---------->

return 0;
}
