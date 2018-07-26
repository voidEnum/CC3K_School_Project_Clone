#include "potion_BA.h"
#include "player.h"
using namespace std;
bool Potion_BA::revealed = false;

Potion_BA::Potion_BA(int p, string name): Potion(p, name) {}
bool Potion_BA::isRevealed() const {return revealed;}
void Potion_BA::reveal() {revealed = true;}
void Potion_BA::beUsedBy(Player &user) {
  reveal();
  user.useEntity(*this);
}

