#include <graphics.h>
#include <conio.h>
#include "conf.h"
#include "gui.h"


void Map::init_gui() {
	initgraph(GRIND_WIDTH * 16, GRIND_HEIGHT * 16);
}


void Map::display_map() {
	for(int i = 0; i < GRIND_HEIGHT*16; i+=16) {
		for(int j = 0; j < GRIND_WIDTH*16; j+=16) {
			putimage(i, j, &blank);
		}
	}
}


void Map::load_assets() {
	loadimage(&blank, _T("./assets/blank.png"));
	loadimage(&empty, _T("./assets/empty.png"));
	loadimage(&flag, _T("./assets/flag.png"));
	loadimage(&mine, _T("./assets/mine.png"));
	loadimage(&mine_click, _T("./assets/mine_click.png"));
	loadimage(&mine_wrong, _T("./assets/mine_wrong.png"));
	loadimage(&qmark, _T("./assets/qmark.png"));
	loadimage(&qmark_click, _T("./assets/qmark_click.png"));
}

void Map::exit_gui() {
	int a = _getch();
	closegraph();
}
