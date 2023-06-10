#include <assert.h>
#include "../include/canvas.h"
#include "../include/window.h"
#include "../include/colors.h"
#include "../include/tools.h"
#include "../include/utils.h"

int main(void)
{
	open_display();
	init_canvas();
	
	assert(canv_width >= DEFAULT_MIN_WIDTH
	       && canv_height >= DEFAULT_MIN_HEIGHT);

	GC gc;
	XGCValues vals = {0};
	unsigned long valuemask;
	
	vals.line_style = LineSolid;
	vals.line_width = 5;
	vals.cap_style = CapButt;
	vals.fill_style = FillSolid;
	
	vals.foreground = COLORS[BLACK].pixel;
	vals.background = COLORS[WHITE].pixel;

	valuemask = GCForeground | GCBackground
		| GCFillStyle | GCLineStyle | GCLineWidth | GCCapStyle | GCJoinStyle;
	
	gc = XCreateGC(dp, root, valuemask, &vals);

	int quit = 0, holding = 0, prev_x, prev_y;

	Atom wm_delete_window = XInternAtom(dp, "WM_DELETE_WINDOW", False);
	XSetWMProtocols(dp, root, &wm_delete_window, 1);
	
	XEvent event;
	while (!quit) {
		XNextEvent(dp, &event);
		switch (event.type) {
		case ButtonPress:
			if (event.xbutton.button == Button1)
				draw_canvas(gc, event.xbutton.x, event.xbutton.y);
			holding = 1;
			break;
			
		case ButtonRelease:
			holding = 0;
			break;
			
		case MotionNotify:
			if (holding)
				draw_line_canvas(gc, prev_x, prev_y, event.xbutton.x, event.xbutton.y);
			prev_x = event.xbutton.x;
			prev_y = event.xbutton.y;
			break;
			
		case KeyPress:
			quit = 1;
			break;
		}
	}
	
	XFreeGC(dp, gc);
	
	del_canvas();
	close_display();
	
	return 0;
}
