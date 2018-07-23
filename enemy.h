#ifndef _ENEMY_H_
#define _ENEMY_H_
#include "creature.h"
#include <string>
#include <memory>

class Player;

class Enemy : public Creature , public std::enable_shared_from_this<Enemy> { //, public std::enable_shared_from_this<Player> {
  public:
    Enemy(char sym, std::string name, int hp = 150, int atk = 25, int def = 25);
    ~Enemy();
    virtual atkStatus attack(std::shared_ptr<Player> p);
    virtual atkStatus wasAttacked(std::shared_ptr<Player> player);
    virtual std::string actionText(std::shared_ptr<Player>p, atkStatus as);
};

#endif
