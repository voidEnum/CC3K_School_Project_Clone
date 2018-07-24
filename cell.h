#ifndef CELL_H
#define CELL_H
#include <cstddef>
#include <memory>

class Entity;
struct Posn;
enum class Terrain {VertWall, HoriWall, ChamFloor,
                    PassFloor, Door, Stair, Empty};
class Player;

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
  Posn getPosn() const;
  int getChamber() const;
  std::shared_ptr<Entity> getOccupant() const;
  void setOccupant(std::shared_ptr<Entity> e);
  Terrain getTerrain() const;

  char getSymbol() const;

  void setChamber(int n);
  void makeStairs();
  bool hasUsable() const;
  
  // returns true if p is allowed to step on this tile based on terrain and
  // current occupant.
  bool canStepHere(const Entity &p) const;
};
#endif
