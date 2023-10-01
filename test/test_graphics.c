#include <assert.h>
#include <unittest.h>

#include "../include/canvas.h"
#include "../include/window.h"
#include "../include/colors.h"
#include "../include/graphics.h"
#include "../include/tools.h"
// #include "../include/utils.h"

TESTCASE(TestingGraphics) {
	open_display();
	init_canvas();

	/* Create the neccessary variables */
	GC gc;
	XEvent event;
	
	TEST(TestCanvas) {
		ASSERT(canv_width >= DEFAULT_MIN_WIDTH
		       && canv_height >= DEFAULT_MIN_HEIGHT);
	}

	/* Then Test the graphics */
	TEST(TestCreateGraphics) {
		gc = create_graphics_contex(BLACK, DEFAULT_INITIAL_BRUSH_WIDTH);

		while (1) {
			XNextEvent(dp, &event);

			/* Wait for the exposure */
			if (event.type == Expose) {
				/* Draw the line */
				draw_line_canvas(gc, 100, 100, 500, 500);
				refresh_canvas();
				sleep(2);
				break;
			}
		}
		

		ASSERT(XFreeGC(dp, gc), "It Must return 1");
	}
	
	
	del_canvas();
	close_display();
} ENDTESTCASE


  /* int quit = 0, holding = 0, prev_x, prev_y; */

  /* Atom wm_delete_window = XInternAtom(dp, "WM_DELETE_WINDOW", False); */
  /* XSetWMProtocols(dp, root, &wm_delete_window, 1); */
	
  /* XEvent event; */
  /* while (!quit) { */
  /* 	XNextEvent(dp, &event); */
  /* 	switch (event.type) { */
  /* 	case ButtonPress: */
  /* 		if (event.xbutton.button == Button1) */
  /* 			draw_canvas(gc, event.xbutton.x, event.xbutton.y); */
  /* 		holding = 1; */
  /* 		break; */
			
  /* 	case ButtonRelease: */
  /* 		holding = 0; */
  /* 		break; */
			
  /* 	case MotionNotify: */
  /* 		if (holding) */
  /* 			draw_line_canvas(gc, prev_x, prev_y, event.xbutton.x, event.xbutton.y); */
  /* 		prev_x = event.xbutton.x; */
  /* 		prev_y = event.xbutton.y; */
  /* 		break; */
			
  /* 	case KeyPress: */
  /* 		quit = 1; */
  /* 		break; */
  /* 	} */
  /* } */
