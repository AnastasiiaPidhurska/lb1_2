#define _GNU_SOURCE
#include "stats.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>   
#include <pwd.h>
#include <sys/utsname.h>




double generate_temperature(DeviceType type) {
    switch (type) {
        case DEVICE_CPU:
            return 30 + rand() % 71;  
        case DEVICE_GPU:
            return 30 + rand() % 91;   
        case DEVICE_HDD:
            return 30 + rand() % 21;  
        default:
            return 0.0;
    }
}


void get_username(char *buffer, size_t size) {
    struct passwd *pw = getpwuid(getuid());
    if (pw) {
        strncpy(buffer, pw->pw_name, size - 1);
        buffer[size - 1] = '\0';
    } else {
        strncpy(buffer, "unknown", size);
    }
}


void get_hostname_info(char *buffer, size_t size) {
    if (gethostname(buffer, size) == -1) {
        strncpy(buffer, "unknown", size);
    }
}


StatRecord *create_stat(DeviceType type) {
    StatRecord *rec = malloc(sizeof(StatRecord));
    if (!rec) return NULL;

    rec->device = type;
    rec->temperature = generate_temperature(type);
    rec->timestamp = time(NULL);

    get_username(rec->user, sizeof(rec->user));
    get_hostname_info(rec->host, sizeof(rec->host));

    return rec;
}
