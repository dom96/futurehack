#ifndef LEVEL_HPP
#define LEVEL_HPP

const int TILE_WIDTH = 64;
const int TILE_HEIGHT = 64;

enum TileType {
  TileNone, TileFloor, TileWall, TileWindow, TileDoor
};

struct Level {
  Level();
  ~Level();
  void Load(int floor);
  void Generate(int floor);
  
  int levelWidth; // In tiles.
  int levelHeight; // In tiles.
  
  TileType** tiles;
  
};

#endif // LEVEL_HPP
