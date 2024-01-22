#include "minesweeper.h"
#include "conf.h"

// return true if x, y is a valid pair
bool valid_pos(int x, int y) {
    if (x >= GRID_HEIGHT || x < 0) {
        return false;
    }
    if (y >= GRID_WIDTH || y < 0) {
        return false;
    }
    return true;
}

Grid::Grid() {
    first_click = true;
    click_count = 0;
    user_map = {};
    sys_map = {};
    empty_blocks = {};
    v = { {1,-1},{1,0},{1,1},{-1,-1},{-1,0},{-1,1},{0,-1},{0,1} };
}

// initialise game variables
void Grid::init_game() {
    first_click = true;
    click_count = 0;
    init_maps();
};

// initialise maps
void Grid::init_maps() {
    srand(time(0));  // set random seed
    init_empty_blocks();
    init_sys_map();
    init_user_map();
    gen_mines(MAX_MINES);
}

void Grid::init_empty_blocks() {
    empty_blocks.clear();
    for (int i = 0; i < GRID_HEIGHT; ++i) {
        for (int j = 0; j < GRID_WIDTH; ++j) {
            empty_blocks.push_back(std::make_pair(i, j));
        }
    }
    random_shuffle(empty_blocks.begin(), empty_blocks.end());
}

// initialise system map
void Grid::init_sys_map() {
    sys_map.clear();
    for (int i = 0; i < GRID_HEIGHT; ++i) {
        std::vector<char> col(GRID_WIDTH, BLANK);
        sys_map.push_back(col);
    }
}

// initialise user map
void Grid::init_user_map() {
    user_map.clear();
    for (int i = 0; i < GRID_HEIGHT; ++i) {
        std::vector<char> col(GRID_WIDTH, UNREV);
        user_map.push_back(col);
    }
}

// @param idx = `0` sys_map | `1` user_map
void Grid::print_map(int idx) {
    // print index
    std::cout << std::setw(2) << ' ';
    for (int i = 0; i < GRID_WIDTH; ++i) {
        std::cout << std::setw(2) << i;
    }
    std::cout << '\n';
    
    if(idx == 0) {
        for (int i = 0; i < sys_map.size(); ++i) {
            std::cout << std::setw(2) << std::right << i;
            for (int j = 0; j < sys_map[0].size(); ++j) {
                std::cout << std::setw(2) << sys_map[i][j];
            }
            std::cout << '\n';
        }
    }
    else if (idx == 1){
        for (int i = 0; i < user_map.size(); ++i) {
            std::cout << std::setw(2) << i ;
            for (int j = 0; j < user_map[0].size(); ++j) {
                std::cout << std::setw(2) << user_map[i][j];
            }
            std::cout << '\n';
        }
    }
    else {
        std::cout << "invalid output index" << std::endl;
    }
}

void Grid::inc_cells(int x, int y) {
    for (int i = 0; i < 8; i++) {
        if (valid_pos(x + v[i][0], y + v[i][1]) && sys_map[x + v[i][0]][y + v[i][1]] != MINE) {
            sys_map[x + v[i][0]][y + v[i][1]]++;
        }
    }
}

// generate mines in the map
void Grid::gen_mines(int mines) {
    for (int i = 0; i < mines; ++i) {
        std::pair<int, int> xys = empty_blocks.back();
        empty_blocks.pop_back();
        sys_map[xys.first][xys.second] = MINE;
        inc_cells(xys.first, xys.second);
    }
}

// @return true if mine hit
bool Grid::is_mine(int x, int y) {
    return sys_map[x][y] == MINE;
}

void Grid::alt_mine(int x, int y) {
    // reverse the surrounding cells
    for (int i = 0; i < 8; i++) {
        if (valid_pos(x + v[i][0], y + v[i][1]) && sys_map[x + v[i][0]][y + v[i][1]] != MINE) {
            sys_map[x + v[i][0]][y + v[i][1]]--;
        }
    }
    // calculate the number on the cell
    sys_map[x][y] = BLANK;
    for (int i = 0; i < 8; i++) {
        if (valid_pos(x + v[i][0], y + v[i][1]) && sys_map[x + v[i][0]][y + v[i][1]] == MINE) {
            sys_map[x][y]++;
        }
    }
    gen_mines(1);
    empty_blocks.push_back(std::make_pair(x, y));
}

// @return true if player wins
bool Grid::check_win() {
    return click_count == BLOCKS - MAX_MINES;
}

/*
* @param axis int x, int y
* @return char at axis in user_map
*/
char Grid::get_user_pos(int x, int y) {
    return user_map[x][y];
}

// dfs algorithm
void Grid::click_dfs(int x, int y, std::vector<Cell>& cells) {
    if (!valid_pos(x, y) || user_map[x][y] != UNREV) {
        return;
    }
    if (user_map[x][y] != FLAG) {
        char nearby_mines = sys_map[x][y];
        if (nearby_mines > '0') {
            user_map[x][y] = nearby_mines;
            cells.push_back({ x, y, nearby_mines });
        }
        else {
            cells.push_back({ x, y, BLANK });
            user_map[x][y] = BLANK;
            for (int i = 0; i < 8; i++) {
                click_dfs(x + v[i][0], y + v[i][1], cells);
            }
        }
        click_count++;
    }
    return;
}

// click a position
void Grid::click_pos(int x, int y, std::vector<Cell> &cells) {
    if (!valid_pos(x, y)) {
        return;
    }
    if (first_click && sys_map[x][y] == MINE) {
        alt_mine(x, y);
    }
    first_click = false;
    if (is_mine(x, y)) {
        if (user_map[x][y] != FLAG) {
            user_map[x][y] = MINE_REV;
            cells.push_back({ x, y, MINE_REV });
            game_over = true;
            refresh_timer = false;  // stop timer
            // check wrongly flagged position
            for (int i = 0; i < sys_map.size(); ++i) {
                for (int j = 0; j < sys_map[0].size(); ++j) {
                    if (sys_map[i][j] != MINE && user_map[i][j] == FLAG) {
                        cells.push_back({ i, j, FLAG_WRONG });
                    }
                }
            }
        }
        return;
    }
    click_dfs(x, y, cells);
    for (int i = 0; i < 8; i++) {
        if (valid_pos(x + v[i][0], y + v[i][1]) && sys_map[x + v[i][0]][y + v[i][1]] == BLANK) {
            click_dfs(x + v[i][0], y + v[i][1], cells);
        }
    }
}

// @return true: set flag | false: cancel flag
bool Grid::flag_mine(int x, int y) {
    if (user_map[x][y] == FLAG) {
        user_map[x][y] = UNREV;
        return false;
    }
    else {
        user_map[x][y] = FLAG;
        return true;
    }
}

// check wrongly flagged position
void Grid::check_wrong_flag(std::vector<Cell>& cells) {
    for (int i = 0; i < sys_map.size(); ++i) {
        for (int j = 0; j < sys_map[0].size(); ++j) {
            if (sys_map[i][j] != MINE && user_map[i][j] == FLAG) {
                cells.push_back({ i, j, FLAG_WRONG });
            }
        }
    }
}

// search a block (middle click)
void Grid::search_pos(int x, int y, std::vector<Cell>& cells) {
    char flags = '0';
    if (user_map[x][y] == UNREV) {
        return;
    }
    for (int i = 0; i < 8; i++) {
        int x_idx = x + v[i][0];
        int y_idx = y + v[i][1];
        if (valid_pos(x_idx, y_idx)) {
            if (user_map[x_idx][y_idx] == FLAG) {
                flags++;
            }
            else {
                cells.push_back({ x_idx, y_idx, sys_map[x_idx][y_idx] });
            }
        }
    }
    if (flags != sys_map[x][y]) {
        cells.clear();
    }
    for (int i = 0; i < cells.size(); ++i) {
        if (is_mine(cells[i].x, cells[i].y)) {
            cells[i].sym = MINE_REV;
            check_wrong_flag(cells);
            game_over = true;
            refresh_timer = false;  // stop timer
        }
        else {
            click_dfs(cells[i].x, cells[i].y, cells);
        }
    }
}
