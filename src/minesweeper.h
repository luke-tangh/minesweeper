#pragma once

#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <iomanip>
#include <vector>
#include <random>
#include <ctime>

bool valid_pos(int x, int y);

struct Cell {
	int x;
	int y;
	char sym;
};

// base class for user_map and sys_map
class Grid {
private:
	int click_count;
	bool first_click;
	std::vector<std::vector<char>> user_map;
	std::vector<std::vector<char>> sys_map;
	std::vector<std::pair<int, int>> empty_blocks;
	std::vector<std::vector<int>> v;
public:
	Grid();
	void init_game();
	void init_maps();
	void init_empty_blocks();
	void init_sys_map();
	void init_user_map();
	void inc_cells(int x, int y);
	void gen_mines(int mines);
	bool check_win();
	char get_user_pos(int x, int y);
	void print_map(int idx);
	bool is_mine(int x, int y);
	bool flag_mine(int x, int y);
	void alt_mine(int x, int y);
	void check_wrong_flag(std::vector<Cell>& cells);
	void click_dfs(int x, int y, std::vector<Cell> &cells);
	void click_pos(int x, int y, std::vector<Cell> &cells);
	void search_pos(int x, int y, std::vector<Cell> &cells);
};
