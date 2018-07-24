#ifndef _DRAGON_H_
#define _DRAGON_H_
#include "enemy.h"

class Treasure_Dragon;

class Dragon: public Enemy {
  Treasure_Dragon* hoard;
 public:
   Dragon(Treasure_Dragon* h);
};
#endif
