#include "entity.h"

#include "posn.h"
using namespace std;

char Entity::getSymbol() const {
  return symbol;
}

atkStatus Entity::wasAttacked(Creature *aggressor) {
  (void)aggressor;
  return atkStatus::InvalidTarget;
}

Entity::Entity(char sym, string name): pos{-1, -1}, symbol{sym}, name{name} {}

void Entity::setPos(Posn p) {
  pos = p;
}

Posn Entity::getPosn() const {
  return pos;
}

bool Entity::wasUsed(Player &user) {
  (void)user;
  return false; // defaults to return false. ovrride for usable entities
}
