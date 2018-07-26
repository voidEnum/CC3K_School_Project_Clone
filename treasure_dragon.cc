#include "treasure_dragon.h"
#include "dragon.h"

using namespace std;

Treasure_Dragon::Treasure_Dragon() : Treasure(TREASURE_DRAGON_VALUE, "Dragon Hoard"), 
                                     dragon{nullptr} {}

// returns true if the dragon is dead
bool Treasure_Dragon::canBeAdded() const {
  if (dragon && dragon->getHp() > 0) {
    return false;
  }else {
    return true;
  }
}

void Treasure_Dragon::makeDragon() {
  dragon = make_shared<Dragon>(this);
}

shared_ptr<Entity> Treasure_Dragon::getDragon() {
  return dragon;
}

shared_ptr<Enemy> Treasure_Dragon::getDragonAsEnemy() {
  return dragon;
}
