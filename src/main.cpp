#include <unordered_map>
#include <iostream>
#include <thread>
#include <vector>
#include <ctime>
#include "minesweeper.h"
#include "conf.h"
#include "gui.h"


using namespace std;


int click_count = 0;
int flag_count = 0;
int t_start = 0;
int t_end = 0;
bool game_over = false;
bool game_exit = false;
bool refresh_timer = false;


// if axis lands in the grind
bool valid_axis(int x, int y) {
	return (x > GAP && x < GAP + GRIND_WIDTH * 16 && y > HEAD && y < GRIND_HEIGHT * 16 + HEAD);
}


// left click a block
void click_block(Grind* pG, Map* pM, int x, int y) {
	if (valid_axis(x, y)) {
		int x_idx = (y - HEAD) / BLOCK;
		int y_idx = (x - GAP) / BLOCK;
		map<vector<int>, char> positions = pG->click_pos(x_idx, y_idx);
		for (pair<vector<int>, char> kv : positions) {
			int x_pic = kv.first[1] * BLOCK + GAP;
			int y_pic = kv.first[0] * BLOCK + HEAD;
			pM->upd_block(x_pic, y_pic, kv.second);
		}
	}
}


// right click a block
void flag_block(Grind* pG, Map* pM, int x, int y) {
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
void search_block(Grind* pG, Map* pM, int x, int y) {
	if (valid_axis(x, y) && !game_over) {
		int x_idx = (y - HEAD) / BLOCK;
		int y_idx = (x - GAP) / BLOCK;
		map<vector<int>, char> positions = pG->search_pos(x_idx, y_idx);
		for (pair<vector<int>, char> kv : positions) {
			int x_pic = kv.first[1] * BLOCK + GAP;
			int y_pic = kv.first[0] * BLOCK + HEAD;
			pM->upd_block(x_pic, y_pic, kv.second);
		}
	}
}


// if restart botton is clicked
bool click_restart(int x, int y) {
	return x > FACE_X && x < FACE_X + FACE && y > FACE_Y && y < FACE_Y + FACE;
}


// restart game
void restart(Grind* pG, Map* pM) {
	game_over = false;
	refresh_timer = false;
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
void upd_time(Map* pM) {
	while (!game_exit) {
		t_end = time(NULL);
		if (refresh_timer) {
			pM->set_rcounter(t_end - t_start);
		}
		Sleep(200);  // interval - 200ms
	}
}


int main() {
	Map* pMap = new Map;
	Grind* pGame = new Grind;
	
	thread timer;
	t_start = time(NULL);
	timer = thread(upd_time, pMap);

	pGame->init_game();
	pMap->init_gui();
	pMap->load_assets();
	pMap->display_map();
	pMap->init_counters();
	pMap->init_map();
	// pGame->print_map(0);

	vector<int> axis = pMap->game_loop();

	while (!axis.empty()) {
		// game loop
		while (!axis.empty() && !game_over) {
			switch (axis[0]) {
			case 0:
				restart(pGame, pMap);
				break;
			case 1:
				check_timer();
				click_block(pGame, pMap, axis[1], axis[2]);
				if (click_restart(axis[1], axis[2])) {
					restart(pGame, pMap);
				}
				break;
			case 2:
				check_timer();
				flag_block(pGame, pMap, axis[1], axis[2]);
				break;
			case 3:
				check_timer();
				search_block(pGame, pMap, axis[1], axis[2]);
				break;
			}
			if (game_over) pMap->set_face_dead();
			if (pGame->check_win()) {
				game_over = true;
				refresh_timer = false;
				pMap->set_face_cool();
			}
			axis = pMap->game_loop();
		}
		// wait loop
		if (!axis.empty()) {
			switch (axis[0]) {
			case 0:
				restart(pGame, pMap);
				break;
			case 1:
				if (click_restart(axis[1], axis[2])) {
					restart(pGame, pMap);
				}
			}
			axis = pMap->wait_loop();
		}
	}

	game_exit = true;
	timer.join();
	// pGame->print_map(1);
	// cout << click_count << endl;
	pMap->exit_gui();

	return 0;
}
