#include <stdio.h>
#include <getopt.h>

#include "regions.h"

#define MAX_REGIONS 16

int main(int argc, char const *argv[])
{
    int opt;
    int count_flag = 1;
    int list_flag = 0;
    int size_flag = 0;
    int region_in_dir;
    char *region = NULL;
    char *species = NULL;
    char *type = NULL;
    char *name = NULL;
    int i;

    char* regions[MAX_REGIONS];
    int nregions = 0;

    static struct option long_options[] = {
        {"nocount", no_argument, 0, 'c'},
        {"list", no_argument, 0, 'l'},
        {"size", no_argument, 0, 's'},
        {"region", required_argument, 0, 'r'},
        {"species", required_argument, 0, 'p'},
        {"type", required_argument, 0, 't'},
        {0, 0, 0, 0}
    };

    while ((opt = getopt_long(argc, argv, "clr:p:t:", long_options, NULL)) != -1) {
        switch (opt) {
            case 'c':
                count_flag = 0;
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
                // handle invalid option
                break;
            default:
                // handle other cases
                break;
        }
    }

    if (optind < argc) {
        name = argv[optind];
    }

    regions_get_regions(&nregions, regions);

    if (region != NULL){

        for (i = 0; i < nregions; i++){
            if (strcmp(region, regions[i]) == 0){
                region_in_dir = 1;
                break;
            }
        }

        if (!region_in_dir){
            printf("Region no encontrada en el directorio actual\n");
            exit(1);
        }

        if (species != NULL){
            regions_read_region(region, species);
        }else {
            regions_read_region(region, "pokemon");
            regions_read_region(region, "trainers");
        }
    } else {
        for (i = 0; i < nregions; i++){
            region = regions[i];

            if (species != NULL){
                regions_read_region(region, species);
            }else {
                regions_read_region(region, "pokemon");
                regions_read_region(region, "trainers");
            }
        }
    }

    

    return 0;
}
