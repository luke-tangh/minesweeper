#include <graphics.h>
#include <iostream>
#include <vector>
#include <conio.h>
#include "minesweeper.h"
#include "conf.h"
#include "gui.h"


using namespace std;


void Map::init_gui() {
	initgraph(MAP_WIDTH, MAP_HEIGHT);
	// set background grey and refresh screen
	setbkcolor(RGB(192, 192, 192));
	cleardevice();
}


void Map::init_map() {
	for (int i = GAP; i < GRIND_WIDTH * 16 + GAP; i += 16) {
		for (int j = HEAD; j < GRIND_HEIGHT * 16 + HEAD; j += 16) {
			putimage(i, j, &blank);
		}
	}
}


void Map::display_map() {
	setlinecolor(WHITE);
	setlinestyle(PS_SOLID, 3);
	line(0, 0, MAP_WIDTH, 0);
	line(0, 0, 0, MAP_HEIGHT);

	setlinecolor(RGB(123, 123, 123));
	setlinestyle(PS_SOLID, 3);
	line(MAP_WIDTH-2, 0, MAP_WIDTH-2, MAP_HEIGHT);
	line(0, MAP_HEIGHT-2, MAP_WIDTH, MAP_HEIGHT-2);
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
	loadimage(&num_1, _T("./assets/num_1.png"));
	loadimage(&num_2, _T("./assets/num_2.png"));
	loadimage(&num_3, _T("./assets/num_3.png"));
	loadimage(&num_4, _T("./assets/num_4.png"));
	loadimage(&num_5, _T("./assets/num_5.png"));
	loadimage(&num_6, _T("./assets/num_6.png"));
	loadimage(&num_7, _T("./assets/num_7.png"));
	loadimage(&num_8, _T("./assets/num_8.png"));
}


vector<int> Map::game_loop() {
	ExMessage m;
	while (true) {
		m = getmessage(EX_MOUSE | EX_KEY);
		switch (m.message) {
		case WM_LBUTTONDOWN:
			return { 1, m.x, m.y };
		case WM_RBUTTONDOWN:
			return { 2, m.x, m.y };
		case WM_KEYDOWN:
			if (m.vkcode == VK_ESCAPE)
				return {0};
			if (m.vkcode == 0x52)
				return {0};
		}
	}
}


void Map::upd_block(int x, int y, char sym) {
	switch (sym) {
	case 'B': putimage(x, y, &blank); break;
	case 'E': putimage(x, y, &empty); break;
	case 'M': putimage(x, y, &mine); break;
	case 'F': putimage(x, y, &flag); break;
	case 'X': putimage(x, y, &mine_click); break;
	case '1': putimage(x, y, &num_1); break;
	case '2': putimage(x, y, &num_2); break;
	case '3': putimage(x, y, &num_3); break;
	case '4': putimage(x, y, &num_4); break;
	case '5': putimage(x, y, &num_5); break;
	case '6': putimage(x, y, &num_6); break;
	case '7': putimage(x, y, &num_7); break;
	case '8': putimage(x, y, &num_8); break;
	}
}


void Map::exit_gui() {
	closegraph();
}
