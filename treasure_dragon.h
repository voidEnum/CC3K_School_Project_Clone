#ifndef __TREASURE_DRAGON_H__
#define __TREASURE_DRAGON_H__

#include "treasure.h"
#include <memory>

class Enemy;
class Dragon;

class Treasure_Dragon: public Treasure {
  static const int TREASURE_DRAGON_VALUE = 6;
  std::shared_ptr<Dragon> dragon;
public:
  static const int SPAWN_RATE = 1;
  Treasure_Dragon();
  void makeDragon();
  virtual bool canBeAdded() const override;
  std::shared_ptr<Entity> getDragon();
  std::shared_ptr<Enemy> getDragonAsEnemy();
};

#endif
