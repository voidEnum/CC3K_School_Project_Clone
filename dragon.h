#ifndef _DRAGON_H_
#define _DRAGON_H_
#include "enemy.h"
#include <memory>
class Treasure_Dragon;

class Dragon: public Enemy {
   Treasure_Dragon *hoard;
 public:
   Dragon(Treasure_Dragon *td);
   Treasure_Dragon * getHoard() const;
};
#endif
