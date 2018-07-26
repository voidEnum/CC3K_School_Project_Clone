#include "player.h"
#include "potion.h"
using namespace std;

Potion::Potion(int p, string name): Item('P', name), potency{p} {}
// potions are by default usable
bool Potion::isUsable() const {return true;}
int Potion::getPotency() const {
  return potency;
}

string Potion::getName() const {
  if (isRevealed()) {
    return name;
  }
  else {
    return "an unknown potion";
  }
}

