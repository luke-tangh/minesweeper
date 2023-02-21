# minesweeper
## Brief
A C++ version of a classic game minesweeper.

## Environment
- `c++ 17`
- `EasyX`

## About
**Config:**

Change the constants in `conf.h` to modify the game.

```
const int GRIND_HEIGHT = 16;
const int GRIND_WIDTH = 30;
const int MAX_MINES = 99;
```
`MAX_MINES` should not be greater than the product of `GRIND_HEIGHT` and `GRIND_WIDTH`.

**Shortkeys:**
- `LEFTCLICK` - open a cell
- `RIGHTCLICK` - flag a cell
- `MIDDLECLICK` - search from a cell
- `ESC` - exit 
- `R` - restart


## Credits
- Black Squirrel - _Winmine 31/NT4/2000+_
