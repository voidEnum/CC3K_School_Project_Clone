#ifndef _DROW_H_
#define _DROW_H_

#include <memory>
#include "player.h"

class Drow: public Player {
 public:
  Drow();  
  std::shared_ptr<Player> useEntity(std::shared_ptr<Potion_RH> p);
  std::shared_ptr<Player> useEntity(std::shared_ptr<Potion_PH> p);
  std::shared_ptr<Player> useEntity(std::shared_ptr<Potion_BA> p);
  std::shared_ptr<Player> useEntity(std::shared_ptr<Potion_WA> p);
  std::shared_ptr<Player> useEntity(std::shared_ptr<Potion_BD> p);
  std::shared_ptr<Player> useEntity(std::shared_ptr<Potion_WD> p);
};

#endif

