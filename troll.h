#ifndef _TROLL_H_
#define _TROLL_H_

#include <memory>
#include "player.h"

class Troll: public Player {
 public:
  Troll();
  void beginTurn();
};

#endif
