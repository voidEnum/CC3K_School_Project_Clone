#include "goblin.h"
#include <iostream>

using namespace std;

Goblin::Goblin(): Player("Goblin", 110, 15, 20) {}

/*atkStatus Goblin::attack(Cell &target) {
  atkStatus as = Player::attack(target);
  if (as == atkStatus::Kill) {
    addGold(5);
  }
  return as;
} */

string Goblin::actionText(shared_ptr<Enemy>aggressor, atkStatus as) {
 //cout << "is this printed" <<endl;
 string newActionText;
  if(as == atkStatus::Hit) {
    string atkAsString = to_string(damage(getAtk(), aggressor->getDef()));
    string EnemyHpAsString = to_string(aggressor->getHp());
    newActionText = getName() + " deals " + atkAsString + " damage to " + aggressor->getName() + "(" + EnemyHpAsString + ").";
  }
  else if (as == atkStatus::Kill) {
    addGold(5);
    newActionText = getName() + " killed " + aggressor->getName() + ".";
  }
  else {
    newActionText = getName() + " attacks " + aggressor->getName() +  " but it missed.";
  }
  //p->actionText(newActionText);
  return newActionText;
} 
