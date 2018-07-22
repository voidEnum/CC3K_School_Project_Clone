#include "vampire.h"
#include "cell.h"

Vampire::Vampire(): Player("Vampire", 50, 25, 25) {}

atkStatus Vampire::attack(Cell &target) {
  if (target.getOccupant() == nullptr) {
    return atkStatus::EmptyTarget;
  }
  hp += 5;
  return target.getOccupant()->wasAttacked<Player *>(this);
}

