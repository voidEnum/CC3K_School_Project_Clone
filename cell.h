#ifndef CELL_H
#define CELL_H
#include <cstddef>

class Entity;

enum class Terrain {VertWall, HoriWall, ChamFloor,
                    PassFloor, Door, Stair, Empty};

class Cell  {
  const size_t r, c;
  Terrain t; 
  Entity * e;

  // Add other private members if necessary

public:
  Cell(size_t r, size_t c, Terrain t);
  Terrain getTerrain() const;

};
#endif
