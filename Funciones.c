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
        if (entry->d_name[0] == '.') {
            continue; 
        }
        
        sprintf(path, "%s/%s", dir_name, entry->d_name);
        if (stat(path, &file_stat) < 0) {
            perror("stat");
            continue;
        }
        if (S_ISDIR(file_stat.st_mode)) {
            search_dir(path, region, species, type, nocount, list, size, name);
        } else if (S_ISREG(file_stat.st_mode)) {
            if (match_criteria(entry->d_name, region, species, type, name)) {
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
    if (!nocount) {
        printf("Total files: %d", total_files);
        if (size) {
            printf(" (%ldKB)", (long)total_size / 1024);
        }
        printf("\n");
    }
}

bool match_criteria(char* fn, char* region, char* species, char* type, char* name) {
    char *filename = malloc(64);
    strcpy(filename, fn);
    
    /* Verificar si el archivo comienza con el nombre dado (si se especificó uno) */
    if (name != NULL && strncmp(name, filename, strlen(name)) != 0) {
        return false;
    }
    
    /* Obtener el nombre del directorio de la región */
    char* region_dir = strtok(filename, "/");
    
    /* Verificar si el archivo está en la región especificada (si se especificó una) */
    if (region != NULL && strcmp(region, region_dir) != 0) {
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
        free(filename);
        return false;
    }

    free(filename);
    /* Si se pasaron todos los criterios, el archivo cumple con la búsqueda */
    return true;
}