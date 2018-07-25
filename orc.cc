#include "orc.h"
#include "player.h"
#include "goblin.h"
#include <string>

Orc::Orc(): 
  Enemy{'O', "Orc", 180, 30, 25} {}

atkStatus Orc::attack(std::shared_ptr<Player> p) {
  if(std::dynamic_pointer_cast<Goblin>(p)){
    return p->wasAttacked(shared_from_this(),1.5); 
  } else return p->wasAttacked(shared_from_this(),1);
}

std::string Orc::actionText(std::shared_ptr<Player>p, atkStatus as) {
  std::string newActionText;
  if(as == atkStatus::Hit) {
    std::string atkAsString = std::to_string(1.5 * damage(getAtk(),p->getDef()));
    std::string playerHpAsString = std::to_string(p->getHp());
    newActionText = " " + getName() + " deals " + atkAsString + " damage to PC" + "(" + playerHpAsString + ").";
  } else if (as == atkStatus::Miss){
    newActionText = " " + getName() + " attacks you but it missed.";
  } else if (as == atkStatus::Kill && p->getHp() >= 0){
    newActionText = " " + getName() + " killed PC.";
  }else newActionText = "";
  //p->actionText(newActionText);
  return newActionText;
}

