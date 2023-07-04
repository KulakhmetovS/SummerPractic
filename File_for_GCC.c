#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define a 10000   //переменная отвечает за количество элементов, доступных для сортировки
#define b 70000   //длина строки для сортировки

int main() {
    clock_t start_time, end_time;
    double cpu_time_used;

    FILE *file; //указатель на файл
    char string[b], item[8], filename[64];
    int i = 0, n = 0, k = 0, array[a], left = 0, last, tmp;
    //array[a] - сортируемый массив
    //left - левая граница массива
    //last - запись индекса последнего обмена,tmp - для перестановки элементов
    //i, n, k - счётчики


    label:  //метка для перехода при ошибках

    printf("Введите путь или имя файла с расширением: ");
    scanf("%s", filename);

    start_time = clock();  // Записываем начальное время


    //<----------- чтение из файла строки и её преобразование в массив чисел ---------->
    if ((file = fopen(filename, "r")) == NULL) {
        printf("ошибка при открытии файла %s\n", filename);
        goto label; //переход мометке для совершения повторного запроса
    }

    fgets(string, b, file);   //чтение чисел в качестве строки
    printf("\t# Исходный массив #\n%s", string);

    fclose(file);

    while (1) { //тут начинается магия
        while (string[i] != ',') {
            item[k] = string[i];
            k++;
            i++;
            if (string[i] == '\n') {break;}
        }

        array[n] = atoi(item); //функция int atoi(char* ) преобразовывает строку в целое число

        if(array[n] == NULL) {  //проверка на коррекность вводимых данных
            printf("Данные в файле не корректны!\nИсправьте их или выберите другой файл!\n");
            goto label; //переход по метке в случае ошибки
        }

        if (string[i] == '\n') break;
        n++;
        i++;
        k = 0;
        memset(item, 0, 8); //обнуляем промежуточный массив
    }

    int right = n;  //правая граница массива


    //<---------- сортировка массива ---------->
    while(left < right) {
        //сортировка массива вправо
        for(int j = left; j < right; j++) {
            if(array[j] > array[j + 1]) {   //если первый элемент больше второго, то меняем их местами
                //перестановка по правилу "Трёх стаканов"
                tmp = array[j];
                array[j] = array[j + 1];
                array[j + 1] = tmp;
                last = j;
            }
        }
        right = last;   //двигаем правую границу к индексу последнего обмена

        //сортировка массива влево
        for(int j = right - 1; j >= left; j--) {
            if(array[j] > array[j + 1]) {
                //перестановка по правилу "Трёх стаканов"
                tmp = array[j];
                array[j] = array[j + 1];
                array[j + 1] = tmp;
                last = j;
            }
        }
        left = last++;  //двигаем левую границу к индексу последнего обмена
    }


    //<----------- запись полученного результата в файл ---------->
    file = fopen("result.txt", "w");
    n++;
    fprintf(file, "%d", array[0]);

    for(int j = 1; j < n; j++) {
        fprintf(file ,", %d", array[j]);    //запись отсортированных значений в файл
    }

    fclose(file);


    //<---------- вывод содержимого отсортированного массива ---------->
    printf("\t# Отсортированный массив #\n");
    file = fopen("result.txt", "r");

    fgets(string, b, file);
    printf("%s", string);

    fclose(file);


    end_time = clock();  // Записываем конечное время

    cpu_time_used = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;  // Вычисляем время выполнения в секундах
    printf("\n");
    printf("Размер массива = %d\n", n);
    printf("Время выполнения программы: %f секунд\n", cpu_time_used);


    return 0;
}
