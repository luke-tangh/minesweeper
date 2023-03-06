#pragma once

/* global variables */
extern bool game_over;
extern bool refresh_timer;


/* map settings chars */
constexpr int GRID_HEIGHT = 16;  // 16
constexpr int GRID_WIDTH = 30;  // 30
constexpr int MAX_MINES = 99;  // 99
constexpr int BLOCKS = GRID_HEIGHT * GRID_WIDTH;


/* map chars */
constexpr char MINE = 'M';
constexpr char REV_MINE = 'X';
constexpr char BLANK = '0';  // `0`: no adjacent mines
constexpr char FLAG = 'F';
constexpr char UNREV = '.';
constexpr char FLAG_WRONG = 'W';


/* gui settings */
constexpr int GAP = 10;
constexpr int HEAD = 50;
constexpr int FACE = 24;
constexpr int BLOCK = 16;  // 16 pixel per block
constexpr int MAP_WIDTH = GRID_WIDTH * 16 + GAP * 2;
constexpr int MAP_HEIGHT = GRID_HEIGHT * 16 + GAP + HEAD;
constexpr int FACE_X = GRID_WIDTH * 16 / 2 + GAP - 12;
constexpr int FACE_Y = HEAD / 2 - 12;
constexpr int DIGIT_WIDTH = 13;
constexpr int DIGIT_HEIGHT = 23;
constexpr int COUNTER_LX = GAP * 2;
constexpr int COUNTER_LY = HEAD / 2 - DIGIT_HEIGHT / 2;
constexpr int COUNTER_RX = MAP_WIDTH - GAP * 2 - DIGIT_WIDTH * 3;
constexpr int COUNTER_RY = HEAD / 2 - DIGIT_HEIGHT / 2;
