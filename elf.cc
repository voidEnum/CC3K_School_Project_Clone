#include "elf.h"
#include "player.h"
#include <string>
#include <cstdlib>
#include <iostream>

using namespace std;

Elf::Elf(shared_ptr<Cell> cellptr): 
  Enemy{cellptr, "E", 140, 30, 10} {}

void Elf::attack(shared_ptr<Player> p) {
   int atkStatus = rand() % 2;
   if (atkStatus == 1) {
      int PlayerHp = p->getHp();
      int PlayerDef = p->getDef();
      int myAtk = getAtk();
      int damage = damage(PlayerDef, myAtk);
      if(dynamic_pointer_cast<Drow>(p)) p->setHp(PlayerHp - damage);
      else p->setHp(PlayerHp - 2 * damage);
   }
   attackText(p,atkStatus); 
}
