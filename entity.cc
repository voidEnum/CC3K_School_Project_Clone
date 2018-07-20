#include "entity.h"

#include "posn.h"

char Entity::getSymbol() const {
  return symbol;
}

atkStatus Entity::wasAttacked(Creature *aggressor) {
  (void)aggressor;
  return atkStatus::InvalidTarget;
}

Entity::Entity(Posn p = {-1, -1}, char sym = 'Y'): pos{p}, symbol{sym} {}

void Entity::setPos(Posn p) {
  pos = p;
}

Posn Entity::getPosn() const {
  return pos;
}
