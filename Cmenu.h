#ifndef GAME_H
#define GAME_H

#include "list.h"
#include <dirent.h>
#include <stdbool.h>
#include <time.h>

void getPrograms(StringList *, const char *);

#define MAX_INPUT_CHARS 65

static const int SCREEN_W = 500;
static const int SCREEN_H = 320;
static const int FONT_SIZE = 13;
static const char PATH[] = "/bin/";
static const int FPS = 10;
// static const int MAX_INPUT_CHARS = 250;
static const int RECTANGLE_H = 16;
static const float DRAW_LILST = 18;
static const int ROWS = 19;
static const char blue[] = "#0000FF";

static const char *dayNames[] = {"Sun", "Mon", "Tue", "Wed",
                                 "Thu", "Fri", "Sat"};
static const char *monthNames[] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun",

                                   "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};

void getPrograms(StringList *, const char *);

#endif // !GAME_H
