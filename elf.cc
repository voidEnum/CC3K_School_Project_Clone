#include "elf.h"
#include "player.h"
#include "drow.h"
#include <string>

using namespace std;

Elf::Elf(): 
  Enemy{'E', "Elf", 140, 30, 10} {}


string Elf::actionText(shared_ptr<Player>p, atkStatus as1) {
  if (Drow* d = dynamic_cast<Drow *>(p.get())) {
    (void)d;
    return Enemy::actionText(p, as1);
  }else {
  string newActionText;
  atkStatus as2 = attack(p);
  string atkAsString = to_string(damage(getAtk(),p->getDef()));
  string playerHpAsString = to_string(p->getHp());
  if(as1 == atkStatus::Hit && as2 == atkStatus::Hit) {
    atkAsString = to_string(2 * damage(getAtk(),p->getDef()));
    newActionText = " Elf attacks " + p->getName() + " twice deals " + atkAsString + " damage to " + p->getName() + "(" + playerHpAsString + ").";
  } else if ((as1 == atkStatus::Miss && as2 == atkStatus::Hit) || (as1 == atkStatus::Hit&& as2 == atkStatus::Miss)){
    newActionText = " Elf attacks " + p->getName() + " twice but it misses once deals " + atkAsString + " damage to " + p->getName() + "(" + playerHpAsString + ").";
  } else if ((as1 == atkStatus::Kill || as2 == atkStatus::Kill) && p->getHp() >= 0) {
    newActionText = "Elf killed the player.";
  }else newActionText = " Elf attacks " + p->getName() + " twice but it misses twice.";
  return newActionText;}
}
