#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include <X11/Xlib.h>
#include <X11/XKBlib.h>

#include "../include/window.h"
#include "../include/graphics.h"
#include "../include/colors.h"
#include "../include/tools.h"
#include "../include/canvas.h"
#include "../include/utils.h"
#include "../include/kbinds.h"

void loop(void)
{
	XEvent event;
	Tool tool = {0};
	
	assert(dp != NULL && "Need a display to run the app");
	assert(src != -1 && "Need a display to run the app");
	
	init_tool(&tool);
	sel_tool(&tool, DEFAULT_INITIAL_TOOL);
	
	KeySym keysym;
	int quit = 0;
	while (!quit) {
		XNextEvent(dp, &event);
		switch (event.type) {
		case ButtonPress:
			if (event.xbutton.button == Button1)
				tool_draw(&tool, event.xbutton.x, event.xbutton.y);
			STATE(&tool)->holding = 1;
			break;
			
		case ButtonRelease:
			STATE(&tool)->holding = 0;
			break;
			
		case MotionNotify:
			if (STATE(&tool)->holding)
				tool_draw(&tool, event.xbutton.x, event.xbutton.y);
			break;

		case LeaveNotify:
			LOG("User leave for the moment");
			break;
			
		case Expose:
			LOG("User arrive");
			break;

		case ConfigureNotify:
			assert(event.xconfigure.width >= DEFAULT_MIN_WIDTH
			       && event.xconfigure.height >= DEFAULT_MIN_HEIGHT
			       && "Checking the configuration");
			if (event.xconfigure.width != canv_width || event.xconfigure.height != canv_height)
				resize_canvas(event.xconfigure.width, event.xconfigure.height);
			break;

		case ClientMessage:
			if ((Atom) event.xclient.data.l[0] == wm_delete_window)
				quit = 1;
			break;
			
		case KeyPress:
			keysym = XkbKeycodeToKeysym(dp, event.xkey.keycode, 0, 0);
			handle_keypress(keysym, &tool, &quit);
			break;
		}

		/* Refresh the canvas */
		if (event.type == ButtonRelease
		    || event.type == Expose
		    || (event.type == KeyPress && keysym == XK_c))
			refresh_canvas();
	}

	/* Free the tools */
	free_tool(&tool);
}

int main(void)
{
	open_display();
	init_canvas();
	
	LOG("Running the app");
	loop();
	
	del_canvas();
	close_display();
	LOG("Quiting");

	return 0;
}



