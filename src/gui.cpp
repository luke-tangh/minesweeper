#include <graphics.h>
#include <iostream>
#include <conio.h>
#include <vector>
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
			putimage(i, j, &unrev);
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

	putimage(FACE_X, FACE_Y, &face_smile);
}


void Map::load_assets() {
	loadimage(&unrev, _T("./assets/unrev.png"));
	loadimage(&blank, _T("./assets/blank.png"));
	loadimage(&flag, _T("./assets/flag.png"));
	loadimage(&mine, _T("./assets/mine.png"));
	loadimage(&mine_click, _T("./assets/mine_click.png"));
	loadimage(&mine_wrong, _T("./assets/mine_wrong.png"));
	loadimage(&qmark, _T("./assets/qmark.png"));
	loadimage(&qmark_click, _T("./assets/qmark_click.png"));
	loadimage(&face_cool, _T("./assets/face_cool.png"));
	loadimage(&face_dead, _T("./assets/face_dead.png"));
	loadimage(&face_shock, _T("./assets/shock.png"));
	loadimage(&face_smile, _T("./assets/face_smile.png"));
	loadimage(&face_smile_press, _T("./assets/face_smile_press.png"));
	loadimage(&num_1, _T("./assets/num_1.png"));
	loadimage(&num_2, _T("./assets/num_2.png"));
	loadimage(&num_3, _T("./assets/num_3.png"));
	loadimage(&num_4, _T("./assets/num_4.png"));
	loadimage(&num_5, _T("./assets/num_5.png"));
	loadimage(&num_6, _T("./assets/num_6.png"));
	loadimage(&num_7, _T("./assets/num_7.png"));
	loadimage(&num_8, _T("./assets/num_8.png"));
	loadimage(&digit_0, _T("./assets/digit_0.png"));
	loadimage(&digit_1, _T("./assets/digit_1.png"));
	loadimage(&digit_2, _T("./assets/digit_2.png"));
	loadimage(&digit_3, _T("./assets/digit_3.png"));
	loadimage(&digit_4, _T("./assets/digit_4.png"));
	loadimage(&digit_5, _T("./assets/digit_5.png"));
	loadimage(&digit_6, _T("./assets/digit_6.png"));
	loadimage(&digit_7, _T("./assets/digit_7.png"));
	loadimage(&digit_8, _T("./assets/digit_8.png"));
	loadimage(&digit_9, _T("./assets/digit_9.png"));
	loadimage(&digit_null, _T("./assets/digit_null.png"));
	loadimage(&digit_empty, _T("./assets/digit_empty.png"));
}



/*
vector.empty() : exit
vector[0] = 0 : restart
vector[0] = 1 : click
vector[0] = 2 : flag
*/
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
				return {};
			if (m.vkcode == 0x52)
				return {0};
		}
	}
}


void Map::upd_block(int x, int y, char sym) {
	switch (sym) {
	case UNREV: putimage(x, y, &unrev); break;
	case BLANK: putimage(x, y, &blank); break;
	case MINE: putimage(x, y, &mine); break;
	case FLAG: putimage(x, y, &flag); break;
	case REV_MINE: putimage(x, y, &mine_click); break;
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
