#include "goblin.h"
#include <iostream>

using namespace std;

Goblin::Goblin(): Player("Goblin", 110, 15, 20) {}

string Goblin::actionText(shared_ptr<Enemy>&aggressor, atkStatus as) {
 string newActionText = Player::actionText(aggressor, as);
  if (as == atkStatus::Kill) {
    addGold(5);
    newActionText += " Goblin abilities earn you 5 extra gold.";
  } 
  return newActionText;
} 

