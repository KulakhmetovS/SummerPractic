#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

int main() {
    setlocale(LC_ALL, "RUS");

    FILE* file; //��������� �� ����
    char string[256], item[8];
    int i = 0, n = 0, k = 0, array[32], left = 0, last, tmp;
    //array[a] - ����������� ������
    //left - ����� ������� �������
    //last - ������ ������� ���������� ������,tmp - ��� ������������ ���������
    //i, n, k - ��������


    //<----------- ������ �� ����� ������ � � �������������� � ������ ����� ---------->
    file = fopen("input.txt", "r"); //�������� ����� input.txt, � ������� ��������� �����

    fgets(string, 256, file);   //������ ����� � �������� ������
    printf("\t# �������� ������ #\n%s", string);

    fclose(file);   //����������� ��������� ���� ����� ������

    while (1) { //��� ���������� �����
        while (string[i] != ',') {
            item[k] = string[i];
            k++;
            i++;
            if (string[i] == '\n') { break; }
        }

        array[n] = atoi(item);  //������� int atoi(char* ) ��������������� ������ � ����� �����

        if (string[i] == '\n') break;
        n++;
        i++;
        k = 0;
        memset(item, 0, 8); //�������� ������������� ������
    }

    int right = n;  //������ ������� �������


    //<---------- ���������� ������� ---------->
    while (left < right) {
        //���������� ������� ������
        for (int j = left; j < right; j++) {
            if (array[j] > array[j + 1]) {   //���� ������ ������� ������ �������, �� ������ �� �������
                //������������ �� ������� "��� ��������"
                tmp = array[j];
                array[j] = array[j + 1];
                array[j + 1] = tmp;
                last = j;
            }
        }
        right = last;   //������� ������ ������� � ������� ���������� ������

        //���������� ������� �����
        for (int j = right - 1; j >= left; j--) {
            if (array[j] > array[j + 1]) {
                //������������ �� ������� "��� ��������"
                tmp = array[j];
                array[j] = array[j + 1];
                array[j + 1] = tmp;
                last = j;
            }
        }
        left = last++;  //������� ����� ������� � ������� ���������� ������
    }


    //<----------- ������ ����������� ���������� � ���� ---------->
    file = fopen("result.txt", "w");
    n++;
    fprintf(file, "%d", array[0]);

    for (int j = 1; j < n; j++) {
        fprintf(file, ", %d", array[j]);    //������ ��������������� �������� � ����
    }

    fclose(file);


    //<---------- ����� ����������� ���������������� ������� ---------->
    printf("\t# ��������������� ������ #\n");
    file = fopen("result.txt", "r");

    fgets(string, 256, file);
    printf("%s", string);

    fclose(file);


    return 0;
}