#include "orc.h"
#include "player.h"
#include "goblin.h"

Orc::Orc(): 
  Enemy{'O', "Orc", 180, 30, 25} {}

atkStatus Orc::attack(std::shared_ptr<Player> p) {
  if(std::dynamic_pointer_cast<Goblin>(p)){
    return p->wasAttacked(shared_from_this(),1.5); 
  } else return p->wasAttacked(shared_from_this(),1);
}

