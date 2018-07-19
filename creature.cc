#include "creature.h"

Creature::Creature(Cell *c, char sym, int mhp, int h, int a, int d):
                   Entity(c, sym), maxHp{mhp}, hp{h}, atk{a}, def{d} {}

void Creature::move(Cell *target) {
  cell = target;
}

void Creature::beginTurn() {}


void Creature::endTurn() {}

int Creature::getAtk() const{
  return atk;
}

int Creature::getDef() const{
  return def;
}
