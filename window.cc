#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <iostream>
#include <cstdlib>
#include <string>
#include <unistd.h>
#include "window.h"

using namespace std;

Xwindow::Xwindow(int width, int height) {

  d = XOpenDisplay(NULL);
  if (d == NULL) {
    cerr << "Cannot open display" << endl;
    exit(1);
  }
  s = DefaultScreen(d);
  w = XCreateSimpleWindow(d, RootWindow(d, s), 10, 10, width, height, 1,
                          BlackPixel(d, s), WhitePixel(d, s));
  XSelectInput(d, w, ExposureMask | KeyPressMask);
  XMapRaised(d, w);

  Pixmap pix = XCreatePixmap(d,w,width,
        height,DefaultDepth(d,DefaultScreen(d)));
  gc = XCreateGC(d, pix, 0,(XGCValues *)0);

  XFlush(d);
  XFlush(d);

  // Set up colours.
  XColor xcolour;
  Colormap cmap;
  char color_vals[5][10]={"white", "black", "red", "green", "blue"};

  cmap=DefaultColormap(d,DefaultScreen(d));
  for(int i=0; i < 5; ++i) {
      XParseColor(d,cmap,color_vals[i],&xcolour);
      XAllocColor(d,cmap,&xcolour);
      colours[i]=xcolour.pixel;
  }

  Pixmap bitmap;
    /* these variables will contain the dimensions of the loaded bitmap. */
    unsigned int bitmap_width, bitmap_height;
    /* these variables will contain the location of the hotspot of the   */
    /* loaded bitmap.                                                    */
    int hotspot_x, hotspot_y;

    /* load the bitmap found in the file "icon.bmp", create a pixmap     */
    /* containing its data in the server, and put its ID in the 'bitmap' */
    /* variable.                                                         */
    int rc = XReadBitmapFile(d, w,
                             "<your chess piece>.bmp",
                             &bitmap_width, &bitmap_height,
                             &bitmap,
                             &hotspot_x, &hotspot_y);
/*
  void drawChessPiece(map<char, Pixmap> &pieceMap) {
    // Retrieve the pixmap from the map
    Pixmap& bitmap = pieceMap[char];
    // Store the width and height
    int bitmapWidth = width;
    int bitmapHeight = height;

  }
*/

  XSetForeground(d,gc,colours[Black]);

  // Make window non-resizeable.
  XSizeHints hints;
  hints.flags = (USPosition | PSize | PMinSize | PMaxSize );
  hints.height = hints.base_height = hints.min_height = hints.max_height = height;
  hints.width = hints.base_width = hints.min_width = hints.max_width = width;
  XSetNormalHints(d, w, &hints);

  XSynchronize(d,True);

  usleep(1000);
}

Xwindow::~Xwindow() {
  XFreeGC(d, gc);
  XCloseDisplay(d);
}

void Xwindow::fillRectangle(int x, int y, int width, int height, int colour) {
  XSetForeground(d, gc, colours[colour]);
  XFillRectangle(d, w, gc, x, y, width, height);
  XSetForeground(d, gc, colours[Black]);
}

void Xwindow::drawString(int x, int y, string msg, int colour) {
  XFontStruct * f = XLoadQueryFont(d, "6x13");
	
	printMessage(x, y, msg, colour, *f); 

	delete f;
}


void Xwindow::drawStringFont(int x, int y, string msg, string font, int colour) {
  XFontStruct * f = XLoadQueryFont(d, font.c_str());
  
	if ( f == nullptr ){
		f = XLoadQueryFont(d, "6x13");
	}

	printMessage(x, y, msg, colour, *f);
	delete f;
}
