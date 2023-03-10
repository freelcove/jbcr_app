#ifndef FILECONTROL_H
#define FILECONTROL_H

#include <stdio.h>

FILE* open_file(const char* filename, const char* mode);
void close_file(FILE* fp);

#endif