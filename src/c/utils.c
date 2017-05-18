#include "utils.h"
//#################################################################################
tm* get_time(){
	time_t rawtime;
	time(&rawtime);
	return localtime(&rawtime);
}
//#################################################################################
int elapsed(time_t past) {
	time_t now;
	time(&now);
	return now - past;
}
//#################################################################################
int indexOf( int values[], int nb, int value) {
	int index = nb - 1;
	for (int i = nb - 1; i >= 0 ; i--)
		if (value < values[i] ) index = i;
	return index ;
}
//#################################################################################
GRect GRectFromSize(GSize size) {
	return GRect(0,0, size.w, size.h);
}
//#################################################################################
GRect GRectFromPoint(GPoint point) {
	return GRect(point.x, point.y, 0,0);
}
//#################################################################################
GRect GRectFromText(char* text, GFont font, GRect box) {
	GSize size = graphics_text_layout_get_content_size
				( 	text,\
					font,\
					box,\
					GTextOverflowModeWordWrap, \
					GTextAlignmentCenter \
				);
	return GRect(0,0, size.w, size.h);
}
//#################################################################################
void translate(int Mode, int  offset, GRect *moved) {
	if (Mode & Horizontal) moved->origin.x = moved->origin.x + offset;
	if (Mode & Vertical) moved->origin.y = moved->origin.y + offset;
}
//#################################################################################
void at(int Mode, GRect anchor, GRect *moved) {
	if (Mode & Left) moved->origin.x = anchor.origin.x - moved->size.w ;
	if (Mode & Right) moved->origin.x = anchor.origin.x + anchor.size.w ;
	if (Mode & Top) moved->origin.y = anchor.origin.y - moved->size.h ;
	if (Mode & Bottom) moved->origin.y = anchor.origin.y + anchor.size.h;
}
//#################################################################################
void align(int Mode, GRect anchor, GRect *aligned) {

	if (Mode & Left)  aligned->origin.x = anchor.origin.x ;
	if (Mode & Right) aligned->origin.x = anchor.origin.x + anchor.size.w - aligned->size.w ;
	if (Mode & Top) aligned->origin.y = anchor.origin.y ;
	if (Mode & Bottom) aligned->origin.y =  anchor.origin.y + anchor.size.h - aligned->size.h ;
}
//#################################################################################
void atCenter(int Mode, GRect anchor, GRect *centered) {
	if (Mode & Horizontal) centered->origin.x = anchor.origin.x + (( anchor.size.w - centered->size.w) / 2);
	if (Mode & Vertical) centered->origin.y = anchor.origin.y + (( anchor.size.h - centered->size.h) / 2);
}
//#################################################################################
void inMiddle( int Mode, GRect first, GRect second, GRect *middle) {
	if (Mode & Horizontal) middle->origin.x = (first.origin.x + first.size.w + second.origin.x - middle->size.w) / 2;
	if (Mode & Vertical) middle->origin.y = (first.origin.y + first.size.h + second.origin.y - middle->size.h) / 2;
}
//#################################################################################
void remainsAt(int Mode, GRect outer, GRect inner, GRect *free) {
	free->origin = outer.origin;
	free->size = outer.size;

	if (Mode & Left) {
		free->size.w = outer.origin.x - inner.origin.x;
	}
	if (Mode & Right) {
		free->origin.x = inner.origin.x + inner.size.w;
		free->size.w = (outer.origin.x + outer.size.w) - free->origin.x;
	}
	if (Mode & Top) {
		free->size.w = outer.origin.y - inner.origin.x;
	}
	if (Mode & Bottom) {
		free->origin.y = inner.origin.y + inner.size.h;
		free->size.h = (outer.origin.y + outer.size.h) - free->origin.y;
	}
}
//#################################################################################
