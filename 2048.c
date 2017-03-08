/* matthew sherwood, suspect device engineering. 
// 2048 in ncurses, with some speculative features, for fun

 3-6-17 -- started.
// make a board, wasd around.

*/

#include "2048.h"

int main (int argc, char *argv[]) {
	int turn=0;


	while (1) {

	}


	

return 0;
}

board add_random (board inBoard) {

}

sub_board move (sub_board sub, unint8_t width) {
	uint8_t checked=0,first=width+1,last=width+1;
	while (checked<(width+1)) {
		if (sub.set[checked]==0)
			first=checked++;
		else if (first!=width+1)
			last=checked;
		else checked++;

		if (first!=last && last!=width+1) {
			sub.set[first]=sub.set[last];
			sub.set[last]=0;
			return sub;
		}


	}

return 0;
}

uint8_t right (sub_board sub, unint8_t width) {

return 0;
}