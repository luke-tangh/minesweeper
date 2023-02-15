#pragma once

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
const int HEAD = 40;
const int BLOCK = 16;  // 16 pixel per block
const int MAP_WIDTH = GRIND_WIDTH * 16 + GAP * 2;
const int MAP_HEIGHT = GRIND_HEIGHT * 16 + GAP + HEAD;
const int FACE_X = GRIND_WIDTH * 16 / 2 + GAP - 12;
const int FACE_Y = HEAD / 2 - 12;
