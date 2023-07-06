#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <locale.h>
#define a 10000   //���������� �������� �� ���������� ���������, ��������� ��� ����������
#define b 70000   //����� ������ ��� ����������

int main() {
    setlocale(LC_ALL, "RUS");
    clock_t start_time, end_time;
    double cpu_time_used;

    FILE* file; //��������� �� ����
    char string[b], item[8], filename[64];
    int i = 0, n = 0, k = 0, array[a], left = 0, last, tmp;
    //array[a] - ����������� ������
    //left - ����� ������� �������
    //last - ������ ������� ���������� ������,tmp - ��� ������������ ���������
    //i, n, k - ��������


    label:  //����� ��� �������� ��� �������
    memset(string, 0, b);
    memset(item, 0, 8);
    i = 0;
    n = 0;
    k = 0;


    printf("������� ���� ��� ��� ����� � �����������: ");
    scanf("%s", filename);

    start_time = clock();  // ���������� ��������� �����


    //<----------- ������ �� ����� ������ � � �������������� � ������ ����� ---------->
    if ((file = fopen(filename, "r")) == NULL) {
        printf("������ ��� �������� ����� %s\n", filename);
        goto label; //������� ������� ��� ���������� ���������� �������
    }

    fgets(string, b, file);   //������ ����� � �������� ������
    

    fclose(file);

    while (1) { //��� ���������� �����
        while (string[i] != ',') {
            item[k] = string[i];
            k++;
            i++;
            if (string[i] == '\n') { break; }
        }

        array[n] = atoi(item); //������� int atoi(char* ) ��������������� ������ � ����� �����

        if (array[n] == NULL) {  //�������� �� ����������� �������� ������
            printf("������ � ����� �� ���������!\n��������� �� ��� �������� ������ ����!\n");
            goto label; //������� �� ����� � ������ ������
        }

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


    printf("\t# �������� ������ #\n%s", string);
    //<---------- ����� ����������� ���������������� ������� ---------->
    printf("\t# ��������������� ������ #\n");
    file = fopen("result.txt", "r");

    fgets(string, b, file);
    printf("%s", string);

    fclose(file);


    end_time = clock();  // ���������� �������� �����

    cpu_time_used = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;  // ��������� ����� ���������� � ��������
    printf("\n");
    printf("������ ������� = %d\n", n);
    printf("����� ���������� ���������: %f ������\n", cpu_time_used);


    return 0;
}
