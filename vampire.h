#ifndef _VAMPIRE_H_
#define _VAMPIRE_H_

#include <memory>
#include "player.h"

class Vampire: public Player {
  Vampire();
  atkStatus attack(Cell &target);
};

#endif
