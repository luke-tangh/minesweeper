#pragma once

/* map settings chars */
const int GRIND_HEIGHT = 10;  //16
const int GRIND_WIDTH = 10;  //30;
const int MAX_MINES = 10;  //99;

/* system map chars */
const char MINE = 'M';
const char REV_MINE = 'X';
// `E`: unrevealed position
const char EMPTY = 'E';
// `B`: no adjacent mines
const char BLANK = 'B';

/* user map chars */
const char UNREV_POS = '.';
