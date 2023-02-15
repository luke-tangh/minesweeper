#include <iostream>
#include <cstdlib>
#include <iomanip>
#include <vector>
#include <ctime>
#include <map>
#include "minesweeper.h"
#include "conf.h"


using namespace std;


// return random number from 0 to `ub` exclusively
int gen_rand(int ub) {
    return rand() % ub;
}


// return true if x, y is a valid pair
bool valid_pos(int x, int y) {
    if (x >= GRIND_HEIGHT || x < 0) {
        return false;
    }
    if (y >= GRIND_WIDTH || y < 0) {
        return false;
    }
    return true;
}


void Grind::init_game() {
    click_count = 0;
    game_over = false;
    v = { {1,-1},{1,0},{1,1},{-1,-1},{-1,0},{-1,1},{0,-1},{0,1} };
    srand(time(0));  // set random seed
    init_sys_map();
    init_user_map();
    gen_mines();
};


// initial system map
void Grind::init_sys_map() {
    sys_map.clear();
    for (int i = 0; i < GRIND_HEIGHT; ++i) {
        vector<char> col;
        for (int j = 0; j < GRIND_WIDTH; ++j) {
            col.push_back(BLANK);
        }
        sys_map.push_back(col);
    }
}


// initial user map
void Grind::init_user_map() {
    user_map.clear();
    for (int i = 0; i < GRIND_HEIGHT; ++i) {
        vector<char> col;
        for (int j = 0; j < GRIND_WIDTH; ++j) {
            col.push_back(UNREV);
        }
        user_map.push_back(col);
    }
}


// print the indexed map 0:sys_map; 1:user_map
void Grind::print_map(int idx) {
    // print index
    cout << setw(2) << ' ';
    for (int i = 0; i < GRIND_WIDTH; ++i) {
        cout << setw(2) << i;
    }
    cout << '\n';
    
    if(idx == 0) {
        for (int i = 0; i < sys_map.size(); ++i) {
            cout << setw(2) << right << i;
            for (int j = 0; j < sys_map[0].size(); ++j) {
                cout << setw(2) << sys_map[i][j];
            }
            cout << '\n';
        }
    }
    else if (idx == 1){
        for (int i = 0; i < user_map.size(); ++i) {
            cout << setw(2) << i ;
            for (int j = 0; j < user_map[0].size(); ++j) {
                cout << setw(2) << user_map[i][j];
            }
            cout << '\n';
        }
    }
    else {
        cout << "invalid output index" << endl;
    }
}


// generate mines in the map
void Grind::gen_mines() {
    for (int i = 0; i < MAX_MINES; ++i) {
        int x = gen_rand(GRIND_HEIGHT);
        int y = gen_rand(GRIND_WIDTH);
        while (sys_map[x][y] == MINE) {
            x = gen_rand(GRIND_HEIGHT);
            y = gen_rand(GRIND_WIDTH);
        }
        sys_map[x][y] = MINE;
        for (int i = 0; i < 8; i++) {
            if (valid_pos(x + v[i][0], y + v[i][1]) && sys_map[x + v[i][0]][y + v[i][1]] != MINE) {
                sys_map[x + v[i][0]][y + v[i][1]]++;
            }
        }
    }
}


// return true if mine hit
bool Grind::is_mine(int x, int y) {
    return sys_map[x][y] == MINE;
}


bool Grind::check_game_over() {
    return game_over || click_count == BLOCKS - MAX_MINES;
}


char Grind::get_user_pos(int x, int y) {
    return user_map[x][y];
}


// dfs algorithm
void Grind::click_dfs(int x, int y) {
    if (!valid_pos(x, y) || user_map[x][y] != UNREV) {
        return;
    }
    if (user_map[x][y] != FLAG) {
        char nearby_mines = sys_map[x][y];
        if (nearby_mines > '0') {
            user_map[x][y] = nearby_mines;
            positions[{x, y}] = nearby_mines;
        }
        else {
            positions[{x, y}] = BLANK;
            user_map[x][y] = BLANK;
            for (int i = 0; i < 8; i++) {
                click_dfs(x + v[i][0], y + v[i][1]);
            }
        }
        click_count++;
    }
    return;
}


// click a position
map<vector<int>, char> Grind::click_pos(int x, int y) {
    positions.clear();
    if (!valid_pos(x, y)) {
        return positions;
    }
    if (is_mine(x, y)) {
        if (user_map[x][y] != FLAG) {
            user_map[x][y] = REV_MINE;
            positions[{x, y}] = REV_MINE;
            game_over = true;
        }
        return positions;
    }
    click_dfs(x, y);
    for (int i = 0; i < 8; i++) {
        if (valid_pos(x + v[i][0], y + v[i][1]) && sys_map[x + v[i][0]][y + v[i][1]] == BLANK) {
            click_dfs(x + v[i][0], y + v[i][1]);
        }
    }
    return positions;
}


// true: set flag | false: cancel flag
bool Grind::flag_mine(int x, int y) {
    if (user_map[x][y] == FLAG) {
        user_map[x][y] = UNREV;
        return false;
    }
    else {
        user_map[x][y] = FLAG;
        return true;
    }
}


map<vector<int>, char> Grind::search_pos(int x, int y) {
    positions.clear();
    char flags = '0';
    for (int i = 0; i < 8; i++) {
        if (valid_pos(x + v[i][0], y + v[i][1])) {
            if (user_map[x + v[i][0]][y + v[i][1]] == FLAG) {
                flags++;
            }
            else {
                positions[{x + v[i][0], y + v[i][1]}] = sys_map[x + v[i][0]][y + v[i][1]];
            }
        }
    }
    if (flags != sys_map[x][y]) {
        positions.clear();
    }
    for (pair<vector<int>, char> kv : positions) {
        if (is_mine(kv.first[0], kv.first[1])) {
            positions[{kv.first[0], kv.first[1]}] = REV_MINE;
            game_over = true;
        }
        if (sys_map[kv.first[0]][kv.first[1]] == BLANK) {
            click_dfs(kv.first[0], kv.first[1]);
        }
    }
    return positions;
}
