
#include <assert.h>
#include "../include/canvas.h"
#include "../include/window.h"
#include "../include/colors.h"

int main(void)
{
	open_display();
	init_canvas();
	
	assert(canv_width >= DEFAULT_MIN_WIDTH
	       && canv_height >= DEFAULT_MIN_HEIGHT);
	
	del_canvas();
	close_display();
	
	return 0;
}

