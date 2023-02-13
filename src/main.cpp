#include <iostream>
#include "gui.h"
#include "minesweeper.h"


using namespace std;


int input_axis() {
	int axis;
	cin >> axis;
	return axis;
}


int main() {
	Map* pMap = new Map;
	pMap->init_gui();
	pMap->load_assets();
	pMap->display_map();
	pMap->exit_gui();

	Grind* pGame = new Grind;
	pGame->init_game();
	pGame->print_map(0);
	while (!pGame->check_win()) {
		int x = input_axis();
		int y = input_axis();
		cout << "position: " << x << ',' << y << endl;
		pGame->rev_pos(x, y);
		pGame->print_map(1);
	}
	return 0;
}
