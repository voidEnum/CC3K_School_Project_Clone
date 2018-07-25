#include "creature.h"
using namespace std;

Creature::Creature(char sym, string name, int h, int a, int d):
                   Entity(sym, name), hp{h}, atk{a}, def{d} {}

void Creature::beginTurn() {}


void Creature::endTurn() {}

void Creature::modifyHp(int delta) {
  hp +=delta;
}

int Creature::getAtk() const{
  return atk;
}

int Creature::getDef() const{
  return def;
}

int Creature::getHp() const{
  return hp;
}

void Creature::setAtk(int newAtk) {
  atk = newAtk;
}

void Creature::setDef(int newDef) {
  def = newDef;
}

void Creature::setHp(int newHp) {
  hp = newHp;
}


string Creature::getName() const{
  return name;
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

void Creature::die() {
}

