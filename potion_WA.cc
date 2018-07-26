#include "potion_WA.h"
#include "player.h"
using namespace std;

bool Potion_WA::revealed = false;

Potion_WA::Potion_WA(int p, string name): Potion(p, name) {}
bool Potion_WA::isRevealed() const {return revealed;}
void Potion_WA::reveal() {revealed = true;}
void Potion_WA::beUsedBy(Player &user) {
  reveal();
  user.useEntity(*this);
}

