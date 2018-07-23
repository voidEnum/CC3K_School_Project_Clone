#include "dwarf.h"
#include "player.h"
#include "vampire.h"

Dwarf::Dwarf(): 
   Enemy{'W', "Dwarf", 100, 20, 30} {}

atkStatus Dwarf::wasAttacked(std::shared_ptr<Player>player) {
  if(std::dynamic_pointer_cast<Vampire>(player)) this->setHp(this->getHp() - 10);
  this->setHp(this->getHp() - damage(player->getAtk(), getDef()));
  if (this->getHp() <= 0) {
    return atkStatus::Kill;
  }
  return atkStatus::Hit;
}
