
#include <X11/Xlib.h>
#include <X11/Xutil.h>

#include <stdio.h>

#define BITMAPDEPTH 1
#define MAX_COLORS 3

/* Display and screen_num are used as arguments to nearly every Xlib routine, 
 * so it simplifies routine calls to declare them global.  If there were 
 * additional source files, these variables would be declared extern in
 * them. */
Display *display;
int screen_num;

/* pixel values */
unsigned long foreground_pixel, background_pixel, border_pixel;

#define MAX_COLORS 3



void get_GC(Window win, GC *gc);
int get_colors();

int main(int argc,char **argv)
{
  Window win;
  unsigned int width, height, x, y; /* window size and position */
  unsigned int borderwidth = 4;	    /* four pixels */
  unsigned int display_width, display_height;
  XEvent report;
  GC gc;
  XGCValues values;
  int currentX=0,currentY=0;
  
  if ( (display=XOpenDisplay(NULL)) == NULL )
    {
      (void) fprintf( stderr, 
		     "basicwin: cannot connect to X server %s\\n");
      exit( -1 );
    }
  screen_num = DefaultScreen(display);
  display_width = DisplayWidth(display, screen_num);
  display_height = DisplayHeight(display, screen_num);
  x = display_width/3, y = display_height/3;
  width = display_width/3, height = display_height/4;
  get_colors();
  win = XCreateSimpleWindow(display, RootWindow(display,screen_num), x, y, 
			    width, height, borderwidth, border_pixel,
			    background_pixel);
  XSelectInput(display, win, ExposureMask | ButtonPressMask| 
	       Button1MotionMask);
  gc = XCreateGC(display, win, 0 , &values);
  XSetForeground(display, gc, foreground_pixel);
  XSetFunction(display, gc, GXxor);
  XMapWindow(display, win);
  while (1)  {
    XNextEvent(display, &report);
    switch  (report.type) {
    case Expose:
      XDrawLine(display, win, gc, 0, 0, currentX, currentY);
      break;
    case MotionNotify:
      XDrawLine(display, win, gc, 0, 0, currentX, currentY);		  
      currentX=report.xmotion.x;
      currentY=report.xmotion.y;
      XDrawLine(display, win, gc, 0, 0, currentX, currentY);		  
    default:
      break;
    } /* end switch */
  } /* end while */
}

int get_colors()
{
  char *visual_class[] = {
    "StaticGray",
    "GrayScale",
    "StaticColor",
    "PseudoColor",
    "TrueColor",
    "DirectColor"
  };
  int default_depth;
  Visual *default_visual;
  static char *name[] = {"Red", "Yellow", "Green"};
  XColor exact_def;
  Colormap default_cmap;
  int ncolors = 0;
  int colors[MAX_COLORS];
  int i = 5;
  XVisualInfo visual_info;
  
  /* Try to allocate colors for PseudoColor, TrueColor, 
     * DirectColor, and StaticColor.  Use black and white
     * for StaticGray and GrayScale */
  
  default_depth = DefaultDepth(display, screen_num);
  default_visual = DefaultVisual(display, screen_num);
  default_cmap   = DefaultColormap(display, screen_num);
  if (default_depth == 1) {
    /* must be StaticGray, use black and white */
    border_pixel = BlackPixel(display, screen_num);
    background_pixel = WhitePixel(display, screen_num);
    foreground_pixel = BlackPixel(display, screen_num);
    return(0);
  }
  
  while (!XMatchVisualInfo(display, screen_num, default_depth, /* visual class */i--, &visual_info))
    ;
 
  if (i < 2) {
    /* No color visual available at default_depth.
       * Some applications might call XMatchVisualInfo
       * here to try for a GrayScale visual 
       * if they can use gray to advantage, before 
       * giving up and using black and white.
    */
    border_pixel = BlackPixel(display, screen_num);
    background_pixel = WhitePixel(display, screen_num);
    foreground_pixel = BlackPixel(display, screen_num);
    return(0);
  }
  
  /* otherwise, got a color visual at default_depth */
  
  /* The visual we found is not necessarily the 
     * default visual, and therefore it is not necessarily
     * the one we used to create our window.  However,
     * we now know for sure that color is supported, so the
     * following code will work (or fail in a controlled way).
     * Let's check just out of curiosity: */ 
  for (i = 0; i < MAX_COLORS; i++) {
    printf("allocating %s\n", name[i]);
    if (!XParseColor (display, default_cmap, name[i], &exact_def)) {
      fprintf(stderr, "color name %s not in database", name[i]);
      exit(0);
    }
    printf("The RGB values from the database are %d, %d, %d\n", exact_def.red, exact_def.green, exact_def.blue);
    if (!XAllocColor(display, default_cmap, &exact_def)) {
      fprintf(stderr, "can't allocate color: all colorcells allocated and no matching cell found.\n");
      exit(0);
    }
    printf("The RGB values actually allocated are %d, %d, %d\n", exact_def.red, exact_def.green, exact_def.blue);
    colors[i] = exact_def.pixel;
    ncolors++;
  }
  border_pixel = colors[0];
  background_pixel = colors[1];
  foreground_pixel = colors[2]^background_pixel;
  return(1);
}
