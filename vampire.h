#ifndef _VAMPIRE_H_
#define _VAMPIRE_H_

#include <memory>
#include "player.h"

class Enemy;

class Vampire: public Player {
 public:
  Vampire();
  atkStatus attack(std::shared_ptr<Enemy> aggressor) override;
};

#endif
