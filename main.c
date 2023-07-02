#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define a 1000   //переменная отвечает за количество сортируемых элементов
#define b 7000   //длина строки для сортировки

int main() {
    FILE *file; //указатель на файл
    char string[b], item[8];
    int i = 0, n = 0, k = 0, array[a], left = 0, last, tmp;
    //array[a] - сортируемый массив
    //left - левая граница массива
    //last - запись индекса последнего обмена,tmp - для перестановки элементов
    //i, n, k - счётчики


    //<----------- запись в файл рандомных чисел ---------->
    file = fopen("input.txt", "w"); //открытие файла input.txt, в котором находятся числа

    k = rand() % (2000 + 2000 + 1) - 2000;  //заполнение псевдорандомными числами в диапазоне [-1000; 1000]
    fprintf(file, "%d", k);

    for (i = 1; i < a; i++) {
        k = rand() % (1000 + 1000 + 1) - 1000;
        fprintf(file, ", %d", k);
    }
    fprintf(file, "%c", '\n');

    k = 0;
    i = 0;

    fclose(file);   //обязательно закрываем файл после работы


    //<----------- чтение из файла строки и её преобразование в массив чисел ---------->
    file = fopen("input.txt", "r");

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

        array[n] = atoi(item);  //функция int atoi(char* ) преобразовывает строку в целое число

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


    return 0;
}
