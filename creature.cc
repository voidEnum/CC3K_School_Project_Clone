#include "creature.h"

Creature::Creature(Posn p, char sym, int mhp, int h, int a, int d):
                   Entity(p, sym), maxHp{mhp}, hp{h}, atk{a}, def{d} {}

void Creature::beginTurn() {}


void Creature::endTurn() {}

int Creature::getAtk() const{
  return atk;
}

int Creature::getDef() const{
  return def;
}
