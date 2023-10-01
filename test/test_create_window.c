/*
  This XOpenDisplay allocates a few chunks that are not freeded on XCloseDisplay
*/

#include <X11/Xlib.h>
#include <unittest.h>

#include "../include/colors.h"
#include "../include/window.h"

TESTCASE(TestCreateWindow) {
	/* Initialize the window */
	Window win = 0;
	
	/* Open the defualt dispaly */
	dp = XOpenDisplay(NULL);

	src = DefaultScreen(dp);
	root = RootWindow(dp, src);
	vis = DefaultVisual(dp, src);
	
	TEST(CreateWindow) {
		win = create_window(0, 0, 500, 500, "window");
		ASSERT(win != 0, "Failed creating the window");
		destroy_window(win);
	}
	
	XCloseDisplay(dp);
} ENDTESTCASE

