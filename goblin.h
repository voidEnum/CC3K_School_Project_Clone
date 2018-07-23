#ifndef _GOBLIN_H_
#define _GOBLIN_H_

#include <memory>
#include "player.h"

class Goblin: public Player {
 public:
  Goblin();
  std::string actionText(std::shared_ptr<Enemy>aggressor, atkStatus as);
};

#endif
