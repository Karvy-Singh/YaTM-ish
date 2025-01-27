
#include <stdio.h>
#include <stdlib.h>
#include <X11/Xlib.h>
#include <X11/Xatom.h>
#include "resize.h"

int resize(int window_id,int x, int y, int width, int height) {
    char command[256];
    int ret;

    // Prepare the command to run the script with the value
    snprintf(command, sizeof(command), "./resize.sh %d", window_id);

    // Execute the script
    ret = system(command);
    Display *display = XOpenDisplay(NULL);
      if (display == NULL) {
          printf("Unable to open X display\n");
          return 1;
      }

    if (XMoveResizeWindow(display, window_id,x,y, width, height) == 0) {
        printf("Failed to resize window\n");
        XCloseDisplay(display);
        return 1;
    }

    XRaiseWindow(display, window_id);

    // Flush the X server
    XFlush(display);

    // Clean up
    XCloseDisplay(display);
    return 0;
}




