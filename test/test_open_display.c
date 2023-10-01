/*
  This XOpenDisplay allocates a few chunks that are not freeded on XCloseDisplay
 */

#include <X11/Xlib.h>
#include <unittest.h>

TESTCASE(TestOpenDisplay) {
	/* Open the defualt dispaly */
	Display *dp = XOpenDisplay(NULL);

	TEST(OpenDisplay) {
		ASSERT(dp != NULL, "The display weren't able to open");
	}

	XCloseDisplay(dp);
} ENDTESTCASE
