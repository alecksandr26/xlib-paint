#include <unittest.h>
#include <stdio.h>

#undef TEST_DIR
#define TEST_DIR "test/"

#undef TEST_OUT
#define TEST_OUT "testrunner.out"

int main(void)
{
#undef UNITTEST_RECOMPILE
#define UNITTEST_RECOMPILE 1

	INCLUDE_TEST_CASE("test_graphics.c", TestingGraphics);
	INCLUDE_TEST_CASE("test_canvas.c", InitCanvasTestCase);
	INCLUDE_TEST_CASE("test_create_window.c", TestCreateWindow);
	INCLUDE_TEST_CASE("test_open_display.c", TestOpenDisplay);
	
	
	ATTACH_EXTRA_COMPILE_FLAGS("-I/usr/include/freetype2 -DTESTING_PAINT");
	ATTACH_EXTRA_LINKING_FLAGS("build/lib/libpaint.a -lX11 -lXft");
	
	RUN();
	return 0;
}




