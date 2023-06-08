#include <X11/Xlib.h>

int main() {
    Display *display = XOpenDisplay(NULL);
    Window window = XCreateSimpleWindow(display, DefaultRootWindow(display),
                                        0, 0, 500, 500, 1,
                                        BlackPixel(display, DefaultScreen(display)),
                                        WhitePixel(display, DefaultScreen(display)));

    Pixmap pixmap = XCreatePixmap(display, window, 500, 500,
                                  DefaultDepth(display, DefaultScreen(display)));

    // Draw on the pixmap
    GC gc = XCreateGC(display, pixmap, 0, NULL);
    XSetForeground(display, gc, WhitePixel(display, DefaultScreen(display)));
    XFillRectangle(display, pixmap, gc, 0, 0, 500, 500);
    XSetForeground(display, gc, BlackPixel(display, DefaultScreen(display)));
    XDrawLine(display, pixmap, gc, 0, 0, 500, 500);

    // Copy the pixmap to the window
    XCopyArea(display, pixmap, window, gc, 0, 0, 500, 500, 0, 0);

    XMapWindow(display, window);
    XFlush(display);

    // Event loop
    XEvent event;
    while (1) {
        XNextEvent(display, &event);
        // Handle events here
    }

    // Clean up resources
    XFreePixmap(display, pixmap);
    XFreeGC(display, gc);
    XCloseDisplay(display);

    return 0;
}
