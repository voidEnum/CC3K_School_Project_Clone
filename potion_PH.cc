#include "potion_PH.h"
#include "player.h"
using namespace std;

bool Potion_PH::revealed = false;

Potion_PH::Potion_PH(int p, string name): Potion(p, name) {}
bool Potion_PH::isRevealed() const {return revealed;}
void Potion_PH::reveal() {revealed = true;}
void Potion_PH::beUsedBy(Player &user) {
  reveal();
  user.useEntity(*this);
}


