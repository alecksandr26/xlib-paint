/*
  This XOpenDisplay allocates a few chunks that are not freeded on XCloseDisplay
 */

#include <X11/Xlib.h>
#include <err.h>

#include "../include/colors.h"
#include "../include/window.h"

Window win;

int main(void)
{
	dp = XOpenDisplay(NULL); /* Open the defualt dispaly */
	if (dp == NULL) errx(1, "The display should be open can't be null");
	
	src = DefaultScreen(dp);
	root = RootWindow(dp, src);
	vis = DefaultVisual(dp, src);
	
	win = create_window(0, 0, 500, 500, "window");
	
	destroy_window(win);
	
	XCloseDisplay(dp);
	return 0;
}




