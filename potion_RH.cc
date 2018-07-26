#include "potion_RH.h"
#include "player.h"
using namespace std;

bool Potion_RH::revealed = false;

Potion_RH::Potion_RH(int p, string name): Potion(p, name)  {}
bool Potion_RH::isRevealed() const {return revealed;}
void Potion_RH::reveal() {revealed = true;}
void Potion_RH::beUsedBy(Player &user) {
  reveal();
  user.useEntity(*this);
}

