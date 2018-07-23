#include "potion.h"
#include "player.h"
#include "player_decorators.h"

using namespace std;

Potion::Potion(int p): Item('P'), potency{p} {}
bool Potion::isUsable() {return true;}
int Potion::getPotency() const {
  return potency;
}


//Set all static revealed bools to false initially.
bool Potion_RH::revealed = false;
bool Potion_PH::revealed = false;
bool Potion_BA::revealed = false;
bool Potion_WA::revealed = false;
bool Potion_BD::revealed = false;
bool Potion_WD::revealed = false;

// RH implementation
Potion_RH::Potion_RH(int p): Potion(p)  {}
bool Potion_RH::isRevealed() const {return revealed;}
void Potion_RH::reveal() {revealed = true;}
shared_ptr<Player> Potion_RH::beUsedBy(shared_ptr<Player> user) {
  reveal();
  return user->useEntity(shared_from_this());
}
/*
bool Potion_RH::wasUsed(Player **user) {
  user->modifyHp(potency);
  reveal();
  return true;
}*/

// PH implementation
Potion_PH::Potion_PH(int p): Potion(p) {}
bool Potion_PH::isRevealed() const {return revealed;}
void Potion_PH::reveal() {revealed = true;}
shared_ptr<Player> Potion_PH::beUsedBy(shared_ptr<Player> user) {
  reveal();
  return user->useEntity(shared_from_this());
}
/*
bool Potion_PH::wasUsed(Player **user) {
  user->modifyHp(-potency);
  reveal();
  return true;
}*/

// BA implementation incomplete
Potion_BA::Potion_BA(int p): Potion(p) {}
bool Potion_BA::isRevealed() const {return revealed;}
void Potion_BA::reveal() {revealed = true;}
shared_ptr<Player> Potion_BA::beUsedBy(shared_ptr<Player> user) {
  reveal();
  return user->useEntity(shared_from_this());
}
/*
bool Potion_BA::wasUsed(Player user) {
  (void)user;
  return true;
}*/

// WA implementation incomplete
Potion_WA::Potion_WA(int p): Potion(p) {}
bool Potion_WA::isRevealed() const {return revealed;}
void Potion_WA::reveal() {revealed = true;}
shared_ptr<Player> Potion_WA::beUsedBy(shared_ptr<Player> user) {
  reveal();
  return user->useEntity(shared_from_this());
}
/*
bool Potion_WA::wasUsed(Player *user) {
  (void)user;
  return true;
}*/

// BD implementation incomplete
Potion_BD::Potion_BD(int p): Potion(p) {}
bool Potion_BD::isRevealed() const {return revealed;}
void Potion_BD::reveal() {revealed = true;}
shared_ptr<Player> Potion_BD::beUsedBy(shared_ptr<Player> user) {
  reveal();
  return user->useEntity(shared_from_this());
}
/*bool Potion_BD::wasUsed(Player *user) {
  (void)user;
  return true;
}*/

// WA implementation incomplete
Potion_WD::Potion_WD(int p): Potion(p) {}
bool Potion_WD::isRevealed() const {return revealed;}
void Potion_WD::reveal() {revealed = true;}
shared_ptr<Player> Potion_WD::beUsedBy(shared_ptr<Player> user) {
  reveal();
  return user->useEntity(shared_from_this());
}
/*bool Potion_WD::wasUsed(Player *user) {
  (void)user;
  return true;
}*/
