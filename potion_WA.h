#ifndef _POTION_WA_H
#define _POTION_WA_H
#include "potion.h"

class Player;

class Potion_WA : public Potion {
  static bool revealed;
public:
  static const int SPAWN_RATE = 1;
  Potion_WA(int p = 5, std::string name = "WA");
  bool isRevealed() const override;
  void reveal() override;
  virtual void beUsedBy(Player &user);
};

#endif
