#include "potion_WD.h"
#include "player.h"

using namespace std;

bool Potion_WD::revealed = false;

Potion_WD::Potion_WD(int p, string name): Potion(p, name) {}
bool Potion_WD::isRevealed() const {return revealed;}
void Potion_WD::reveal() {revealed = true;}
void Potion_WD::beUsedBy(Player &user) {
  reveal();
  user.useEntity(*this);
}
