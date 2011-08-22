#include <iostream>

#include <cstdio>
#include <cstdlib>
#include <cmath>

#include <level.hpp>


using namespace std;

const int MAX_TILES_X = 400;
const int MAX_TILES_Y = 400;
const int MIN_TILES_X = 110;
const int MIN_TILES_Y = 110;

const int MIN_ROOM_TILES = 5;

Level::Level()
{ 
  tilesCountX = (rand() % MAX_TILES_X) + MIN_TILES_X;
  tilesCountY = (rand() % MAX_TILES_Y) + MIN_TILES_Y;
  // Allocate a 2D array.
  
  tiles = new TileType*[tilesCountX];
  for (int i = 0; i < tilesCountX; i++)
    tiles[i] = new TileType[tilesCountY];
    
  // Set all tiles to some tile.
  for (int x = 0; x < tilesCountX; x++)
    for (int y = 0; y < tilesCountY; y++)
      tiles[x][y] = TileFloor;
}

Level::~Level()
{
  // Deallocate 2D array
  for (int i = 0; i < tilesCountX; i++)
    delete [] tiles[i];
  
  delete [] tiles;
}

void Level::Generate(int level)
{
  // Generate level. *We work in tiles not pixels*.
  int curX = 0, curY = 0;
  int maxRoomWidth = int(floor(tilesCountX / 15));
  int maxRoomHeight = int(floor(tilesCountY / 15));

  while (true)
  {
    int roomWidth = (rand() % maxRoomWidth) + MIN_ROOM_TILES;
    int roomHeight = (rand() % maxRoomHeight) + MIN_ROOM_TILES;
    
    if (((curX + roomWidth) >= tilesCountX) || 
        ((curY + roomHeight) >= tilesCountY))
    {
      break;
    }

    cout << curX << " " << curY << endl;
    cout << "Max X: " << tilesCountX << endl;
    // TODO: Safer array access. Make sure it is not out of bounds.
    for (int x = 0; x <= tilesCountX-1; x++)
    {
      //tiles[curX + x][curY] = TileWall;
      tiles[x][curY + roomHeight] = TileWall;
    }
    
    
    for (int y = 0; y <= tilesCountY-1; y++)
    {
      //tiles[curX][curY + y] = TileWall;
      //tiles[curX + roomWidth][+ y] = TileWall;
    }
    
    
    curX += roomWidth;
    curY += roomHeight;
    
  }
  
  
}

