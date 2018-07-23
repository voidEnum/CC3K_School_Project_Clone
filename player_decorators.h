#ifndef __PLAYER_DECORATORS_H__
#define __PLAYER_DECORATORS_H__

#include "player.h"

class PlayerDecorator : public Player {
protected:
  std::shared_ptr<Player> thePlayer;
  PlayerDecorator(std::shared_ptr<Player> p);
public:
  // Needed to remove decorators from player at end of floor
  std::shared_ptr<Player> withoutBuffs() final override;

  //Entity Virtual Functions
  virtual atkStatus wasAttacked(Creature *aggressor) override;
  virtual char getSymbol() const override;
  virtual bool wasUsed(std::shared_ptr<Player> *user) override;
  virtual void setPos(Posn p) override;
  virtual Posn getPosn() const override;
  virtual bool isUsable() const override;
  virtual std::shared_ptr<Player> beUsedBy(std::shared_ptr<Player> user) override;

  //Creature Virtual Functions
  virtual void beginTurn() override;
  virtual void endTurn() override;
  virtual int getAtk() const override;
  virtual int getDef() const override;
  virtual int getHp() const override;
  virtual std::string getName() const override;
  virtual int damage(int atk, int def) override;
  virtual void modifyHp(int delta) override;

  //Player Virtual Functions
  virtual atkStatus attack(Cell &target) override;
  virtual void move(Posn p) override;
  virtual void addGold(int reward) override;
  virtual int finalScore() override;
  virtual std::string actionText(Creature * aggressor) override;
  virtual int getGold() override;
  virtual std::shared_ptr<Player> useEntity(std::shared_ptr<Potion_RH> p) override;
  virtual std::shared_ptr<Player> useEntity(std::shared_ptr<Potion_PH> p) override;
  virtual std::shared_ptr<Player> useEntity(std::shared_ptr<Potion_BA> p) override;
  virtual std::shared_ptr<Player> useEntity(std::shared_ptr<Potion_WA> p) override;
  virtual std::shared_ptr<Player> useEntity(std::shared_ptr<Potion_BD> p) override;
  virtual std::shared_ptr<Player> useEntity(std::shared_ptr<Potion_WD> p) override;
};

class PlayerDecoratorAtk : public PlayerDecorator, 
      public std::enable_shared_from_this<PlayerDecoratorAtk> {
  int adjustment;
public:
  PlayerDecoratorAtk(std::shared_ptr<Player> p, int n);
  virtual int getAtk() const override;
};

class PlayerDecoratorDef : public PlayerDecorator, 
      public std::enable_shared_from_this<PlayerDecoratorDef> {
  int adjustment;
public:
  PlayerDecoratorDef(std::shared_ptr<Player> p, int n);
  virtual int getDef() const override;
};

#endif
