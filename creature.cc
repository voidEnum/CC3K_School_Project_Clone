#include "creature.h"

Creature::Creature(Cell *c, char sym, int h, int a, int d):
                   Entity(c, sym), hp{h}, atk{a}, def{d}, isAlive(true) {}

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

void Creature::die() {
  if (hp <= 0) isAlive == false;
}

bool Creature::checkAlive() const {
  return isAlive;
}

int Creature::ceil_divide(int numerator, int denom) {
  if (numerator % denom == 0) {
    return numerator / denom;
  }
  return (numerator / denom) + 1;
}

int Creature::damage(int atk, int def) {
  return ceil_divide(100 * atk, 100 + def);
}