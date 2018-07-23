#include "merchant.h"
#include "player.h"

Merchant::Merchant(): 
   Enemy{'M', "Merchant", 30, 70, 5}, isHostile{false} {}


void Merchant::turnHostile() {
  isHostile = true;
}

bool Merchant::checkHostile() {
  return isHostile;
}

atkStatus Merchant::attack(std::shared_ptr<Player> p) {
  if(checkHostile()) {
    std::shared_ptr<Enemy> enemy(this);
    return p->wasAttacked(enemy,1);
  } else return atkStatus::InvalidTarget;
}

atkStatus Merchant::wasAttacked(std::shared_ptr<Player>player) {
  turnHostile();
  this->setHp(this->getHp() - damage(player->getAtk(), getDef()));
    if (this->getHp() <= 0) {
      return atkStatus::Kill;
    }
    return atkStatus::Hit;
}
