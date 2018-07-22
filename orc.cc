#include "orc.h"


Orc::Orc(): 
  Enemy{'O', "Orc", 180, 30, 25} {}

/*
void Orc::attack(shared_ptr<Player> p) {
   int atkStatus = rand() % 2;
   if (atkStatus == 1) {
      int PlayerHp = p->getHp();
      int PlayerDef = p->getDef();
      int myAtk = getAtk();
      int damage = damage(PlayerDef, myAtk);
      if(dynamic_pointer_cast<Goblins>(p)) p->setHp(PlayerHp - 1.5 * damage);
      else p->setHp(PlayerHp - damage);
   }
   attackText(p,atkStatus); 
}
*/
