#include <SFML/Graphics.hpp>
#include "Grid.h"

int main()
{
    const int width=12;
    const int height=12;
    const float mine_density=0.18;
    const int tile_width=32;
    Grid grid(width, height, mine_density);
    sf::RenderWindow window(sf::VideoMode(tile_width*(width + 2), tile_width * (height + 2)), "Saper"); //okno z gra
    sf::Texture tiles;
    tiles.loadFromFile("images/tiles.jpg");
    sf::Sprite s_tiles(tiles); //zaladowanie grafiki z kafelkami

    bool mines_created=false;
    while(window.isOpen())
    {
        sf::Event event{};
        while(window.pollEvent(event))
        {
            if(event.type==sf::Event::Closed)
            {
                window.close();
            }
            else if(event.type==sf::Event::MouseButtonPressed)
            {
                sf::Vector2i pos=sf::Mouse::getPosition(window);
                int x=pos.x/tile_width-1;
                int y=pos.y/tile_width-1;
                if(!grid.in_bounds(x,y))
                {
                    break;
                }
                if(event.mouseButton.button==sf::Mouse::Left)
                {
                    if(!mines_created)
                    {
                        grid.create_mines(x,y);
                        mines_created=true;
                    }
                    grid.reveal_tile(x,y);
                    if(grid[x][y].value==9) //odkrycie miny
                    {
                        grid.set_game_state(Grid::GAME_OVER);
                    }
                }
                else if(event.mouseButton.button==sf::Mouse::Right && grid[x][y].mode==Tile::COVERED) //oflagowanie
                {
                    grid[x][y].mode=Tile::FLAGGED;
                }
            }
        }
        window.clear(sf::Color::White);
        for(int i=0; i<width; i++) //rysowanie planszy
        {
            for(int j=0; j<height; j++)
            {
                //wyciecie kafelka z grafiki
                if(grid[i][j].mode==Tile::COVERED)
                {
                    s_tiles.setTextureRect(sf::IntRect(10*tile_width, grid.get_game_state()*tile_width, tile_width, tile_width));
                }
                else if(grid[i][j].mode==Tile::REVEALED)
                {
                    s_tiles.setTextureRect(sf::IntRect(grid[i][j].value*tile_width, grid.get_game_state()*tile_width, tile_width, tile_width));
                }
                else
                {
                    s_tiles.setTextureRect(sf::IntRect(11*tile_width, grid.get_game_state()*tile_width, tile_width, tile_width));
                }
                s_tiles.setPosition(float(i+1)*tile_width, float(j+1)*tile_width);
                window.draw(s_tiles);
            }
        }
        window.display();
        if(grid.get_game_state()!=Grid::STILL_PLAYING) //program reaguje tylko na zamkniecie okna po skonczeniu gry
        {
            while(window.pollEvent(event))
            {
                if(event.type==sf::Event::Closed)
                {
                    window.close();
                }
            }
        }
    }
    return 0;
}
