#include <stdio.h>
#include <locale.h>
#include<Windows.h>
int main() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    FILE* fp;
    char filename[] = "db_sample.tsv";
    char id[20][50]={NULL}, problem[20][1000]= { NULL }, list[20][4][500]= { NULL }, answer[20][500]= { NULL }, date[20][500]= { NULL };
    int i = 0;
    fp = fopen(filename, "r");

    if (fp == NULL) {
        printf("Error opening file.\n");
        return 1;
    }

    printf("문제\t보기1\t보기2\t보기3\t보기4\t정답\n");
    printf("--------------------------------------------------------------------------------------------------\n");
    while (fscanf(fp, "%[^\t]\t%[^\t]\t%[^\t]\t%[^\t]\t%[^\t]\t%[^\t]\t%[^\t]\t%[^\n]\n", id[i],problem[i], list[i][0], list[i][1],list[i][2], list[i][3], answer[i],date[i]) == 8) {
        printf("%s. %s\n1) %s\t2) %s\n3) %s\t4) %s\n정답 : %s\t기출년도 : %s\n", id[i],problem[i], list[i][0], list[i][1],list[i][2], list[i][3], answer[i],date[i]);

    }
    
    fclose(fp);

    return 0;
}
