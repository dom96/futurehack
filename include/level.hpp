#ifndef LEVEL_HPP
#define LEVEL_HPP

const int TILE_WIDTH = 16;
const int TILE_HEIGHT = 16;

enum TileType {
  TileNone, TileFloor, TileWall, TileWindow, TileDoor
};

struct Level {
  Level();
  ~Level();
  void Generate(int floor);
  
private:
  int tilesCountX;
  int tilesCountY;
  
  TileType** tiles;
  
};

#endif // LEVEL_HPP
