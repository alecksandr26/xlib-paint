#include <X11/Xlib.h>
#include <X11/Xutil.h>

#include "../include/kbinds.h"
#include "../include/tools.h"
#include "../include/utils.h"
#include "../include/canvas.h"

static COLOR prev_curr, prev_swap, prev_width;

void handle_keypress(KeySym key, Tool *tool, int *quit)
{
	switch (key) {
	case XK_equal:
		if (STATE(tool)->width < 100) {
			mod_tool(tool, STATE(tool)->width + 1, NONE_COLOR);
			LOG("Increasing pincel size %i", STATE(tool)->width);
		}
		break;
	case XK_minus:
		if (STATE(tool)->width > 1) {
			mod_tool(tool, STATE(tool)->width - 1, NONE_COLOR);
			LOG("Increasing pincel size %i", STATE(tool)->width);
		}
		break;
	case XK_c:
		LOG("Clearing the window");
		clear_canvas();
		break;

	case XK_x:
		if (STATE(tool)->curr == PAINT_BRUSH) {
			LOG("Changnig brush color to  %s", color_name(tool->pbrush.swap));
			mod_tool(tool, STATE(tool)->width, tool->pbrush.swap);
		} else
			LOG("Can't switch if erasing mode is active");
		break;

	case XK_s:
		LOG("Saving feature not developed yet");
		break;

	case XK_e:
		if (STATE(tool)->curr == PAINT_BRUSH) {
			LOG("Switching tool to eraser");
			prev_curr = tool->pbrush.curr;
			prev_swap = tool->pbrush.swap;
			prev_width = STATE(tool)->width;
			sel_tool(tool, ERASER);
		} else {
			LOG("Switching tool to paint brush");
			sel_tool(tool, PAINT_BRUSH);
			tool->pbrush.curr = prev_swap;
			mod_tool(tool, prev_width, prev_curr);
		}
		break;

	case XK_q:
		*quit = 1;
		break;

	case XK_1:
	case XK_2:
	case XK_3:
	case XK_4:
	case XK_5:
	case XK_6:
	case XK_7:
	case XK_8:
		if (STATE(tool)->curr == PAINT_BRUSH)
			mod_tool(tool, STATE(tool)->width, (COLOR) key - XK_0 - 1);
		else
			LOG("Can't switch if erasing mode is active");
		break;
	}
}
