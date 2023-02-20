#pragma once

/* global variables */
extern int click_count;  // number of blocks clicked
extern int flag_count;
extern int t_start;
extern int t_end;
extern bool game_start;
extern bool game_exit;  // `esc` is pressed

/* map settings chars */
const int GRIND_HEIGHT = 16;  // 16
const int GRIND_WIDTH = 30;  // 30
const int MAX_MINES = 99;  // 99
const int BLOCKS = GRIND_HEIGHT * GRIND_WIDTH;


/* system map chars */
const char MINE = 'M';
const char REV_MINE = 'X';
const char BLANK = '0';  // `0`: no adjacent mines
const char FLAG = 'F';


/* user map chars */
const char UNREV = '.';


/* gui settings */
const int GAP = 10;
const int HEAD = 50;
const int BLOCK = 16;  // 16 pixel per block
const int MAP_WIDTH = GRIND_WIDTH * 16 + GAP * 2;
const int MAP_HEIGHT = GRIND_HEIGHT * 16 + GAP + HEAD;
const int FACE_X = GRIND_WIDTH * 16 / 2 + GAP - 12;
const int FACE_Y = HEAD / 2 - 12;
const int DIGIT_WIDTH = 13;
const int DIGIT_HEIGHT = 23;
const int COUNTER_LX = GAP * 2;
const int COUNTER_LY = HEAD / 2 - DIGIT_HEIGHT / 2;
const int COUNTER_RX = MAP_WIDTH - GAP * 2 - DIGIT_WIDTH * 3;
const int COUNTER_RY = HEAD / 2 - DIGIT_HEIGHT / 2;
