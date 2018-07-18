#include "cell.h"

using namespace std;

Cell::Cell(size_t r, size_t c, Terrain t): row{r}, col{c}, tile{t},
                                           occupant{nullptr}, chamber{0} {}

Terrain Cell::getTerrain() const {
  return tile;
}

int Cell::getRow() const {
  return row;
}

int Cell::getCol() const {
  return col;
}

int Cell::getChamber() const {
  return chamber;
}

void Cell::setChamber(int n) {
  chamber = n;
}
