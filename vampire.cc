#include "vampire.h"
#include "cell.h"

Vampire::Vampire(): Player("Vampire", 50, 25, 25) {}

atkStatus Vampire::attack(Cell &target) {
  if (target.getOccupant() == nullptr) {
    return atkStatus::EmptyTarget;
  }
  this->setHp(this->getHp() + 5);
  return target.getOccupant()->wasAttacked(shared_from_this());
}

