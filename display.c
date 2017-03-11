/*
// ncurses display routines. Some sort of animation.
//
*/
#include "display.h"

bool display_score (uint32_t score) {

}

void init_display (void) {
	initscr();
	noecho();
	curs_set(FALSE);
	clear();
	nodelay(stdscr,TRUE);	
}