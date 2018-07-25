#include "treasure.h"
#include "player.h"

#include <iostream>

using namespace std;

Treasure::Treasure(int v, std::string name): Item('G', name), value{v} {}

int Treasure::getValue() const {
  return value;
}

// When players step on treasures, they gain the treasure's value in gold
/*void Treasure::beSteppedOn(Player &whoStepped) {
  cout << "this should get called" << endl;
  whoStepped.addGold(value);
}*/

void Treasure::beSteppedOn(Entity &whoStepped) {
  // Using dynamic casts for double dispatch
  // If any player steps on me, use setOnGold(shared_from_this())
  
  cout << "calling treasure beSteppedOn" << endl;
  if (Player *p = dynamic_cast<Player*>(&whoStepped)) {
    p->setOnGold(shared_from_this());
  }
  // in all other cases do nothing
}

bool Treasure::canBeAdded() const {
  return true;
}

// By default, players can step on treasure and no one else can
bool Treasure::canBeSteppedOn(const Entity &whoStepped) const{
  
  if (const Player *p = dynamic_cast<const Player*>(&whoStepped)) {
    (void)p;
    return true;
  }
  return false;
}
