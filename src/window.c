#include "../include/window.h"
#include "../include/colors.h"

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xatom.h>
#include <X11/Xft/Xft.h>
#include <err.h>

#include <assert.h>


Display *dp = NULL;
int src = -1;
Window root = {0};
Visual *vis = NULL;

Window create_window(int x, int y, int w, int h, int bw, const char *win_name)
{
	Window win;
	XSetWindowAttributes watt;
	assert(dp != NULL && "To execute this thing you need to open a display");
	assert(src != -1 && "You must to have an screen number");
	
	watt.background_pixel = WhitePixel(dp, src);
	watt.border_pixel = BlackPixel(dp, src);

	#if 1
	watt.event_mask = Button1MotionMask | ButtonPressMask | ButtonReleaseMask
		  | KeyPressMask | PointerMotionMask | StructureNotifyMask;
	#else
	watt.event_mask = Button1MotionMask | ButtonPressMask | ButtonReleaseMask
		| KeyPressMask | PointerMotionMask;
	#endif
	
	win = XCreateWindow(dp, root, x, y, w, h, bw,
			    DefaultDepth(dp, src), InputOutput,  vis,
			    CWBackPixel | CWBorderPixel | CWEventMask, &watt);

	XSizeHints xsh = {
		.min_width = DEFAULT_MIN_WIDTH,
		.min_height = DEFAULT_MIN_HEIGHT,
		.max_width = DEFAULT_MAX_WIDTH,
		.max_height = DEFAULT_MAX_HEIGHT
	};

	xsh.flags = PMinSize | PMaxSize;
	XSetSizeHints(dp, win, &xsh, XA_WM_NORMAL_HINTS);
	
	XStoreName(dp, win, win_name);
	XMapWindow(dp, win);
	return win;
}

void open_display(void)
{
	dp = XOpenDisplay(NULL); /* Open the defualt dispaly */
	if (dp == NULL) errx(1, "The display should be open can't be null");
	
	src = DefaultScreen(dp);
	root = RootWindow(dp, src);
	vis = DefaultVisual(dp, src);
}

void close_display(Window win)
{
	assert(dp != NULL && "The display should be open can't be null");

	XUnmapWindow(dp, win);
	XDestroyWindow(dp, win);
	XCloseDisplay(dp);
}

