#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ncurses.h>
#include <time.h>

#define GRIDSIZE 4

//macros
#define max(A,B) ((A)>(B) ? (A) : (B))

typedef struct {
	uint32_t cell[GRIDSIZE][GRIDSIZE];
} boards;

typedef struct {
	uint32_t set[GRIDSIZE];
	uint8_t index; 			// 1-4 L-to-R and/or U-to-D
} sub_boards;

extern boards board[100]; 	// all the boards, ever.

typedef enum {attract=0,begin,add,check,move} states;
typedef enum {human=0,computer} players;

extern states state;
extern players player;

boards add_random (boards);
bool check_move (boards);
sub_boards move (sub_boards , uint8_t (*comp)(sub_boards*, uint8_t));
uint8_t mv_left (sub_boards *, uint8_t );
uint8_t mv_right (sub_boards *, uint8_t );
uint32_t cmb_left (sub_boards *, uint8_t );
uint32_t cmb_right (sub_boards *, uint8_t );