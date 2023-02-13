#pragma once
#include <graphics.h>

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
public:
	void init_gui();
	void display_map();
	void load_assets();
	void exit_gui();
};
