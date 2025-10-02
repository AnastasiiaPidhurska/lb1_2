#ifndef STATS_H
#define STATS_H

#include <time.h>


typedef enum {
    DEVICE_CPU,
    DEVICE_GPU,
    DEVICE_HDD
} DeviceType;


typedef struct {
    DeviceType device;     
    double temperature;  
    char user[64];        
    char host[64];         
    time_t timestamp;     
} StatRecord;


double generate_temperature(DeviceType type);


void get_username(char *buffer, size_t size);


void get_hostname_info(char *buffer, size_t size);

StatRecord *create_stat(DeviceType type);

#endif
