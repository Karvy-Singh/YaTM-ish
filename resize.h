#ifndef resize_h
#define resize_h
#include <stdio.h>
#include <stdlib.h>
#include <X11/Xlib.h>
#include <X11/Xatom.h>
#include "resize.h"

int resize(int window_id,int x, int y, int width, int height);

#endif
