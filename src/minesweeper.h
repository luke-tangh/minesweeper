#pragma once
#include <vector>


using namespace std;


int gen_rand(int ub);
bool valid_pos(int x, int y);


// base class for user_map and sys_map
class Grind {
public:
	vector<vector<char>> sys_map, user_map;

	void init_game();
	void init_sys_map();
	void init_user_map();
	void gen_mines();
	void upd_user_map();
	bool check_win();
	void print_map(int idx);
	bool is_mine(int x, int y);
	void rev_dfs(int x, int y);
	bool rev_pos(int x, int y);
};
