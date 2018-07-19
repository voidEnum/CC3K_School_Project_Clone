#ifndef _ORC_H_
#define _ORC_H_

#include "enemy.h"

class Player;

class Orc: public Enemy {
 public:
   Orc(shared_ptr<Cell> cellptr);
   void attack(shared_ptr<Player> p) override;
};

#endif
