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
	IMAGE mine_click;
	IMAGE mine_wrong;
	IMAGE qmark;
	IMAGE qmark_click;
	IMAGE num_1, num_2, num_3, num_4;
	IMAGE num_5, num_6, num_7, num_8;
public:
	void init_gui();
	void init_map();
	void display_map();
	void load_assets();
	vector<int> game_loop();
	void upd_block(int x, int y, char sym);
	void exit_gui();
};
