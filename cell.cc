#include "cell.h"

#include "entity.h"

using namespace std;

Cell::Cell(size_t r, size_t c, Terrain t): row{r}, col{c}, tile{t},
                                           occupant{nullptr}, chamber{0} {}

int Cell::getRow() const {
  return row;
}

int Cell::getCol() const {
  return col;
}

Posn Cell::getPosn() const {
  return {getRow(), getCol()};
}

Terrain Cell::getTerrain() const {
  return tile;
}

shared_ptr<Entity> Cell::getOccupant() const {
  return occupant;
}

void Cell::setOccupant(shared_ptr<Entity> e) {
  occupant = e;
}

int Cell::getChamber() const {
  return chamber;
}

void Cell::setChamber(int n) {
  chamber = n;
}

char Cell::getSymbol() const {
  if (occupant) {
    return occupant->getSymbol();
  }else {
    switch (tile) {
      case Terrain::VertWall  : return '|';
      case Terrain::HoriWall  : return '-';
      case Terrain::ChamFloor : return '.';
      case Terrain::PassFloor : return '#';
      case Terrain::Door      : return '+';
      case Terrain::Stair    : return '\\';
      default                 : return ' ';
    }
  }
}
