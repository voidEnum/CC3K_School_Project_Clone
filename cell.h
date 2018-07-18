#ifndef CELL_H
#define CELL_H
#include <cstddef>
#include <memory>

class Entity;

enum class Terrain {VertWall, HoriWall, ChamFloor,
                    PassFloor, Door, Stair, Empty};

class Cell  {
  const size_t row, col;
  Terrain tile; 
  std::shared_ptr<Entity> occupant;
  int chamber;

  // Add other private members if necessary

public:
  Cell(size_t r, size_t c, Terrain t);
  int getRow() const;
  int getCol() const;
  int getChamber() const;
  Terrain getTerrain() const;

  void setChamber(int n);

};
#endif
