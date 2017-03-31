#include "utils.h"

//#################################################################################
tm* get_time(){
	time_t rawtime;
	time(&rawtime);
	return localtime(&rawtime);
}
//#################################################################################
int elapsed_seconds(tm* reference) {
	time_t rawtime;
	time(&rawtime);
	time_t converted = mktime(reference);
	return difftime(rawtime, converted);
}
//#################################################################################
