#ifndef GRID_H
#define GRID_H
#include <exception>
#include <iostream>
#include <vector>
#include <memory>
#include <string>

#include "textdisplay.h"
#include "cell.h"
#include "posn.h"

class MyMapNotFoundException : public std::exception {
public:
  virtual const char *what() const noexcept;
};

class Grid {
  std::vector<std::vector<Cell>> theGrid;  // The actual grid.
  std::vector<std::vector<Cell *>> chambers; // Cell* sorted into chambers
  std::shared_ptr<TextDisplay> td;  // The text display.
  int level;  // What level were on.
    // Add private members, if necessary.
  void assignChamber(Posn p, int n);
  void findChambers();
public:
  Grid();

  void init(const std::string &fname, int n); // Sets up a new grid using fname

  Cell &getCell(Posn p);
  int getWidth() const;
  int getHeight() const;

  std::vector<std::vector<Cell *>> & getChambers(); //Returns a reference to the chambers vector UNSAFE
  int getLevel() const;
  void levelUp();
  void moveEntity(Posn src, Posn dest);
  void removeEntity(Posn remFrom);
  void placeEntity(std::shared_ptr<Entity> e, Posn placeHere);

  void placeStairs(Posn placeHere);

  void printChambers();

  // checks if the cell at Posn p has a useable entity
  bool hasUsable(Posn p) const;
  // checks if the Entity e can step on the cell at Posn p
  bool canStep(Posn p, const Entity &e) const;

  friend std::ostream &operator<<(std::ostream &out, const Grid &g);
};

#endif
