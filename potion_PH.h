#ifndef _POTION_PH_H_
#define _POTION_PH_H_
#include "potion.h"

class Player;

class Potion_PH : public Potion{
  static bool revealed;
public:
  static const int SPAWN_RATE = 1;
  Potion_PH(int p = 10, std::string name = "PH");
  bool isRevealed() const override;
  void reveal() override;
  virtual void beUsedBy(Player &user);
};

#endif
