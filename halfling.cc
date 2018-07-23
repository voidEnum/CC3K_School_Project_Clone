#include "halfling.h"
#include "player.h"
#include "vampire.h"

Halfling::Halfling(): 
  Enemy{'L', "Halfling", 100, 15, 20} {}

atkStatus Halfling::wasAttacked(std::shared_ptr<Player>player) {
  int randomAction = rand() % 2;
  if (randomAction == 0) {
    this->setHp(this->getHp() - damage(player->getAtk(), getDef()));
    if (this->getHp() <= 0) {
      return atkStatus::Kill;
    }
    return atkStatus::Hit;
  }
  else {
    if (std::dynamic_pointer_cast<Vampire>(player)) player->setHp(player->getHp() - 5);
    return atkStatus::Miss;
  }
}
