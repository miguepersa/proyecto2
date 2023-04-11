#include "regions.h"

void regions_get_regions(int *nregions, char* regions[])
{
    struct dirent* ent;
    DIR* dir = opendir(".");

    if (dir = NULL){
        exit(1);
    }

    ent = readdir(dir);
    while (ent != NULL){
        if (ent->d_type == DT_DIR){
            regions[*nregions] = ent->d_name;
            *nregions++;
        }
    }


}

void regions_read_region(char* region, char* species)
{
    DIR *region_dir = opendir(strcat("./", region));
}