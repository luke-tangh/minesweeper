#include <unordered_map>
#include <iostream>
#include <vector>
#include "gui.h"
#include "conf.h"
#include "minesweeper.h"


using namespace std;


bool valid_axis(int x, int y) {
	return (x > GAP && x < GAP + GRIND_WIDTH * 16 &&
			y > HEAD && y < GRIND_HEIGHT * 16 + HEAD);
}


void click_block(Grind* pG, Map* pM, int x, int y) {
	if (valid_axis(x, y)) {
		int x_idx = (y - HEAD) / BLOCK;
		int y_idx = (x - GAP) / BLOCK;
		map<vector<int>, char> positions = pG->rev_pos(x_idx, y_idx);
		for (pair<vector<int>, char> kv : positions) {
			int x_pic = kv.first[1] * BLOCK + GAP;
			int y_pic = kv.first[0] * BLOCK + HEAD;
			pM->upd_block(x_pic, y_pic, kv.second);
		}
	}
}


void flag_block(Grind* pG, Map* pM, int x, int y) {
	if (valid_axis(x, y)) {
		int x_idx = (y - HEAD) / BLOCK;
		int y_idx = (x - GAP) / BLOCK;
		char this_char = pG->get_user_pos(x_idx, y_idx);
		if (this_char != UNREV_POS && this_char != FLAG) {
			return;
		}
		bool set_flag = pG->flag_mine(x_idx, y_idx);
		int x_pic = y_idx * BLOCK + GAP;
		int y_pic = x_idx * BLOCK + HEAD;
		if (set_flag) {
			pM->upd_block(x_pic, y_pic, FLAG);
		}
		else {
			pM->upd_block(x_pic, y_pic, BLANK);
		}
	}
}


void restart(Grind* pG, Map* pM) {
	pG->init_game();
	pM->init_map();
}


int main() {
	Map* pMap = new Map;
	Grind* pGame = new Grind;
	
	pGame->init_game();
	pMap->init_gui();
	pMap->load_assets();
	pMap->display_map();
	pMap->init_map();

	vector<int> axis = pMap->game_loop();

	while (!axis.empty()) {
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
		}
		axis = pMap->game_loop();
	}

	pMap->exit_gui();

	return 0;
}
