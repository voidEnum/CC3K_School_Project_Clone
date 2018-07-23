#include "troll.h"

Troll::Troll(): Player("Troll", 120, 25, 15) {}

void Troll::beginTurn() {
  this->setHp(this->getHp() + 5);
  if (this->getHp() >= this->getMaxHp()) this->setHp(this->getMaxHp());
}

