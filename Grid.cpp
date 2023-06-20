#include <random>
#include "Grid.h"

void Grid::neighbours(int x, int y, const std::function<void(int, int)> &function)
{
    function(x,y+1);
    function(x,y-1);
    function(x+1,y);
    function(x-1,y);
    function(x+1,y+1);
    function(x-1,y+1);
    function(x+1,y-1);
    function(x-1,y-1);
}
void Grid::increase_value(int x, int y)
{
    if(in_bounds(x,y) && tiles[x][y].value!=9)
    {
        tiles[x][y].value++;
    }
}
void Grid::reveal_tile(int x, int y)
{
    if(!in_bounds(x,y) || tiles[x][y].mode==Tile::REVEALED)
    {
        return;
    }
    tiles[x][y].mode=Tile::REVEALED;
    revealed_tiles++;
    if(revealed_tiles== width * height - num_of_mines)
    {
        game_state=YOU_WIN;
    }
    if(tiles[x][y].value==0)
    {
        auto RevealTileFunc=[this](int x, int y){reveal_tile(x, y);};
        neighbours(x, y, RevealTileFunc);
    }
}
void Grid::create_mines(int x, int y)
{
    unsigned int seed=std::random_device{}();
    std::mt19937 rng(seed);
    int indexes[width * height];
    int tiles_removed=0;
    for(int i=0; i< width * height; i++)
    {
        indexes[i]=i;
    }
    if(in_bounds(x+1,y+1))
    {
        indexes[(y+1)*width+x+1]=indexes[width * height - 1 - tiles_removed];
        tiles_removed++;
    }
    if(in_bounds(x,y+1))
    {
        indexes[(y+1)*width+x]=indexes[width * height - 1 - tiles_removed];
        tiles_removed++;
    }
    if(in_bounds(x-1,y+1))
    {
        indexes[(y+1)*width+x-1]=indexes[width * height - 1 - tiles_removed];
        tiles_removed++;
    }
    if(in_bounds(x+1,y))
    {
        indexes[y*width+x+1]=indexes[width * height - 1 - tiles_removed];
        tiles_removed++;
    }
    indexes[y*width+x]=indexes[width * height - 1 - tiles_removed];
    tiles_removed++;
    if(in_bounds(x-1,y))
    {
        indexes[y*width+x-1]=indexes[width * height - 1 - tiles_removed];
        tiles_removed++;
    }
    if(in_bounds(x+1,y-1))
    {
        indexes[(y-1)*width+x+1]=indexes[width * height - 1 - tiles_removed];
        tiles_removed++;
    }
    if(in_bounds(x,y-1))
    {
        indexes[(y-1)*width+x]=indexes[width * height - 1 - tiles_removed];
        tiles_removed++;
    }
    if(in_bounds(x-1,y-1))
    {
        indexes[(y-1)*width+x-1]=indexes[width * height - 1 - tiles_removed];
        tiles_removed++;
    }
    for(int i=0; i<num_of_mines; i++)
    {
        unsigned int chosen=rng()%(width * height - tiles_removed);
        int new_x=indexes[chosen]%width;
        int new_y=indexes[chosen]/width;
        tiles[new_x][new_y].value=9;
        auto IncreaseValueFunc=[this](int new_x, int new_y){increase_value(new_x, new_y);};
        neighbours(new_x, new_y, IncreaseValueFunc);
        indexes[chosen]=indexes[width * height - 1 - tiles_removed];
        tiles_removed++;
    }
}