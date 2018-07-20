#include "creature.h"

Creature::Creature(char sym, int mhp, int h, int a, int d):
                   Entity(sym), maxHp{mhp}, hp{h}, atk{a}, def{d} {}

void Creature::beginTurn() {}


void Creature::endTurn() {}

int Creature::getAtk() const{
  return atk;
}

int Creature::getDef() const{
  return def;
}
