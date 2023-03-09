#include "utilities.h"


char* get_current_time() {
    time_t now;
    struct tm* timeinfo;
    static char str_time[20];

    time(&now);
    timeinfo = localtime(&now);

    strftime(str_time, sizeof(str_time), "%Y-%m-%d %H%M%S", timeinfo);
    return str_time;
}