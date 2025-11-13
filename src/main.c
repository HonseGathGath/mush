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
                                      BlackPixel(display, screen),
                                      WhitePixel(display, screen));
  printf("4. Window created\n");
  XStoreName(display, window, "mush");
  XClassHint *class_hint = XAllocClassHint();
  class_hint->res_name = "mush";
  class_hint->res_class = "mush";
  XSetClassHint(display, window, class_hint);
  XFree(class_hint);

  XSelectInput(display, window, ExposureMask | KeyPressMask);

  printf("5. Mapping window...\n");
  XMapWindow(display, window);
  printf("6. Window mapped - should be visible now\n");

  XEvent event;
  int window_mapped = 0;
  int attempts = 0;

  while (!window_mapped && attempts < 10) {
    XNextEvent(display, &event);
    if (event.type == MapNotify) {
      window_mapped = 1;
      printf("Window is now visible!\n");
    } else {
      attempts++;
    }
  }

  XSetInputFocus(display, window, RevertToParent, CurrentTime);

  GC gc = XCreateGC(display, window, 0, NULL);
  XSetForeground(display, gc, BlackPixel(display, screen));

  printf(
      "Window should be visible now. Press any key in the window to exit.\n");

  int running = 1;
  while (running) {
    XNextEvent(display, &event);

    switch (event.type) {
    case Expose:
      XDrawString(display, window, gc, 50, 50, "mush Shell - Press any key",
                  26);
      break;

    case KeyPress:
      running = 0;
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
