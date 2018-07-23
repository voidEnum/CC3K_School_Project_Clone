#include "vampire.h"
#include "enemy.h"

Vampire::Vampire(): Player("Vampire", 50, 25, 25) {}

atkStatus Vampire::attack(std::shared_ptr<Enemy> aggressor) {
  this->setHp(this->getHp() + 5);
  return aggressor->wasAttacked(shared_from_this());
}

