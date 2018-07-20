#ifndef _ENEMY_H_
#define _ENEMY_H_
#include "creature.h"
#include <string>
#include <memory>

class Player;

class Enemy : public Creature { //, public std::enable_shared_from_this<Player> {
  public:
    Enemy();
    ~Enemy();
    atkStatus attack(std::shared_ptr<Player> p);
    atkStatus wasAttacked(std::shared_ptr<Creature> player);
    std::string actionText(std::shared_ptr<Player>p);
};

#endif
