/* matthew sherwood, suspect device engineering. 
// 2048 in ncurses, with some speculative features, for fun

 3-6-17 -- started.
// make a board, wasd around.

*/

#include "2048.h"

states state=attract;
players player=human;
clock_t currTime;
uint32_t time=0;
uint8_t maxx,maxy,yOff;

int main (int argc, char *argv[]) {
	int turn=0,c;

	init_display();

	// get saved data
	// init


	while (1) {
		
		c=getch();
		if (c!=cOld) yOff++;
		if (yOff>20) yOff=0;
		cOld=c;

		currTime=clock();
		time = currTime/(CLOCKS_PER_SEC/100);

		getmaxyx (stdscr,maxy,maxx);
		if ((time%1000)==0) clear();

		mvprintw(y,x,"x:%i, y:%i",maxx,maxy);
		mvprintw(1+yOff,0,"%d",c);
		refresh();
/*
		// attract mode - options.
		if (!state) {		
			make_menu();
			display();
		} else {
			// do the game.
		}
*/

		


		// play

	}


	

return 0;
}

boards add_random (boards inBoard) {
	uint8_t total=0,x=0,y=0,randList[GRIDSIZE*GRIDSIZE]={0};
	int random=0;

	for (int i=0;i!=GRIDSIZE*GRIDSIZE;i++) {
		x=i/4;
		y=i%4;
		if (inBoard[x][y]==0) randList[total++]=(x<<=4)|y;
	} 

	if (!total) return inBoard;

	random=rand();
	random%=total;

	y=randList[random]&0x0f;
	x=randList[random]>>4;		//assumes GRIDSIZE never more than 15x15

	random=rand();
	random%=2;

	inBoard[x][y]=2+(random*2);
	return inBoard;
}

// checks a board. returns true if moves remain.
bool check_move (boards inBoard) {
	uint32_t test;
	uint8_t poss=0;

	for (int i=0;i!=GRIDSIZE*GRIDSIZE;i++) {
		x=i/4;
		y=i%4;
		if ((test=inBoard[x][y])==0) return TRUE;
		if (x<3) {
			if (inBoard[x+1][y]==test) return TRUE;
		}
		if (y<3) {
			if (inBoard[x][y+1]==test) return TRUE;
		}
	}
	return FALSE;
}

sub_boards move (sub_boards lBoard, uint8_t (*comp)(sub_boards *a, uint8_t width)) {

	if (!((*comp)(lBoard,GRIDSIZE))) move(lBoard,(*comp));	//hate calling this with GRIDSIZE.

return lBoard;
}


// moves sub_board left/up, returns 0 in process, 1 when done
// 
uint8_t mv_left (sub_boards *a, uint8_t b) {
	uint8_t checked=0, from=b;
	while (checked!=(b-1) && b>1) {
		if (a->set[checked]==0)
			from=++checked;
		else from=b;

		if (from!=b && a->set[from]!=0) {
			a->set[checked-1]=a->set[from];	//swap function, yeah?
			a->set[from]=0;
			return 0;
		}
	}
	return 1;
}

// moves sub_board right/down, returns 0 in process, 1 when done
uint8_t mv_right (sub_boards *a, uint8_t b) {
	int8_t checked=b-1, from=-1;
	while (checked>0) {
		if (a->set[checked]==0)
			from=--checked;
		else from=-1;

		if (from!=-1 && a->set[from]!=0) {
			a->set[from+1]=a->set[from];	// yup, swap.
			a->set[from]=0;
			return 0;
		}
	}
	return 1;
}

// combines left/up returns score when done. One pass combines all elegible.
uint32_t cmb_left (sub_boards *a, uint8_t b) {
	uint32_t score=0;

	if (b<2) return score;

	uint8_t checked=1;
	while (checked<b) {
		if (a->set[checked-1]==a->set[checked]) {
			a->set[checked-1]*=2;
			score+=a->set[checked-1];
			a->set[checked]=0;
			checked++;
		}
		checked++;
	}
	return score;
}

// combines right/down returns score when done. One pass combines all elegible. these could be combined.
uint32_t cmb_right (sub_boards *a, uint8_t b) {
	uint32_t score=0;

	if (b<2) return score;

	uint8_t checked=b-1;
	while (checked>0) {
		if (a->set[checked-1]==a->set[checked]) {
			a->set[checked]*=2*;
			score+=a->set[checked];
			a->set[checked-1]=0;
			checked--;
		}
		checked--;
	}
	return score;
}