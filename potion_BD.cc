#include "potion_BD.h"
#include "player.h"

using namespace std;

bool Potion_BD::revealed = false;

Potion_BD::Potion_BD(int p, string name): Potion(p, name) {}
bool Potion_BD::isRevealed() const {return revealed;}
void Potion_BD::reveal() {revealed = true;}
void Potion_BD::beUsedBy(Player &user) {
  reveal();
  user.useEntity(*this);
}
