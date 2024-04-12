#include "Cmenu.h"
#include "list.h"
#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>

void getPrograms(StringList *s, const char *path) {
    DIR *dir;
    struct dirent *entry;

    dir = opendir(path);
    if (dir == NULL) {
        printf("Error al abrir directorio\n");
        return;
    }

    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_type != DT_DIR) {
            push(s, entry->d_name, sizeof(entry->d_name));
        }
    }
    closedir(dir);
}
