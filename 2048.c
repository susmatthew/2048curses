/* matthew sherwood, suspect device engineering. 
// 2048 in ncurses, with some speculative features, for fun


*/

#include "2048.h"
#include "display.h"

states state[100]={0}; // adding
players player=human;
clock_t currTime;
uint32_t locTime=0;
uint8_t maxX,maxY,yOff,current=0; //board
boards *cBoard=&board;


int main (int argc, char *argv[]) {
	int c,move;
	uint32_t turn=0;

	init_display();


	while (1) {
		// choose a board.

		switch (state[current]) {
			default:
				break;

			case (newturn):
				add_random(*(cBoard+current));
				if (check_move(board[current])) state[current]=moving;
				else state[current]=done;
				break;

			case (moving):
				c=getch();
				if (!current && !player) move=c;
				else move=get_RNN(current,*(cBoard+current));
				do_move(move,c,*(cBoard+current));
				break;

			case (done):
				c=getch();
				if (current || player) score_RNN (*(cBoard+current));
				else display_end(c);
				break;
		}
	}


/*
		currTime=clock();
		locTime = currTime/(CLOCKS_PER_SEC/100);

		getmaxyx (stdscr,maxY,maxX);
		mvprintw(0,0,"x:%i, y:%i",maxX,maxY);
		mvprintw(1+yOff,0,"%d",c);
		refresh();
*/
	
return 0;
}



void add_random (boards *inBoard) {
	uint8_t total=0,x=0,y=0,randList[GRIDSIZE*GRIDSIZE]={0};
	int random=0;

	for (int i=0;i!=GRIDSIZE*GRIDSIZE;i++) {
		x=i/4;
		y=i%4;
		if (inBoard->cell[x][y]==0) randList[total++]=(x<<=4)|y;
	} 

	if (!total) return 0;

	random=rand();
	random%=total;

	y=randList[random]&0x0f;
	x=randList[random]>>4;		//assumes GRIDSIZE never more than 15x15

	random=rand();
	random%=2;

	inBoard->cell[x][y]=2+(random*2);
}

// checks a board. returns true if moves remain.
//
bool check_move (boards *inBoard) {
	uint32_t test;
	uint8_t x=0,y=0;

	for (int i=0;i!=GRIDSIZE*GRIDSIZE;i++) {
		x=i/4;
		y=i%4;
		if ((test=inBoard->cell[x][y])==0) return TRUE;
		if (x<3) {
			if (inBoard->cell[x+1][y]==test) return TRUE;
		}
		if (y<3) {
			if (inBoard->cell[x][y+1]==test) return TRUE;
		}
	}
	return FALSE;
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
//
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
			a->set[checked]*=2;
			score+=a->set[checked];
			a->set[checked-1]=0;
			checked--;
		}
		checked--;
	}
	return score;
}