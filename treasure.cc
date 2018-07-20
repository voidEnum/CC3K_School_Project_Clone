#include "treasure.h"

Treasure::Treasure(int v): Item(), value{v} {}

int Treasure::getValue() const {
  return value;
}
