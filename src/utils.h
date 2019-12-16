#ifndef UTILS_H
#define UTILS_H

#include <string.h>

#define GRID_W 16
#define GRID_H 22
#define SPAWN_X 7
#define NUM_BLOCKS 7
#define MENU_COL 2*GRID_W+5
#define MENU_ROW 23
#define CRITICAL_BLOCK 15

/*
 * Controls
 */
//key for player one
#define UP_KEY_1 65
#define DOWN_KEY_1 66
#define LEFT_KEY_1 68
#define RIGHT_KEY_1 67
// key for player two
/*
#define UP_KEY_2 65
#define DOWN_KEY_2 66
#define LEFT_KEY_2 68
#define RIGHT_KEY_2 67
*/

#define DROP_KEY_1 ' '


#define HOLD_KEY_1 'h'



#define ROTATE_KEY_1 'r'
#define ROTATE_KEY_2 'a'

#define PAUSE_KEY '1'
#define RESUME_KEY '2'
#define QUIT_KEY '3'
#define SELECT_KEY 10

/*
 * External constants to be used in other files
 */
extern const int I_Block[4][2];
extern const int O_Block[4][2];
extern const int T_Block[4][2];
extern const int Z_Block[4][2];
extern const int S_Block[4][2];
extern const int J_Block[4][2];
extern const int L_Block[4][2];
extern const int ROTATION_MATRIX_R[2][2];

/*
 * Taken from https://i.stack.imgur.com/JLRFu.png
 *
 * Not defined as enum class to allow implicit casting to int
 */
typedef enum {EMPTY, CYAN, BLUE, WHITE, YELLOW, GREEN, PURPLE, RED, GHOST} BlockColor;

/*
 * Taken from http://tetris.wikia.com/wiki/Tetromino
 */
typedef enum {I, J, L, O, S, T, Z, NONE} BlockType;

/*
 * Modes that the game can be in
 */
typedef enum {RUNNING, PAUSED, CONFIRM_QUIT, SHUTDOWN, ENDGAME } Gamemode;

/*
  Representation of generic Tetris block
*/
typedef struct {
    int cells[4][2];
    int x, y;
    int ghosty;
    BlockColor color;
    BlockType type;
} Block;

/*
 * Container for aggregating net movement in a frame.
 */
typedef struct {
    int x;
    int y;
    int r;
    int drop;
} Movement;

typedef struct {
    int grid[GRID_W][GRID_H];
    int score;
    int level;
    Gamemode mode;
    int speed; // speed at which blocks move down without user input
    int can_hold;
    Block* block;
    BlockType next;
    BlockType held_block;
    int block_count;
    Movement* net_move;
} State;

/*
 * Checks whether coordinate is inside playable area
 */
int in_grid(int x, int y);

/*
 * Checks whether the spaces below or above a cell are empty
 */
int can_move_vertically(int x, int y, State* s);

/*
 * Checks whether the spaces to the sides of a cell are empty
 */
int can_move_horizontally(int x, int y, State* s);

/*
 * Attempt to move a block a vertical distance defined by the movement struct
 */
int move_block_vertically(State* s);

/*
 * Attempt to move a block a horizontal distance
 */
int move_block_horizontally(State* s);

/*
 * Attempt to rotate a block
 */
int rotate_block(State* s);

/*
 * Set all cells occupied by playable block to EMPTY
 */
void clear_block(State* s);

/*
 * Set all cells occupied by playable block to the block's color
 */
void draw_block(State* s);

/*
 * Set all cells occupied by playable block's ghost to EMPTY
 * Note: this implementation allows for overlap between playable block and
 *  its ghost, so this method may clear some cells of the playable block.
 */
void clear_ghost(State* s);

/*
 * Set all cells occupied by the playable block's ghost to the GHOST color.
 * Note: since the ghost and playable block may overlap, the order in which
 *  their draw calls are made will determine which renders "ontop" of the other.
 */
void draw_ghost(State* s);

/*
 * Calculate and assign correct position for the ghost of the playable block.
 * The correct position of the ghost is always the furthest down the block may
 * travel before hitting any other block.
 */
void project_ghost(State* s);

/*
 * Increment an integer by one without surpassing a specified maximum
 *
 * @param num: the integer to increment
 * @param max: the maximum value that the integer can be incremented to
 */
void increment_with_max(int* num, int max);

/*
 * Decrement an integer by one without surpassing a specified minimum
 *
 * @param num: the integer to deccrement
 * @param max: the minimum value that the integer can be deccremented to
 */
void decrement_with_min(int* num, int min);

/*
 * Set all values in tetris grid to EMPTY
 */
void initialize_grid(int grid[GRID_W][GRID_H]);

/*
 * Rotates block 90 degrees clockwise
 */
void rotate(Block* b);

#endif
