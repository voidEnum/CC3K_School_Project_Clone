#include "vampire.h"
#include "enemy.h"

#include "dwarf.h"

Vampire::Vampire(): Player("Vampire", 50, 25, 25) {}

void Vampire::modifyHp(int delta) {
  hp = hp + delta;
  hp = (hp <= 0) ? 0 : hp;
}

atkStatus Vampire::attack(const std::shared_ptr<Enemy> &aggressor) {
  atkStatus result = aggressor->wasAttacked(shared_from_this());
  if (Dwarf* d = dynamic_cast<Dwarf*>(aggressor.get())) {
    (void)d;
    if (result == atkStatus::Hit || result == atkStatus::Kill) {
      modifyHp(-5);
    }
  }else {
    if (result == atkStatus::Hit || result == atkStatus::Kill) {
      modifyHp(5);
    }
  }
  return result;
}

