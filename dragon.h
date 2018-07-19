#ifndef _DRAGON_H_
#define _DRAGON_H_

#include "enemy.h"

class Dragon: public Enemy {
 public:
   Dragon(shared_ptr<Cell> cellptr, shared_ptr<Cell> hoardptr);
};

#endif
