#include <pebble.h>

// Returning a time structure on the curent time
tm* get_time();

// Returning Elapsed seconds between now and provided time;
int elapsed(time_t past);

// Returning index from range Array
int indexOf( int values[], int nb, int value);

// Create GRect ...
GRect GRectFromSize(GSize size);
GRect GRectFromPoint(GPoint point);
GRect GRectFromText(char* text, GFont font, GRect box);


// Mode defined & mixed values
#define Horizontal 1
#define Vertical 2

#define Top 1
#define Bottom 2
#define Left 4
#define Right 8
// Moving GRect from constraints
void translate(int Mode, int  offset, GRect *moved);
void at(int Mode, GRect anchor, GRect *moved);
void align(int Mode, GRect anchor, GRect *aligned);
void atCenter(int Mode, GRect center, GRect *centered);
void inMiddle( int Mode, GRect first, GRect second, GRect *middle);
void remainsAt(int Mode, GRect outer, GRect inner, GRect *free);
