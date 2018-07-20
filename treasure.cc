#include "treasure.h"

Treasure::Treasure(int v): Item('G'), value{v} {}

int Treasure::getValue() const {
  return value;
}
