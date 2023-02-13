﻿#include <iostream>
#include <cstdlib>
#include <iomanip>
#include <vector>
#include <ctime>
#include "conf.h"
#include "minesweeper.h"


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
    // set random seed
    srand(time(0));
    init_sys_map();
    init_user_map();
    gen_mines();
};


// initial system map
void Grind::init_sys_map() {
    for (int i = 0; i < GRIND_HEIGHT; ++i) {
        vector<char> col;
        for (int j = 0; j < GRIND_WIDTH; ++j) {
            col.push_back(EMPTY);
        }
        sys_map.push_back(col);
    }
}


// initial user map
void Grind::init_user_map() {
    for (int i = 0; i < GRIND_HEIGHT; ++i) {
        vector<char> col;
        for (int j = 0; j < GRIND_WIDTH; ++j) {
            col.push_back(UNREV_POS);
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
    }
}


// return true if mine hit
bool Grind::is_mine(int x, int y) {
    if (sys_map[x][y] == MINE) {
        return true;
    }
    else {
        return false;
    }
}


// return true if win
bool Grind::check_win() {
    for (int i = 0; i < GRIND_HEIGHT; ++i) {
        for (int j = 0; j < GRIND_WIDTH; ++j) {
            if (sys_map[i][j] != user_map[i][j]) {
                return false;
            }
        }
    }
    return true;
}


// update user map
void Grind::upd_user_map() {
    for (int i = 0; i < GRIND_HEIGHT; ++i) {
        for (int j = 0; j < GRIND_WIDTH; ++j) {
            if (sys_map[i][j] != MINE && sys_map[i][j] != EMPTY) {
                user_map[i][j] = sys_map[i][j];
            }
        }
    }
}


// dfs algorithm
void Grind::rev_dfs(int x, int y) {
    if (!valid_pos(x, y) || sys_map[x][y] == BLANK) {
        return;
    }
    vector<vector<int>> v = { {1,-1},{1,0},{1,1},{-1,-1},{-1,0},{-1,1},{0,-1},{0,1} };
    int count = 0;
    if (sys_map[x][y] == EMPTY) {
        for (int i = 0; i < 8; i++) {
            if (valid_pos(x + v[i][0], y + v[i][1]) && sys_map[x + v[i][0]][y + v[i][1]] == MINE) {
                count++;
            }
        }
        if (count > 0) {
            sys_map[x][y] = '0' + count;
        }
        else {
            sys_map[x][y] = BLANK;
            for (int i = 0; i < 8; i++) {
                rev_dfs(x + v[i][0], y + v[i][1]);
            }
        }
    }
}


// unreveal a position
bool Grind::rev_pos(int x, int y) {
    if (not valid_pos(x, y)) {
        cout << "invalid position!" << endl;
        return false;
    }
    if (is_mine(x, y)) {
        user_map[x][y] = REV_MINE;
        cout << "hit mine!" << endl;
        return false;
    }
    rev_dfs(x, y);
    upd_user_map();
    return true;
}
