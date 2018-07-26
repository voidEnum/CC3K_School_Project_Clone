#ifndef POTION_RH_H
#define POTION_RH_H
#include "potion.h"

class Player;

class Potion_RH : public Potion{
  static bool revealed;
public:
  // How likely something is to spawn, relative to other things derived from
  // the same baseclass. SPAWN_RATE = 0 means the object will not spawn during
  // random generation except under special circumstances.
  static const int SPAWN_RATE = 1;
  Potion_RH(int p = 10, std::string name = "RH");
  bool isRevealed() const override;
  void reveal() override;
  virtual void beUsedBy(Player &user);
};

#endif
