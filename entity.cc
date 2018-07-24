#include "entity.h"

#include "posn.h"

#include <iostream>

using namespace std;

char Entity::getSymbol() const {
  return symbol;
}

string Entity::getName() const {
  return name;
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

bool Entity::wasUsed(shared_ptr<Player> *user) {
  (void)user;
  return false; // defaults to return false. ovrride for usable entities
}

// default to false
bool Entity::isUsable() const {
  return false;
}

// do nothing and return player by default
shared_ptr<Player> Entity::beUsedBy(shared_ptr<Player> user) {
  return user;
}


// by default, do nothing when stepped on
void Entity::beSteppedOn(Entity &whoStepped) {
  (void)whoStepped;
}

// by default, entities cannot be stepped on
bool Entity::canBeSteppedOn(const Entity &whoStepped) const{
  (void)whoStepped;
  return false;
}

