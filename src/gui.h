#pragma once
#include <graphics.h>
#include <vector>


class Map {
private:
	IMAGE unrev;
	IMAGE blank;
	IMAGE flag, flag_wrong;
	IMAGE mine, mine_click;
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
	void init_counters();
	void set_lcounter(int mines);
	void set_rcounter(int time);
	void set_digit(int x, int y, int digit);
	void set_face_smile();
	void set_face_dead();
	void set_face_cool();
	void load_assets();
	std::vector<int> game_loop();
	std::vector<int> wait_loop();
	void upd_block(int x, int y, char sym);
	void exit_gui();
};
