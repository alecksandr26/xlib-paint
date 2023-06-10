#ifndef TOOLS_INCLUDED
#define TOOLS_INCLUDED

#include <X11/Xlib.h>
#include "../include/colors.h"

#define DEFAULT_INITIAL_TOOL PAINT_BRUSH
#define DEFAULT_INITIAL_BRUSH_WIDTH 5
#define DEFAULT_INITIAL_ERASE_WIDTH 25
#define DEFAULT_INITIALIZED_BOOL 1
#define STATE(tool) ((struct __st_tool_state *) (tool))

typedef enum {
	PAINT_BRUSH,
	ERASER
} TOOL;

struct __st_tool_state {
	int holding, prev_x, prev_y, width;
	GC graphics_contex;
	TOOL curr;
};

typedef struct {
	struct __st_tool_state state;
	COLOR curr, swap;
} PaintBrush;

typedef struct {
	struct __st_tool_state state;
	COLOR erase_color;
} Eraser;

typedef union {
	PaintBrush pbrush;
	Eraser eraser;
} Tool;

extern void init_tool(Tool *tool);
extern void free_tool(Tool *tool);
extern void sel_tool(Tool *tool, TOOL sel_t);
extern void tool_draw(Tool *tool, int x, int y);
extern void mod_tool(Tool *tool, int width, COLOR color);
#endif
