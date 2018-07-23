#include "elf.h"
#include "player.h"
#include "drow.h"

Elf::Elf(): 
  Enemy{'E', "Elf", 140, 30, 10} {}


atkStatus Elf::attack(std::shared_ptr<Player> p) {
   std::shared_ptr<Enemy> enemy(this);
   if(std::dynamic_pointer_cast<Drow>(p))return p->wasAttacked(enemy,1);
   else {
     p->wasAttacked(enemy,1);
     return p->wasAttacked(enemy,1);
   }
}

