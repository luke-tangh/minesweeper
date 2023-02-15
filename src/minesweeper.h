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
	vector<vector<int>> v;
	map<vector<int>, char> positions;
	int click_count;  // number of blocks clicked
public:
	void init_game();
	void init_sys_map();
	void init_user_map();
	void gen_mines();
	bool check_win();
	void print_map(int idx);
	bool is_mine(int x, int y);
	bool flag_mine(int x, int y);
	char get_user_pos(int x, int y);
	void click_dfs(int x, int y);
	map<vector<int>, char> click_pos(int x, int y);
};
