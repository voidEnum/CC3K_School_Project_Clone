#include "entity.h"

char Entity::getSymbol() const {
  return symbol;
}

Entity::Entity(Cell *c = nullptr, char sym = 'Y'): cell{c}, symbol{sym} {}

void Entity::setCell(Cell *c) {
  cell = c;
}
