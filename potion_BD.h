#ifndef _POTION_BD_H_
#define _POTION_BD_H_
#include "potion.h"

class Player;

class Potion_BD : public Potion  {
  static bool revealed;
public:
  static const int SPAWN_RATE = 1;
  Potion_BD(int p = 5, std::string name = "BD");
  bool isRevealed() const override;
  void reveal() override;
  virtual void beUsedBy(Player &user);
  //std::shared_ptr<Player> beUsedBy(std::shared_ptr<Player> user) override;
};
#endif
