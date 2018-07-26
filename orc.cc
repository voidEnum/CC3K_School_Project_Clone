#include <iostream>
#include "orc.h"
#include "player.h"
#include "goblin.h"
#include <string>
#include <sstream>
#include <iomanip>
#include <cmath>

using  namespace std;

Orc::Orc(): 
  Enemy{'O', "Orc", 180, 30, 25} {}

atkStatus Orc::attack(shared_ptr<Player> p) {
  if(dynamic_pointer_cast<Goblin>(p)){ 
    return p->wasAttacked(shared_from_this(), 1.5); 
  } 
  else return p->wasAttacked(shared_from_this(),1);
}

string Orc::actionText(shared_ptr<Player>p, atkStatus as) {
  string newActionText;
  string atkAsString;
  stringstream ss;
  if(as == atkStatus::Hit) {
    if(dynamic_pointer_cast<Goblin>(p)) {
      ss << fixed << setprecision(0) << round(1.5 * damage(getAtk(), p->getDef()));
      atkAsString = ss.str();
    }
    else {
      atkAsString = to_string(damage(getAtk(), p->getDef()));
    }
    string playerHpAsString = std::to_string(p->getHp());
    newActionText = getName() + " deals " + atkAsString + " damage to PC" + "(" + playerHpAsString + ").";
  
  } else if (as == atkStatus::Miss){
    newActionText = getName() + " attacks you but it missed.";
  } else if (as == atkStatus::Kill){
    newActionText = getName() + " killed PC.";
  }else newActionText = "";
  return newActionText;
}

