#pragma once
#include <graphics.h>
#include <vector>


using namespace std;


class Map {
private:
	IMAGE blank;
	IMAGE empty;
	IMAGE flag;
	IMAGE mine;
	IMAGE mine_click, mine_wrong;
	IMAGE qmark, qmark_click;
	IMAGE face_cool, face_dead, face_shock;
	IMAGE face_smile, face_smile_press;
	IMAGE num_1, num_2, num_3, num_4;
	IMAGE num_5, num_6, num_7, num_8;
	IMAGE digit_0, digit_1, digit_2;
	IMAGE digit_3, digit_4, digit_5;
	IMAGE digit_6, digit_7, digit_8;
	IMAGE digit_9, digit_null, digit_empty;
public:
	void init_gui();
	void init_map();
	void display_map();
	void load_assets();
	vector<int> game_loop();
	void upd_block(int x, int y, char sym);
	void exit_gui();
};
