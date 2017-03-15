// display header

#include <ncurses.h>
#include <stdint.h>
#include <stdbool.h>

extern uint8_t score_x,score_y;

void init_display (void);
bool display_score (uint32_t);