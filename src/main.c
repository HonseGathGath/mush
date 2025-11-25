#include <X11/X.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/keysym.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
  printf("1. Opening display...\n");
  Display *display = XOpenDisplay(NULL);
  if (!display) {
    fprintf(stderr, "ERROR in creating display!");
  }
  printf("2. Display opened successfully\n");

  int screen = DefaultScreen(display);
  Window root = RootWindow(display, screen);

  printf("3. creating window...\n");
  Window window = XCreateSimpleWindow(display, root, 100, 50, 800, 600, 2,
                                      WhitePixel(display, screen),
                                      BlackPixel(display, screen));
  printf("4. Window created\n");
  XStoreName(display, window, "mush");
  XClassHint *class_hint = XAllocClassHint();
  class_hint->res_name = "mush";
  class_hint->res_class = "mush";
  XSetClassHint(display, window, class_hint);
  XFree(class_hint);

  XSelectInput(display, window,
               ExposureMask | KeyPressMask | StructureNotifyMask);

  printf("5. Mapping window...\n");
  XMapWindow(display, window);
  printf("6. Window mapped - should be visible now\n");

  GC gc = XCreateGC(display, window, 0, NULL);
  XSetForeground(display, gc, BlackPixel(display, screen));

  XEvent event;
  int window_mapped = 0;

  while (!window_mapped) {
    XNextEvent(display, &event);
    if (event.type == MapNotify) {
      window_mapped = 1;
      printf("Window is now visible!\n");
    }
  }

  XSetInputFocus(display, window, RevertToParent, CurrentTime);

  printf(
      "Window should be visible now. Press any key in the window to exit.\n");

  int quit = 1;
  while (quit) {
    XNextEvent(display, &event);

    switch (event.type) {
    case Expose:

      XDrawString(display, window, gc, 50, 50, "mush-$", 6);
      break;

    case KeyPress:
      quit = 0;
      break;

    case ConfigureNotify:
      printf("Window moved/resized\n");
      break;
    }
  }

  XFreeGC(display, gc);
  XCloseDisplay(display);

  return EXIT_SUCCESS;
}
