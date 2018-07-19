#ifndef _ENEMY_H_
#define _ENEMY_H_
#include "creature.h"
#include <string>
#include <memory>

class Player;

using std::Shared_ptr;

class Enemy : public Creature, public std::enable_shared_from_this<Player> {
  public:
    Enemy(Cell cellptr, char symbol, int hp, int atk, int def);
    void attack(shared_ptr<Player> p) virtual;
    void attackText(shared_ptr<Player> p, atkStatus atkstatus);
    ~Enemy();
};
#endif