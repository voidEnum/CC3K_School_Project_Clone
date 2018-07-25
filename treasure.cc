#include "treasure.h"
#include "player.h"


using namespace std;

Treasure::Treasure(int v, std::string name): Item('G', name), value{v} {}

int Treasure::getValue() const {
  return value;
}

void Treasure::beSteppedOn(Entity &whoStepped) {
  // Using dynamic casts for double dispatch
  // If any player steps on me, use setOnGold(shared_from_this())
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
