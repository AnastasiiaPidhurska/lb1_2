#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <getopt.h>
#include <time.h>

#include "stats.h"
#include "arraylist.h"

#define DEFAULT_FILE "stats.txt"


void print_usage(const char *progname) {
    printf("Usage: %s [options]\n", progname);
    printf("Options:\n");
    printf("  -p, --proc        Collect CPU temperature\n");
    printf("  -v, --video       Collect GPU temperature\n");
    printf("  -h, --hard        Collect HDD temperature\n");
    printf("  -t, --time N      Interval in seconds between measurements\n");
    printf("  -n, --number N    Number of iterations\n");
    printf("  --help            Show this message\n");
}


void save_stats(ArrayList *list, const char *filename) {
    FILE *f = fopen(filename, "w");
    if (!f) {
        perror("fopen");
        return;
    }

    for (size_t i = 0; i < list->size; i++) {
        StatRecord *rec = (StatRecord*) arraylist_get(list, i);

        char *dev;
        switch (rec->device) {
            case DEVICE_CPU: dev = "CPU"; break;
            case DEVICE_GPU: dev = "GPU"; break;
            case DEVICE_HDD: dev = "HDD"; break;
            default: dev = "UNKNOWN";
        }

        fprintf(f, "%s\tUser:%s\tHost:%s\tTemp:%.2f\tTime:%s",
                dev, rec->user, rec->host,
                rec->temperature, ctime(&rec->timestamp));
    }

    fclose(f);
    printf("Stats saved to %s\n", filename);
}

int main(int argc, char *argv[]) {
    srand(time(NULL));

    int opt;
    int option_index = 0;

    int collect_cpu = 0;
    int collect_gpu = 0;
    int collect_hdd = 0;
    int interval = 1;
    int iterations = 1;

 
    const struct option long_opts[] = {
        {"proc",  no_argument,       0, 'p'},
        {"video", no_argument,       0, 'v'},
        {"hard",  no_argument,       0, 'h'},
        {"time",  required_argument, 0, 't'},
        {"number",required_argument, 0, 'n'},
        {"help",  no_argument,       0,  0 },
        {0,0,0,0}
    };

    while ((opt = getopt_long(argc, argv, "pvht:n:", long_opts, &option_index)) != -1) {
        switch (opt) {
            case 'p': collect_cpu = 1; break;
            case 'v': collect_gpu = 1; break;
            case 'h': collect_hdd = 1; break;
            case 't': interval = atoi(optarg); break;
            case 'n': iterations = atoi(optarg); break;
            case 0:   print_usage(argv[0]); return 0;
            default:  print_usage(argv[0]); return 1;
        }
    }

    if (!collect_cpu && !collect_gpu && !collect_hdd) {
        printf("No devices selected!\n");
        print_usage(argv[0]);
        return 1;
    }

    ArrayList *stats = arraylist_create(10);

    for (int i = 0; i < iterations; i++) {
        if (collect_cpu) {
            StatRecord *rec = create_stat(DEVICE_CPU);
            arraylist_add(stats, rec);
        }
        if (collect_gpu) {
            StatRecord *rec = create_stat(DEVICE_GPU);
            arraylist_add(stats, rec);
        }
        if (collect_hdd) {
            StatRecord *rec = create_stat(DEVICE_HDD);
            arraylist_add(stats, rec);
        }

        if (i < iterations - 1) {
            sleep(interval);
        }
    }

   
    const char *filename = getenv("FILE");
    if (!filename) filename = DEFAULT_FILE;

    save_stats(stats, filename);

   
    for (size_t i = 0; i < stats->size; i++) {
        free(arraylist_get(stats, i));
    }
    arraylist_free(stats);

    return 0;
}
