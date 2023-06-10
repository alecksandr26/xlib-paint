/*
  This XOpenDisplay allocates a few chunks that are not freeded on XCloseDisplay
 */

#include <X11/Xlib.h>
#include <err.h>

int main(void)
{
	Display *dp = XOpenDisplay(NULL); /* Open the defualt dispaly */
	if (dp == NULL) errx(1, "The display should be open can't be null");

	XCloseDisplay(dp);
	return 0;
}
