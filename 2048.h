#include <stdint.h>

#define GRIDSIZE 4

//macros
#define max(A,B) ((A)>(B) ? (A) : (B))

typedef struct {
	uint32_t cell[GRIDSIZE][GRIDSIZE];
} boards;

typedef struct {
	uint32_t set[GRIDSIZE];
	uint8_t index;
} sub_boards;

extern boards board[100]; // all the boards, ever.