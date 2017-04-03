#include <pebble.h>

// Returning a time structure on the curent time
tm* get_time();

// Returning Elapsed seconds between now and provided time;
int elapsed(time_t past);

// Moving GRect from constraints
void atLeft(GRect left, GRect *at);
void atRight(GRect right, GRect *at);
void atTop(GRect top, GRect *at);
void atBottom(GRect bottom, GRect *at);
void alignLeft(GRect left, GRect *align );
void alignTop(GRect top, GRect *align );
void alignRight(GRect right, GRect *align );
void alignBottom(GRect bottom, GRect *align );
void translate(GSize vector, GRect *moved);
void inCenterHrz(GRect center, GRect *in );
void inCenterVrt(GRect center, GRect *in );
void inBetweenHrz(GRect left, GRect right, GRect *in );
void inBetweenVrt(GRect top, GRect bottom, GRect *in );

// Create GRect ...
GRect GRectFromSize(GSize size);
GRect GRectFromPoint(GPoint point);
GRect GRectFromText(char* text, GFont font, GRect box);
