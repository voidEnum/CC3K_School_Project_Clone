#include "vampire.h"
#include "enemy.h"

Vampire::Vampire(): Player("Vampire", 50, 25, 25) {}

/*
<<<<<<< HEAD
// this needs to be fixed
atkStatus Vampire::attack(Cell &target) {
  atkStatus ak = Player::attack(target);
  if (ak == atkStatus::Hit) {
    hp += 5;
  }
  return ak;
=======
*/
atkStatus Vampire::attack(const std::shared_ptr<Enemy> &aggressor) {
  setHp(getHp() + 5);
  return aggressor->wasAttacked(shared_from_this());
}

