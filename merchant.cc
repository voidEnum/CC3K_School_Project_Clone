#include "merchant.h"
#include "player.h"

Merchant::Merchant(): 
   Enemy{'M', "Merchant", 30, 70, 5} {}

bool Merchant::isHostile = false;


void Merchant::turnHostile() {
  isHostile = true;
}

bool Merchant::checkHostile() {
  return isHostile;
}

atkStatus Merchant::attack(std::shared_ptr<Player> p) {
  if(checkHostile()) {
    return p->wasAttacked(shared_from_this(),1);
  } else return atkStatus::InvalidTarget;
}


