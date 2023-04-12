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
        ent = readdir(dir);
    }

    closedir(dir);
}

void regions_read_region(char* region, char* species, char* type)
{
    DIR *region_dir = opendir(strcat("./", region));
    
    if (region_dir = NULL){
        exit(1);
    }

    struct dirent* ent = readdir(region_dir);
    while (ent != NULL) {

        
    }
}