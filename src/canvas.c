
#include <X11/Xlib.h>
#include "../include/canvas.h"
#include "../include/window.h"
#include "../include/graphics.h"
#include "../include/utils.h"

int canv_width, canv_height;
static Window window;
static Pixmap pixm;
static GC canv_gc;

void init_canvas(void)
{
	LOG("Initializing canvas");
	create_colors();
	window = create_window(DEFAULT_POSX, DEFAULT_POSY, DEFAULT_MIN_WIDTH,
			       DEFAULT_MIN_HEIGHT, "Canvas");

	canv_gc = create_graphics_contex(WHITE, DEFAULT_MIN_WIDTH);

	win_size(window, &canv_width, &canv_height);
	pixm = XCreatePixmap(dp, window, canv_width, canv_height, DefaultDepth(dp, src));
	XFillRectangle(dp, pixm, canv_gc, 0, 0, canv_width, canv_height);

	LOG("Canvas initialized");
}

void draw_canvas(GC gc, int x, int y)
{
	
	LOG("Drawing %i - %i", x, y);
	XDrawPoint(dp, pixm, gc, x, y);
	XDrawPoint(dp, window, gc, x, y);
}

void draw_line_canvas(GC gc, int src_x, int src_y, int des_x, int des_y)
{
	XDrawLine(dp, pixm, gc, src_x, src_y, des_x, des_y);
	XDrawLine(dp, window, gc, src_x, src_y, des_x, des_y);
}

void del_canvas(void)
{
	XFreeGC(dp, canv_gc);
	XFreePixmap(dp, pixm);
	destroy_window(window);
}

void refresh_canvas(void)
{
	XClearWindow(dp, window);
	XCopyArea(dp, pixm, window, canv_gc, 0, 0, canv_width, canv_height, 0, 0);
	XFlush(dp);

	LOG("Refreshing canvas %i - %i", canv_width, canv_height);

}

void resize_canvas(int new_width, int new_height)
{
	LOG("Resizing canvas %i - %i", new_width, new_height);
	Pixmap temp = XCreatePixmap(dp, window, new_width, new_height, DefaultDepth(dp, src));
	
	XSetForeground(dp, canv_gc, COLORS[WHITE].pixel);
	XFillRectangle(dp, temp, canv_gc, 0, 0, new_width, new_height);
				
	XCopyArea(dp, pixm, temp, canv_gc, 0, 0, canv_width, canv_height, 0, 0);
	XFreePixmap(dp, pixm);
				
	pixm = temp;
	canv_width = new_width;
	canv_height = new_height;
}


void clear_canvas(void)
{
	XFillRectangle(dp, pixm, canv_gc, 0, 0, canv_width, canv_height);
	XFillRectangle(dp, window, canv_gc, 0, 0, canv_width, canv_height);
	
	LOG("Cleaing the canvas");
}
