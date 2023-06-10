#include <assert.h>

#include <X11/Xlib.h>

#include "../include/tools.h"
#include "../include/graphics.h"
#include "../include/canvas.h"
#include "../include/utils.h"
#include "../include/window.h"

void init_tool(Tool *tool)
{
	assert(tool != NULL && "Can't be null the tool");
	STATE(tool)->holding = STATE(tool)->prev_x = STATE(tool)->prev_y = 0;
}

void free_tool(Tool *tool)
{
	free_graphics_contex(STATE(tool)->graphics_contex);
}

void sel_tool(Tool *tool, TOOL sel_tl)
{
	assert(tool != NULL && "Can't be null the tool");
	STATE(tool)->curr = sel_tl;
	
	if (STATE(tool)->graphics_contex != 0)
		XFreeGC(dp, STATE(tool)->graphics_contex);

	switch (sel_tl) {
	case PAINT_BRUSH:
		tool->pbrush.curr = BLACK;
		tool->pbrush.swap = WHITE;
		STATE(tool)->width = DEFAULT_INITIAL_BRUSH_WIDTH;
		STATE(tool)->graphics_contex = create_graphics_contex(BLACK, DEFAULT_INITIAL_BRUSH_WIDTH);
		break;
		
	case ERASER:
		tool->eraser.erase_color = WHITE;
		STATE(tool)->width = DEFAULT_INITIAL_ERASE_WIDTH;
		STATE(tool)->graphics_contex = create_graphics_contex(WHITE, DEFAULT_INITIAL_ERASE_WIDTH);
		break;
	}
}

void mod_tool(Tool *tool, int width, COLOR color)
{
	switch (STATE(tool)->curr) {
	case PAINT_BRUSH:
		if (color != NONE_COLOR) {
			tool->pbrush.swap = tool->pbrush.curr;
			tool->pbrush.curr = color;
		}

		STATE(tool)->width = width;
		mod_graphics_contex(STATE(tool)->graphics_contex,
				    color, width);
		break;
		
	case ERASER:
		STATE(tool)->width = width;
		mod_graphics_contex(STATE(tool)->graphics_contex,
				    color, width);

		break;
	}
}

void tool_draw(Tool *tool, int x, int y)
{
	switch (STATE(tool)->curr) {
	case PAINT_BRUSH:
	case ERASER:
		if (STATE(tool)->holding)
			draw_line_canvas(STATE(tool)->graphics_contex,
					 STATE(tool)->prev_x, STATE(tool)->prev_y, x, y);
		else
			draw_canvas(STATE(tool)->graphics_contex, x, y);
		break;
	}

	STATE(tool)->prev_x = x;
	STATE(tool)->prev_y = y;
}

