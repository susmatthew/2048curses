#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ncurses.h>
#include <time.h>

#define GRIDSIZE 4

// keys
#define UP		119
#define LEFT	97
#define DOWN 	115
#define RIGHT	100
#define NOKEY	-1
#define HINT	104
#define SAVE	112

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

typedef enum {newturn,moving,done} states;
typedef enum {human=0,computer} players;

extern states state;
extern players player;

boards add_random (boards);
bool check_move (boards);
uint8_t mv_left (sub_boards *, uint8_t );
uint8_t mv_right (sub_boards *, uint8_t );
uint32_t cmb_left (sub_boards *, uint8_t );
uint32_t cmb_right (sub_boards *, uint8_t );