#include <iostream>

#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <cassert>

#include <level.hpp>
#include <utils.hpp>

using namespace std;

const int MAX_TILES_X = 400;
const int MAX_TILES_Y = 400;
const int MIN_TILES_X = 110;
const int MIN_TILES_Y = 110;

const int MIN_ROOM_TILES = 5;

Level::Level()
{ 
  levelWidth = -1;
  levelHeight = -1;
}

Level::~Level()
{
  // Deallocate 2D array
  for (int i = 0; i < levelWidth; i++)
    delete [] tiles[i];
  
  delete [] tiles;
}

void Level::Load(int level)
{
  sf::Image levelImage;
  if (!levelImage.LoadFromFile("resources/levels/" + itos(level) + ".png"))
    assert(false);
  
  levelWidth = levelImage.GetWidth(); // 1px == 1 tile.
  levelHeight = levelImage.GetHeight();
  
  tiles = new TileType*[levelWidth];
  for (int i = 0; i < levelWidth; i++)
    tiles[i] = new TileType[levelWidth];
    
  // Set all tiles to some tile.
  //for (int x = 0; x < tilesCountX; x++)
  //  for (int y = 0; y < tilesCountY; y++)
  //    tiles[x][y] = TileFloor;
   
  
  for (int x = 0; x < levelWidth; x++)
  {
    for (int y = 0; y < levelHeight; y++)
    {
      TileType tile = TileNone;
      sf::Color color = levelImage.GetPixel(x, y);
      if (color == sf::Color::White)
        tile = TileWall;
      
      tiles[x][y] = tile;
    }
  }




}


void Level::Generate(int level)
{
  // Generate level. *We work in tiles not pixels*.
  int curX = 0, curY = 0;
  int maxRoomWidth = int(floor(levelWidth / 15));
  int maxRoomHeight = int(floor(levelHeight / 15));

  while (true)
  {
    int roomWidth = (rand() % maxRoomWidth) + MIN_ROOM_TILES;
    int roomHeight = (rand() % maxRoomHeight) + MIN_ROOM_TILES;
    
    if (((curX + roomWidth) >= levelWidth) || 
        ((curY + roomHeight) >= levelHeight))
    {
      break;
    }

    cout << curX << " " << curY << endl;
    cout << "Max X: " << levelWidth << endl;
    // TODO: Safer array access. Make sure it is not out of bounds.
    for (int x = 0; x <= levelWidth-1; x++)
    {
      //tiles[curX + x][curY] = TileWall;
      tiles[x][curY + roomHeight] = TileWall;
    }
    
    
    for (int y = 0; y <= levelHeight-1; y++)
    {
      //tiles[curX][curY + y] = TileWall;
      //tiles[curX + roomWidth][+ y] = TileWall;
    }
    
    
    curX += roomWidth;
    curY += roomHeight;
    
  }
}

