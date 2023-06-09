#include "Funciones.h"

void search_dir(char *dir_name, char *region, char *species, char *type, int nocount, int list, int size, char *name) {
    DIR *dir;
    struct dirent *entry;
    struct stat file_stat;
    char path[MAX_PATH];
    int total_files = 0;
    int total_size = 0;
    dir = opendir(dir_name);
    if (!dir) {
        perror("opendir");
        return;
    }
    while ((entry = readdir(dir))) {
        if (entry->d_name[0] == '.' || strcmp(entry->d_name, "fameChecker") == 0) {
            continue; 
        }
        
        sprintf(path, "%s/%s", dir_name, entry->d_name);
        if (stat(path, &file_stat) < 0) {
            perror("stat");
            continue;
        }
        if (S_ISDIR(file_stat.st_mode) ) {
            search_dir(path, region, species, type, nocount, list, size, name);
        } else if (S_ISREG(file_stat.st_mode)) {
            if (match_criteria(path, region, species, type, name)) {
                if (list) {
                    printf("%s", entry->d_name);
                    if (size) {
                        printf(" (%ldKB)", file_stat.st_size / 1024);
                    }
                    printf("\n");
                }
                total_files++;
                total_size += file_stat.st_size;
            }
        }
    }
    closedir(dir);
    if (!nocount && total_files > 0) {
        printf("Total files in \"%s\": %d", dir_name, total_files);
        if (size) {
            printf(" (%ldKB)", (long)total_size / 1024);
        }
        printf("\n\n");
    }
}

bool match_criteria(char* fn, char* region, char* species, char* type, char* name) {

    if (strcmp(fn, ".") == 0){
        return true;
    }
    
    /* Obtener el nombre del directorio de la región */
    char* region_dir = strtok(fn, "/");
    region_dir = strtok(NULL, "/");
    
    /* Verificar si el archivo está en la región especificada (si se especificó una) */
    if (region != NULL && region_dir != NULL && strcmp(region, region_dir) != 0) {
        return false;
    }
    
    /* Obtener el nombre del directorio de la especie */
    char *species_dir = strtok(NULL, "/");
    
    /* Verificar si el archivo es de la especie especificada (si se especificó una) */
    if (species != NULL && species_dir != NULL) {
        if (strcmp(species, species_dir) != 0){
            return false;
        }
    }
    
    /* Obtener el nombre del directorio del número de apariciones */
    char* type_dir = strtok(NULL, "/");
    
    /* Verificar si el archivo es del tipo de apariciones especificado (si se especificó uno) */
    if (type != NULL && type_dir != NULL && strcmp(type, type_dir) != 0) {
        return false;
    }

    char *f_name = strtok(NULL, "/");

    /* Verificar si el archivo comienza con el nombre dado (si se especificó uno) */
    if (name != NULL && f_name != NULL && strncmp(name, f_name, strlen(name)) != 0) {
        return false;
    }

    /* Si se pasaron todos los criterios, el archivo cumple con la búsqueda */
    return true;
}