#ifndef _DRAGON_H_
#define _DRAGON_H_
#include "enemy.h"

class Treasure_DragonHoard

class Dragon: public Enemy {
  Treasure_DragonHoard* hoard;
 public:
   Dragon(Treasure_DragonHoard* h);
};
#endif
