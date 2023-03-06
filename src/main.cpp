#include <iostream>
#include <thread>
#include <vector>
#include <ctime>
#include "minesweeper.h"
#include "conf.h"
#include "gui.h"


using namespace std;


/* global variables */
bool game_over = false;
bool refresh_timer = false;


static unique_ptr<Map> pM(new Map);
static unique_ptr<Grid> pG(new Grid);
static bool game_exit = false;  // `esc` is pressed
static int flag_count = 0;
static int t_start = 0;
static int t_end = 0;


// if axis lands in the grind
bool valid_axis(int x, int y) {
	return (x > GAP && x < GAP + GRID_WIDTH * 16 && y > HEAD && y < GRID_HEIGHT * 16 + HEAD);
}


// left click a block
void click_block(int x, int y) {
	if (valid_axis(x, y)) {
		int x_idx = (y - HEAD) / BLOCK;
		int y_idx = (x - GAP) / BLOCK;
		vector<CellInfo> cells;
		pG->click_pos(x_idx, y_idx, cells);
		for (CellInfo ci : cells) {
			int x_pic = ci.y * BLOCK + GAP;
			int y_pic = ci.x * BLOCK + HEAD;
			pM->upd_block(x_pic, y_pic, ci.sym);
		}
	}
}


// right click a block
void flag_block(int x, int y) {
	if (valid_axis(x, y) && !game_over) {
		int x_idx = (y - HEAD) / BLOCK;
		int y_idx = (x - GAP) / BLOCK;
		char this_char = pG->get_user_pos(x_idx, y_idx);
		if (this_char != UNREV && this_char != FLAG) {
			return;
		}
		bool set_flag = pG->flag_mine(x_idx, y_idx);
		int x_pic = y_idx * BLOCK + GAP;
		int y_pic = x_idx * BLOCK + HEAD;
		if (set_flag) {
			pM->upd_block(x_pic, y_pic, FLAG);
			flag_count++;
		}
		else {
			pM->upd_block(x_pic, y_pic, UNREV);
			flag_count--;
		}
		pM->set_lcounter(MAX_MINES - flag_count);
	}
}


// middle click a block
void search_block(int x, int y) {
	if (valid_axis(x, y) && !game_over) {
		int x_idx = (y - HEAD) / BLOCK;
		int y_idx = (x - GAP) / BLOCK;
		vector<CellInfo> cells;
		pG->click_pos(x_idx, y_idx, cells);
		for (CellInfo ci : cells) {
			int x_pic = ci.y * BLOCK + GAP;
			int y_pic = ci.x * BLOCK + HEAD;
			pM->upd_block(x_pic, y_pic, ci.sym);
		}
	}
}


// if restart botton is clicked
bool click_restart(int x, int y) {
	return x > FACE_X && x < FACE_X + FACE && y > FACE_Y && y < FACE_Y + FACE;
}


// restart game
void restart() {
	game_over = false;
	refresh_timer = false;
	flag_count = 0;
	pG->init_game();
	pM->init_map();
	pM->init_counters();
}


// start timer if game starts
void check_timer() {
	if (!refresh_timer) {
		refresh_timer = true;
		t_start = time(NULL);
	}
}


// update time LCD
void upd_time() {
	while (!game_exit) {
		t_end = time(NULL);
		if (refresh_timer) {
			pM->set_rcounter(t_end - t_start);
		}
		Sleep(200);  // interval - 200ms
	}
}


int main() {
	thread timer;
	t_start = time(NULL);
	timer = thread(upd_time);

	pG->init_game();
	pM->load_assets();
	pM->display_map();
	pM->init_counters();
	pM->init_map();
	// pGame->print_map(0);

	vector<int> axis = pM->game_loop();

	while (!axis.empty()) {
		// game loop
		while (!axis.empty() && !game_over) {
			switch (axis[0]) {
			case 0:
				restart();
				break;
			case 1:
				check_timer();
				click_block(axis[1], axis[2]);
				if (click_restart(axis[1], axis[2])) {
					restart();
				}
				break;
			case 2:
				check_timer();
				flag_block(axis[1], axis[2]);
				break;
			case 3:
				check_timer();
				search_block(axis[1], axis[2]);
				break;
			}
			if (game_over) pM->set_face_dead();
			if (pG->check_win()) {
				game_over = true;
				refresh_timer = false;
				pM->set_face_cool();
			}
			axis = pM->game_loop();
		}
		// wait loop
		if (!axis.empty()) {
			switch (axis[0]) {
			case 0:
				restart();
				break;
			case 1:
				if (click_restart(axis[1], axis[2])) {
					restart();
				}
			}
			axis = pM->wait_loop();
		}
	}

	game_exit = true;
	timer.join();
	// pGame->print_map(1);
	// cout << click_count << endl;
	pM->exit_gui();

	return 0;
}
