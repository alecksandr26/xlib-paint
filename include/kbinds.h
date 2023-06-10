#ifndef KBINDS_INCLUDED
#define KBINDS_INCLUDED

#include <X11/Xlib.h>

#include "../include/tools.h"

extern void handle_keypress(KeySym key, Tool *tool, int *quit);

#endif
