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
void atLeft(GRect left, GRect *at) {
	at->origin.x = left.origin.x - at->size.w ;
}
//#################################################################################
void atRight(GRect right, GRect *at) {
	at->origin.x = right.origin.x + right.size.w ;
}
//#################################################################################
void atTop(GRect top, GRect *at) {
	at->origin.y = top.origin.y - at->size.h ;
}
//#################################################################################
void atBottom(GRect bottom, GRect *at) {
	at->origin.y = bottom.origin.y + bottom.size.h;
}
//#################################################################################
void alignLeft(GRect left, GRect *align ) {
	align->origin.x = left.origin.x ;
}
//#################################################################################
void alignTop(GRect top, GRect *align ) {
	align->origin.y = top.origin.y ;
}
//#################################################################################
void alignRight(GRect right, GRect *align ) {
	align->origin.x = right.origin.x + right.size.w - align->size.w ;
}
//#################################################################################
void alignBottom(GRect bottom, GRect *align ) {
	align->origin.y =  bottom.origin.y + bottom.size.h - align->size.h ;
}
//#################################################################################
void translate(GSize vector, GRect *moved) {
	moved->origin.x = moved->origin.x + vector.w;
	moved->origin.y = moved->origin.y + vector.h;
}
//#################################################################################
void inCenterHrz(GRect center, GRect *in ) {
	in->origin.x = center.origin.x + (( center.size.w - in->size.w) / 2);
}
//#################################################################################
void inCenterVrt(GRect center, GRect *in ) {
	in->origin.y = center.origin.y + (( center.size.h - in->size.h) / 2);
}
//#################################################################################
void inBetweenHrz(GRect left, GRect right, GRect *in ) {
	in->origin.x = (left.origin.x + left.size.w + right.origin.x - in->size.w) / 2;
}
//#################################################################################
void inBetweenVrt(GRect top, GRect bottom, GRect *in ) {
	in->origin.y = (top.origin.y + top.size.h + bottom.origin.y - in->size.h) / 2;
}
