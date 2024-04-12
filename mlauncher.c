#include "Cmenu.h"
#include "list.h"
#include <X11/X.h>
#include <X11/Xatom.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>

int main(void) {
    Display *d;
    Window w;
    XEvent e;
    struct tm *localTime;
    time_t currentTime;
    StringList items, screenItems;
    pid_t pid;
    int s, letterCount, row;
    char formattedString[100], name[MAX_INPUT_CHARS + 1] = "\0", *executable,
                                                      process[255];
    bool notEscape;

    d = XOpenDisplay(NULL);
    if (d == NULL) {
        fprintf(stderr, "Cannot open display\n");
        exit(1);
    }

    initStringList(&items);
    initStringList(&screenItems);
    getPrograms(&items, PATH);
    letterCount = row = 0;
    notEscape = false;

    currentTime = time(NULL);
    time(&currentTime);
    localTime = localtime(&currentTime);
    sprintf(formattedString, "%02d:%02d %s %d %s %d", localTime->tm_hour,
            localTime->tm_min, dayNames[localTime->tm_wday], localTime->tm_mday,
            monthNames[localTime->tm_mon], localTime->tm_year + 1900);

    s = DefaultScreen(d);
    w = XCreateSimpleWindow(d, RootWindow(d, s), 0, 0, SCREEN_W, SCREEN_H, 0, 0,
                            BlackPixel(d, s));

    XSetWindowAttributes attr;
    attr.override_redirect = True;
    XChangeWindowAttributes(d, w, CWOverrideRedirect, &attr);

    XSizeHints hints;
    hints.flags = PMinSize | PMaxSize;
    hints.min_width = hints.max_width = SCREEN_W;
    hints.min_height = hints.max_height = SCREEN_H;
    XSetWMNormalHints(d, w, &hints);

    XSelectInput(d, w, ExposureMask | KeyPressMask);
    XMapWindow(d, w);

    GC gcWhite = XCreateGC(d, w, 0, NULL);
    XSetForeground(d, gcWhite, WhitePixel(d, s));

    Colormap colormap = DefaultColormap(d, s);
    XColor color;
    XParseColor(d, colormap, blue, &color);
    XAllocColor(d, colormap, &color);

    GC gcBlue = XCreateGC(d, w, 0, NULL);
    XSetForeground(d, gcBlue, color.pixel);

    while (1) {
        XNextEvent(d, &e);

        if (e.type == Expose) {

            if (strlen(name) < 1) {
                screenItems = obtenerPrimerosN(&items, ROWS);
                executable = NULL;
            } else {
                screenItems = obtenerPrimerosNconPrefijo(&items, ROWS, name);
                executable = front(&screenItems);
            }

            XClearWindow(d, w);
            XDrawString(d, w, gcWhite, 7, 5, name, strlen(name));
            XFillRectangle(d, w, gcBlue, 0, SCREEN_H - 15, SCREEN_W, 16);
            XDrawString(d, w, gcWhite, 7, SCREEN_H - 3, formattedString,
                        strlen(formattedString));
            drawItems(&screenItems, row, d, w, gcWhite, gcBlue);
        }
        if (e.type == KeyPress) {

            char buffer[10];
            KeySym keysym;
            XLookupString(&e.xkey, buffer, sizeof(buffer), &keysym, NULL);
            printf("%d\n", buffer[0]);

            if (buffer[0] == 27)
                break;

            if (buffer[0] == 13) {
                printf("ENTER");
                notEscape = true;
                break;
            }

            if (keysym == XK_Down) {
                if (row + 1 <= ROWS - 1)
                    row++;
            }

            if (keysym == XK_Up) {
                if (row - 1 >= 0)
                    row--;
            }

            if (buffer[0] == 8) {
                letterCount--;
                if (letterCount < 0)
                    letterCount = 0;
                name[letterCount] = '\0';
            }

            if (((int)buffer[0] >= 32) && ((int)buffer[0] <= 125) &&
                (letterCount < MAX_INPUT_CHARS)) {
                name[letterCount] = (char)buffer[0];
                name[letterCount + 1] = '\0';
                letterCount++;
            }

            if (strlen(name) < 1) {
                screenItems = obtenerPrimerosN(&items, ROWS);
                executable = NULL;
            } else {
                screenItems = obtenerPrimerosNconPrefijo(&items, ROWS, name);
                executable = front(&screenItems);
            }
            XClearWindow(d, w);
            drawItems(&screenItems, row, d, w, gcWhite, gcBlue);
            XDrawString(d, w, gcWhite, 7, 12, name, strlen(name));
            XFillRectangle(d, w, gcBlue, 0, SCREEN_H - 15, SCREEN_W, 16);
            XDrawString(d, w, gcWhite, 7, SCREEN_H - 3, formattedString,
                        strlen(formattedString));
        }
    }

    XCloseDisplay(d);
    printf("Hola bobi");

    if (executable != NULL && notEscape) {
        printf("ENTRO");
        strcpy(process, PATH);
        strcat(process, executable);

        clearStringList(&items);
        clearStringList(&screenItems);
        pid = fork();
        if (pid == 0) {
            printf("%s\n", process);
            printf("HOLA\n");
            int e = execl(process, process, NULL);
            printf("%d\n", e);
        } else {
            wait(NULL);
        }
    }

    clearStringList(&items);
    clearStringList(&screenItems);

    return 0;
}
