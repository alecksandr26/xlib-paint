
#include <unittest.h>

#include "../include/canvas.h"
#include "../include/window.h"
#include "../include/colors.h"



TESTCASE(InitCanvasTestCase) {
	open_display();
	
	TEST(TestCanvas) {
		init_canvas();
		
		ASSERT(canv_width >= DEFAULT_MIN_WIDTH && canv_height >= DEFAULT_MIN_HEIGHT,
		       "The Canvas Should be oppend with that dimensions");
	
		del_canvas();
	}

	close_display();
} ENDTESTCASE

