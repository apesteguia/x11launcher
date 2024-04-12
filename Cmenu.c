#include "Cmenu.h"
#include "list.h"
#include <X11/Xlib.h>
#include <X11/Xutil.h>
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

void drawItems(StringList *s, int n, Display *d, Drawable w, GC gcWhite,
               GC gcBlue) {
    Node *aux = s->start;
    int x, y, i;

    x = 5;
    y = DRAW_LILST + 12;
    i = 0;

    while (aux != NULL) {
        if (i == n) {
            XFillRectangle(d, w, gcBlue, 0, (i + 1) * DRAW_LILST, SCREEN_W,
                           DRAW_LILST);
        }
        XDrawString(d, w, gcWhite, 7, y, aux->text, strlen(aux->text));
        i++;
        aux = aux->next;
        y += DRAW_LILST;
    }
}
