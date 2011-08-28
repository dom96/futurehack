#include <iostream>
#include <SFML/Graphics.hpp>

#include <cstdio>
#include <ctime>
#include <cstdlib>
#include <cassert>

#include <world.hpp>
#include <level.hpp>
#include <game.hpp>

using namespace std;

World::World(Game *refGame) :
  game(refGame)
{
  currentLevel = maxLevels - 1; 
  levels = new Level[maxLevels];
  levels[currentLevel].Load(currentLevel);

  mapTexture.Create(levels[currentLevel].levelWidth * TILE_WIDTH,
                    levels[currentLevel].levelHeight * TILE_HEIGHT);
  mapTexture.Clear();
  DrawMap();
}

World::~World()
{
  delete [] levels;
}

void World::Update()
{
  // TODO: ...
}

// This should only be called when the level is updated.
void World::DrawMap()
{
  // Draw current level
  sf::Color floorColor = sf::Color(46, 46, 46, 255); // Dark grey
  sf::Color wallColor  = sf::Color::White;
  sf::Color windowColor = sf::Color(204, 85, 0, 255); // Orange
  sf::Color doorColor = sf::Color(0, 80, 133, 255); // Very dark blue
  
  sf::Color color = sf::Color::Green;
  sf::Shape tile;
  int tileCount = 0;
  for (int x = 0; x < levels[currentLevel].levelWidth; x++)
  {
    for (int y = 0; y < levels[currentLevel].levelHeight; y++)
    {
      switch (levels[currentLevel].tiles[x][y]) {
        case TileNone: 
          color = sf::Color::Red;
          break;
        case TileFloor:
          color = floorColor;
          break;
        case TileWall:
          color = wallColor;
          break;
        case TileWindow:
          color = windowColor;
          break;
        case TileDoor:
          color = doorColor;
          break;
        default: assert(false);
      }
      tile = sf::Shape::Rectangle(x * TILE_WIDTH, y * TILE_HEIGHT,
                                  TILE_WIDTH, TILE_HEIGHT,
                                  color);
      mapTexture.Draw(tile);
      tileCount++;
    }
  } 
  mapTexture.Display();
  cout << "Tiles rendered: " << tileCount << endl;
}

void World::Draw(sf::RenderWindow &win)
{
  sf::Sprite mapSprite(mapTexture.GetTexture());
  mapSprite.SetPosition(0, 0);
  win.Draw(mapSprite);
}

bool World::CollidesWith(TileType tile, sf::FloatRect rect)
{
  // Get tile at `pos`.
  assert(rect.Left >= 0 && rect.Top >= 0);
  int x = round(rect.Left / TILE_WIDTH);
  int y = round(rect.Top / TILE_HEIGHT);
  cout << "Tile x: " << x << " y: " << y << endl;
  cout << "Rect x: " << rect.Left << " y: " << rect.Top << endl;

  if (game->debug)
  {
    game->win.SetView(game->camera);
    sf::Shape rRect = sf::Shape::Rectangle(rect, sf::Color::Green);
    game->win.Draw(rRect);
  }

  for (int j = -1; j < 2; j++)
  { 
    for (int i = -1; i < 2; i++)
    {
      if (levels[currentLevel].tiles[x+j][y+i] == tile)
      {    
        sf::FloatRect tileRect((x+j) * TILE_WIDTH, (y+i) * TILE_HEIGHT,
                               TILE_WIDTH, TILE_HEIGHT);
        if (game->debug)
        {
          sf::Shape rTRect = sf::Shape::Rectangle(tileRect, sf::Color::Blue);
          game->win.Draw(rTRect);
        }
        if (tileRect.Intersects(rect)) return true;
      }
    }
  }

  return false;
}
