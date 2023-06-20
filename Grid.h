#ifndef SAPER_GRID_H
#define SAPER_GRID_H
#include <cstdlib>
#include <cstdio>
#include <ctime>
#include <vector>
#include <functional>

struct Tile
{
    enum Mode{COVERED, REVEALED, FLAGGED};
    Mode mode;
    int value; //0-8 oznacza liczbe sasiadow-min dla danego pola, 9 oznacza mine; zostawiam w tej formie bo korzystam z operatora ++ ktory inaczej musialbym przeciazyc
};

class Grid
{
public:
    Grid(int width, int height, float n): width(width), height(height), num_of_mines((int(n * float(width) * float(height)))), tiles(width, std::vector<Tile>(height)){};
    static void neighbours(int x, int y, const std::function<void(int, int)> &function);
    void increase_value(int x, int y); //kafelek zwieksza wartosc czyli liczbe sasiadow-min o jeden
    void reveal_tile(int x, int y);
    void create_mines(int x, int y);
    bool in_bounds(int x, int y) const
    {
        if(x>=0 && y>=0 && x<width && y < height)
        {
            return true;
        }
        return false;
    }
    enum Game_State{STILL_PLAYING, GAME_OVER, YOU_WIN};
    std::vector<Tile>& operator[](int i)
    {
        return tiles[i];
    }
    void set_game_state(Game_State new_game_state)
    {
        game_state=new_game_state;
    }
    Game_State get_game_state() const
    {
        return game_state;
    }
private:
    int width;
    int height;
    int num_of_mines;
    int revealed_tiles=0;
    Game_State game_state=STILL_PLAYING;
    std::vector<std::vector<Tile>> tiles;
};

#endif //SAPER_GRID_H
