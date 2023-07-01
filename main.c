#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    FILE *file; //указатель на файл
    char string[256], item[8];
    int i = 0, n = 0, k = 0, array[32], left = 0, last, tmp;
    //array[a] - сортируемый массив
    //left - левая граница массива
    //last - запись индекса последнего обмена,tmp - для перестановки элементов
    //i, n, k - счётчики


    //<----------- чтение из файла строки и её преобразование в массив чисел ---------->
    file = fopen("input.txt", "r"); //открытие файла input.txt, в котором находятся числа

    fgets(string, 256, file);   //чтение чисел в качестве строки
    printf("\t# Исходный массив #\n%s", string);

    fclose(file);   //обязательно закрываем файл после работы

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

    fgets(string, 256, file);
    printf("%s", string);

    fclose(file);


    return 0;
}
