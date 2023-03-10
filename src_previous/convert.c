#include "filecontrol.h"
#include "convert.h"
#include <ctype.h>

#define MAX_LEN 1000

void convert_to_lowercase() {
    FILE* fp_in, * fp_out;
    char str[MAX_LEN];
    // 입력 파일 열기
    fp_in = open_file("db/db_subjective.tsv", "r");

    // 출력 파일 열기
    fp_out = open_file("db/db_subjective_lowercase.tsv", "w");

    // 파일 끝까지 한 줄씩 읽어서 소문자로 변환하여 출력 파일에 쓰기
    while (fgets(str, MAX_LEN, fp_in) != NULL) {
        int i;
        for (i = 0; str[i]; i++) {
            str[i] = tolower(str[i]);
        }
        fputs(str, fp_out);
    }

    // 파일 닫기
    close_file(fp_in);
    close_file(fp_out);

    printf("\nConversion complete.\n");
}