#include "goblin.h"
#include <iostream>

Goblin::Goblin(): Player("Goblin", 110, 15, 20) {}

atkStatus Goblin::attack(Cell &target) {
  atkStatus as = attack(target);
  if( as == atkStatus::Kill) addGold(5);
  return as;
}
