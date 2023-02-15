#pragma once
#include <vector>
#include <map>


using namespace std;


int gen_rand(int ub);
bool valid_pos(int x, int y);


// base class for user_map and sys_map
class Grind {
private:
	vector<vector<char>> user_map;
	vector<vector<char>> sys_map;
public:
	void init_game();
	void init_sys_map();
	void init_user_map();
	void gen_mines();
	void upd_user_map();
	bool check_win();
	void print_map(int idx);
	bool is_mine(int x, int y);
	bool flag_mine(int x, int y);
	char get_user_pos(int x, int y);
	map<vector<int>, char> rev_dfs(map<vector<int>, char> &positions, int x, int y);
	map<vector<int>, char> rev_pos(int x, int y);
};
