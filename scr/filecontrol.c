#include "filecontrol.h"

FILE* open_file(const char* filename, const char* mode) {
	FILE* fp = fopen(filename, mode);
	if (fp == NULL) {
		printf("Error: Unable to open file %s.\n", filename);
		exit(1);
	}
	return fp;
}

void close_file(FILE* fp) {
	fclose(fp);
}