// utilities.c 파일

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_LEN 1000

void convert_to_lowercase() {
    FILE* fp_in, * fp_out;
    char str[MAX_LEN];

    // 입력 파일 열기
    fp_in = fopen("db_english.tsv", "r");
    if (fp_in == NULL) {
        printf("Error: Unable to open input file.\n");
        exit(1);
    }

    // 출력 파일 열기
    fp_out = fopen("db_english_lowercase.tsv", "w");
    if (fp_out == NULL) {
        printf("Error: Unable to open output file.\n");
        exit(1);
    }

    // 파일 끝까지 한 줄씩 읽어서 소문자로 변환하여 출력 파일에 쓰기
    while (fgets(str, MAX_LEN, fp_in) != NULL) {
        int i;
        for (i = 0; str[i]; i++) {
            str[i] = tolower(str[i]);
        }
        fputs(str, fp_out);
    }

    // 파일 닫기
    fclose(fp_in);
    fclose(fp_out);

    printf("Conversion complete.\n");
}

