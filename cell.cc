#include "cell.h"

using namespace std;

Cell::Cell(size_t r, size_t c, Terrain  t): r{r}, c{c}, t{t}, e{nullptr} {}

Terrain Cell::getTerrain() const {
  return t;
}
