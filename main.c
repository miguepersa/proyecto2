#include <stdio.h>
#include <getopt.h>

#include "Funciones.h"

#define MAX_REGIONS 32

int main(int argc, char *const argv[])
{
    int opt;
    int no_count_flag = 0;
    int list_flag = 0;
    int size_flag = 0;
    char *region = NULL;
    char *species = NULL;
    char *type = NULL;
    char name[256];

    static struct option long_options[] = {
        {"nocount", no_argument, 0, 'c'},
        {"list", no_argument, 0, 'l'},
        {"size", no_argument, 0, 's'},
        {"region", required_argument, 0, 'r'},
        {"species", required_argument, 0, 'p'},
        {"type", required_argument, 0, 't'},
        {0, 0, 0, 0}
    };

    while ((opt = getopt_long(argc, argv, "cslr:p:t:", long_options, NULL)) != -1) {
        switch (opt) {
            case 'c':
                no_count_flag = 1;
                break;
            case 'l':
                list_flag = 1;
                break;
            case 's':
                size_flag = 1;
                break;
            case 'r':
                region = optarg;
                break;
            case 'p':
                species = optarg;
                break;
            case 't':
                type = optarg;
                break;
            case '?':
                printf("Uso: $ ./fameChecker [-r <region>] [-s <species>] [-t <type>] [-c|--nocount] [-l|--list] [--size] [name]\n");
                break;
            default:
                /* handle other cases */
                break;
        }
    }

    if (optind < argc) {
        strcpy(name, argv[optind]);
    }

    search_dir(".", region, species, type, no_count_flag, list_flag, size_flag, name);

    return 0;
}
