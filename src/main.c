#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/XKBlib.h>
#include <X11/Xft/Xft.h>

#include "../include/window.h"
#include "../include/graphics.h"
#include "../include/colors.h"

#define PROG_NAME "paint programn"
#define LOG(msg, ...) do {						\
		char str[1024];						\
		sprintf(str, msg __VA_OPT__(,) __VA_ARGS__);		\
		fprintf(stdout, "[INFO] %s\n", str);			\
	} while (0)

#define SWAP(a, b) do {					\
		typeof(a) temp = b;			\
		b = a;					\
		a = temp;				\
	} while (0)

#define RESIZE_PIXMAP 0
#define RESIZE_REQUEST 0

Window main_win;

void run(void)
{
	XEvent ev;
	int holding = 0, prev_x = 0, prev_y = 0, erase = 0;
	enum IND_COLORS curr = DEFAULT_INITIAL_COLOR;
	enum IND_COLORS swap = DEFAULT_SWAP_COLOR;
	
	assert(dp != NULL && "Need a display to run the app");
	assert(src != -1 && "Need a display to run the app");

	Atom wm_delete_window = XInternAtom(dp, "WM_DELETE_WINDOW", False);
	XSetWMProtocols(dp, main_win, &wm_delete_window, 1);
	
	int width, height;
	win_size(main_win, &width, &height);
	
	KeySym keysym;
	Pixmap pixm = XCreatePixmap(dp, main_win, width, height, DefaultDepth(dp, src));
	XSetForeground(dp, gc, COLORS[WHITE].pixel);
	XFillRectangle(dp, pixm, gc, 0, 0, width, height);
	XSetForeground(dp, gc, COLORS[curr].pixel);
	while (XNextEvent(dp, &ev) == 0) {
		switch (ev.type) {
		case ButtonPress:
			if (ev.xbutton.button == Button1) {
				LOG("Drawing %i - %i", ev.xbutton.x, ev.xbutton.y);
				XDrawPoint(dp, pixm, gc, ev.xbutton.x, ev.xbutton.y);
			}
			holding = 1;
			break;
			
		case ButtonRelease:
			holding = 0;
			break;
			
		case MotionNotify:
			if (holding)
				XDrawLine(dp, pixm, gc, prev_x, prev_y,
					  ev.xbutton.x, ev.xbutton.y);
			prev_x = ev.xbutton.x;
			prev_y = ev.xbutton.y;
			break;

		case LeaveNotify:
			LOG("User leave for the moment");
			break;

		case ConfigureNotify:
			if (ev.xconfigure.width != width || ev.xconfigure.height != height) {
				LOG("Resizing %i - %i", ev.xconfigure.width, ev.xconfigure.height);
				Pixmap temp = XCreatePixmap(dp, main_win,
							    ev.xconfigure.width,
							    ev.xconfigure.height, DefaultDepth(dp, src));
				
				XSetForeground(dp, gc, COLORS[WHITE].pixel);
				XFillRectangle(dp, temp, gc, 0, 0, ev.xconfigure.width, ev.xconfigure.height);
				XSetForeground(dp, gc, COLORS[curr].pixel);
				
				XCopyArea(dp, pixm, temp, gc, 0, 0, width, height, 0, 0);
				XFreePixmap(dp, pixm);
				
				pixm = temp;
				width = ev.xconfigure.width;
				height = ev.xconfigure.height;
			}
			break;

		case ClientMessage:
			if ((Atom) ev.xclient.data.l[0] == wm_delete_window)
				return;
			break;
			
		case KeyPress:
			/* TODO: Create a switch here */
			keysym = XkbKeycodeToKeysym(dp, ev.xkey.keycode, 0, 0);
			switch (keysym) {
			case XK_equal:
				if (gc_vals.line_width < 100) {
					int lw = gc_vals.line_width;
					XFreeGC(dp, gc);
					create_graphics_contex(&COLORS[curr], lw + 1);
					LOG("Increasing pincel size %i", gc_vals.line_width);
				}
				break;
			case XK_minus:
				if (gc_vals.line_width > 2) {
					int lw = gc_vals.line_width;
					XFreeGC(dp, gc);
					create_graphics_contex(&COLORS[curr], lw - 1);
					LOG("Decreasing pincel size %i", gc_vals.line_width);
				}
				break;
			case XK_c:
				XSetForeground(dp, gc, COLORS[WHITE].pixel);
				XFillRectangle(dp, pixm, gc, 0, 0, width, height);
				XSetForeground(dp, gc, COLORS[curr].pixel);
				LOG("Cleaing the screen");
				break;
			case XK_x:
				LOG("Toglecolor color to %s", color_name(swap));
				XSetForeground(dp, gc, COLORS[swap].pixel);
				SWAP(curr, swap);
				break;

			case XK_s:
				LOG("Saving draw");
				break;
			case XK_e: {
				int lw = gc_vals.line_width;
				if (erase) {
					LOG("Erase mode deactive");
					XFreeGC(dp, gc);
					create_graphics_contex(&COLORS[curr], lw / 4);
					
				} else {
					LOG("Erase mode active");
					XFreeGC(dp, gc);
					create_graphics_contex(&COLORS[WHITE], lw * 4);
				}
				
				erase = !erase;
				}
				break;

			case XK_q:
				return;

				/* Swap colors */
			case XK_1: /* TODO: Put this code into a function */
				{
					int lw = gc_vals.line_width;
					swap = curr;
					curr = BLACK;
					LOG("Changing color %s", color_name(curr));
					XFreeGC(dp, gc);
					create_graphics_contex(&COLORS[curr], lw);
				}
				break;
				
			case XK_2:
				{
					int lw = gc_vals.line_width;
					swap = curr;
					curr = WHITE;
					LOG("Changing color %s", color_name(curr));
					XFreeGC(dp, gc);
					create_graphics_contex(&COLORS[curr], lw);
				}
				break;

			case XK_3:
				{
					int lw = gc_vals.line_width;
					swap = curr;
					curr = RED;
					LOG("Changing color %s", color_name(curr));
					XFreeGC(dp, gc);
					create_graphics_contex(&COLORS[curr], lw);
				}
				break;
				
			case XK_4:
				{
					int lw = gc_vals.line_width;
					swap = curr;
					curr = BLUE;
					LOG("Changing color %s", color_name(curr));
					XFreeGC(dp, gc);
					create_graphics_contex(&COLORS[curr], lw);
				}
				break;

			case XK_5:
				{
					int lw = gc_vals.line_width;
					swap = curr;
					curr = GREEN;
					LOG("Changing color %s", color_name(curr));
					XFreeGC(dp, gc);
					create_graphics_contex(&COLORS[curr], lw);
				}
				break;

			case XK_6:
				{
					int lw = gc_vals.line_width;
					swap = curr;
					curr = YELLOW;
					LOG("Changing color %s", color_name(curr));
					XFreeGC(dp, gc);
					create_graphics_contex(&COLORS[curr], lw);
				}
				break;
				
			case XK_7:
				{
					int lw = gc_vals.line_width;
					swap = curr;
					curr = ORANGE;
					LOG("Changing color %s", color_name(curr));
					XFreeGC(dp, gc);
					create_graphics_contex(&COLORS[curr], lw);
				}
				break;
			}
		}

		/* Draw pixmap */
		if (holding || ev.type == ConfigureNotify
		    || (ev.type == KeyPress && keysym == XK_c)) {
			XClearWindow(dp, main_win);
			XCopyArea(dp, pixm, main_win, gc, 0, 0, width, height, 0, 0);
			XFlush(dp);
		}
		
	}
	XFreePixmap(dp, pixm);
}


int main(void)
{
	open_display();
	
	LOG("Display opened");
	main_win = create_window(DEFAULT_POSX, DEFAULT_POSY, DEFAULT_MIN_WIDTH,
				 DEFAULT_MIN_HEIGHT, DEFAULT_BORDER_WIDTH, PROG_NAME);
	LOG("Window id %lu", (unsigned long)  main_win);
	LOG("Window created");
	create_colors();

	create_graphics_contex(&COLORS[DEFAULT_INITIAL_COLOR], DEFAULT_LINE_WIDTH);
	LOG("Creating Graphics and Colors");
	LOG("Running the app");
	run();
	
	LOG("Finishing closing everything");
	
	XFreeGC(dp, gc);
	free_colors();
	close_display(main_win);
	LOG("Programn finished");
	
	return 0;
}



