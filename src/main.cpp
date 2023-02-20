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
bool game_start = false;
bool game_exit = false;


// if axis lands in the grind
bool valid_axis(int x, int y) {
	return (x > GAP && x < GAP + GRIND_WIDTH * 16 && y > HEAD && y < GRIND_HEIGHT * 16 + HEAD);
}


// left click a block
void click_block(Grind* pG, Map* pM, int x, int y) {
	if (valid_axis(x, y) && !pG->check_game_over()) {
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
	if (valid_axis(x, y) && !pG->check_game_over()) {
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
	if (valid_axis(x, y) && !pG->check_game_over()) {
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


// restart game
void restart(Grind* pG, Map* pM) {
	game_start = false;
	pG->init_game();
	pM->init_map();
	pM->init_counters();
}


// start timer if game starts
void check_time() {
	if (!game_start) {
		game_start = true;
		t_start = time(NULL);
	}
}


// update time LCD
void upd_time(Grind* pG, Map* pM) {
	while (!game_exit) {
		t_end = time(NULL);
		if (game_start) {
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
	timer = thread(upd_time, pGame, pMap);

	pGame->init_game();
	pMap->init_gui();
	pMap->load_assets();
	pMap->display_map();
	pMap->init_counters();
	pMap->init_map();
	pGame->print_map(0);

	vector<int> axis = pMap->game_loop();

	while (!axis.empty()) {
		check_time();
		switch (axis[0]) {
		case 0:
			restart(pGame, pMap);
			break;
		case 1:
			click_block(pGame, pMap, axis[1], axis[2]);
			break;
		case 2:
			flag_block(pGame, pMap, axis[1], axis[2]);
			break;
		case 3:
			search_block(pGame, pMap, axis[1], axis[2]);
			break;
		}
		axis = pMap->game_loop();
	}

	game_exit = true;
	timer.join();
	pGame->print_map(1);
	pMap->exit_gui();

	return 0;
}
