#ifndef _POTION_BA_H
#define _POTION_BA_H
#include "potion.h"

class Player;

class Potion_BA : public Potion {
  static bool revealed;
public:
  static const int SPAWN_RATE = 1;
  Potion_BA(int p = 5, std::string name = "BA");
  bool isRevealed() const override;
  void reveal() override;
  virtual void beUsedBy(Player &user);
};

#endif

