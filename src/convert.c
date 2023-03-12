#include "filecontrol.h"
#include "convert.h"
#include <ctype.h>

#define MAX_LEN 1000

void convert_to_lowercase() {
    FILE* fp_in, * fp_out;
    char str[MAX_LEN];
    // �Է� ���� ����
    fp_in = open_file("db/db_subjective.tsv", "r");

    // ��� ���� ����
    fp_out = open_file("db/db_subjective_lowercase.tsv", "w");

    // ���� ������ �� �پ� �о �ҹ��ڷ� ��ȯ�Ͽ� ��� ���Ͽ� ����
    while (fgets(str, MAX_LEN, fp_in) != NULL) {
        int i;
        for (i = 0; str[i]; i++) {
            str[i] = tolower(str[i]);
        }
        fputs(str, fp_out);
    }

    // ���� �ݱ�
    close_file(fp_in);
    close_file(fp_out);

    printf("\nConversion complete.\n");
}