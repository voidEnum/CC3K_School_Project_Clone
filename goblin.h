#ifndef _GOBLIN_H_
#define _GOBLIN_H_

#include <memory>
#include "player.h"

class Goblin: public Player {
 public:
  Goblin();
/*<<<<<<< HEAD
  //atkStatus attack(Cell &target);
=======
>>>>>>> 431b61aa856f9bcc0545a46272958fc858411cf2*/
  std::string actionText(std::shared_ptr<Enemy>aggressor, atkStatus as) override;
};

#endif
