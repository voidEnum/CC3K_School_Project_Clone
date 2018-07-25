#ifndef _VAMPIRE_H_
#define _VAMPIRE_H_

#include <memory>
#include "player.h"

class Enemy;

class Vampire: public Player {
 public:
  Vampire();
  void modifyHp(int delta);
  atkStatus attack(const std::shared_ptr<Enemy> &aggressor) override;
};

#endif
