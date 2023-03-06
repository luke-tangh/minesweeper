#pragma once
#include <vector>
#include <map>


int gen_rand(int ub);
bool valid_pos(int x, int y);


struct CellInfo {
	int x;
	int y;
	char sym;
};


// base class for user_map and sys_map
class Grid {
private:
	std::vector<std::vector<char>> user_map;
	std::vector<std::vector<char>> sys_map;
	std::vector<std::vector<int>> v;
	int click_count;
	// bool first_click;
public:
	Grid();
	void init_game();
	void init_maps();
	void init_sys_map();
	void init_user_map();
	void gen_mines();
	bool check_win();
	char get_user_pos(int x, int y);
	void print_map(int idx);
	bool is_mine(int x, int y);
	bool flag_mine(int x, int y);
	void click_dfs(int x, int y, std::vector<CellInfo> &cells);
	void click_pos(int x, int y, std::vector<CellInfo> &cells);
	void search_pos(int x, int y, std::vector<CellInfo> &cells);
};
