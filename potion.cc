#include "potion.h"
#include "player.h"


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


//Set all static revealed bools to false initially.
bool Potion_RH::revealed = false;
bool Potion_PH::revealed = false;
bool Potion_BA::revealed = false;
bool Potion_WA::revealed = false;
bool Potion_BD::revealed = false;
bool Potion_WD::revealed = false;

// All implementations of beUsedBy are made with the visitor pattern,
// modified slightly to use shared_pointers

// RH implementation
Potion_RH::Potion_RH(int p, string name): Potion(p, name)  {}
bool Potion_RH::isRevealed() const {return revealed;}
void Potion_RH::reveal() {revealed = true;}
void Potion_RH::beUsedBy(Player &user) {
  reveal();
  user.useEntity(*this);
}

/*
shared_ptr<Player> Potion_RH::beUsedBy(shared_ptr<Player> user) {
  reveal();
  return user->useEntity(shared_from_this());
}*/

// PH implementation
Potion_PH::Potion_PH(int p, string name): Potion(p, name) {}
bool Potion_PH::isRevealed() const {return revealed;}
void Potion_PH::reveal() {revealed = true;}
void Potion_PH::beUsedBy(Player &user) {
  reveal();
  user.useEntity(*this);
}
/*
shared_ptr<Player> Potion_PH::beUsedBy(shared_ptr<Player> user) {
  reveal();
  return user->useEntity(shared_from_this());
}*/

// BA implementation incomplete
Potion_BA::Potion_BA(int p, string name): Potion(p, name) {}
bool Potion_BA::isRevealed() const {return revealed;}
void Potion_BA::reveal() {revealed = true;}
void Potion_BA::beUsedBy(Player &user) {
  reveal();
  user.useEntity(*this);
}
/*
shared_ptr<Player> Potion_BA::beUsedBy(shared_ptr<Player> user) {
  reveal();
  return user->useEntity(shared_from_this());
}*/

// WA implementation incomplete
Potion_WA::Potion_WA(int p, string name): Potion(p, name) {}
bool Potion_WA::isRevealed() const {return revealed;}
void Potion_WA::reveal() {revealed = true;}
void Potion_WA::beUsedBy(Player &user) {
  reveal();
  user.useEntity(*this);
}
/*
shared_ptr<Player> Potion_WA::beUsedBy(shared_ptr<Player> user) {
  reveal();
  return user->useEntity(shared_from_this());
}*/

// BD implementation incomplete
Potion_BD::Potion_BD(int p, string name): Potion(p, name) {}
bool Potion_BD::isRevealed() const {return revealed;}
void Potion_BD::reveal() {revealed = true;}
void Potion_BD::beUsedBy(Player &user) {
  reveal();
  user.useEntity(*this);
}
/*
shared_ptr<Player> Potion_BD::beUsedBy(shared_ptr<Player> user) {
  reveal();
  return user->useEntity(shared_from_this());
}*/

// WA implementation incomplete
Potion_WD::Potion_WD(int p, string name): Potion(p, name) {}
bool Potion_WD::isRevealed() const {return revealed;}
void Potion_WD::reveal() {revealed = true;}
void Potion_WD::beUsedBy(Player &user) {
  reveal();
  user.useEntity(*this);
}
/*
shared_ptr<Player> Potion_WD::beUsedBy(shared_ptr<Player> user) {
  reveal();
  return user->useEntity(shared_from_this());
}*/
