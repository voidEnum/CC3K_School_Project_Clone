#ifndef __PLAYER_DECORATORS_H__
#define __PLAYER_DECORATORS_H__

#include "player.h"

class PlayerDecorator : public Player {
protected:
  std::shared_ptr<Player> thePlayer;
  PlayerDecorator(std::shared_ptr<Player> p);
  std::shared_ptr<Player> withoutBuffs() final override;
};

class PlayerDecoratorAtk : public PlayerDecorator {
  int adjustment;
public:
  PlayerDecoratorAtk(std::shared_ptr<Player> p, int n);
  virtual int getAtk() const;
};

class PlayerDecoratorDef : public PlayerDecorator {
  int adjustment;
public:
  PlayerDecoratorDef(std::shared_ptr<Player> p, int n);
  virtual int getDef() const;
};

#endif
