#include "vampire.h"
#include "cell.h"

Vampire::Vampire(): Player("Vampire", 50, 25, 25) {}

// this needs to be fixed
atkStatus Vampire::attack(Cell &target) {
  atkStatus ak = Player::attack(target);
  if (ak == atkStatus::Hit) {
    hp += 5;
  }
  return ak;
}

