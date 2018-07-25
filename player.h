#ifndef _PLAYER_H_
#define _PLAYER_H_
#include "creature.h"
#include "potion.h"
#include <memory>
#include <string>
#include "enemy.h"
class Treasure;

class Player: public Creature, public std::enable_shared_from_this<Player> {
  int gold;
  int maxHp;
  double atkOffset;
  double defOffset;
  std::shared_ptr<Treasure> onGold;
public:
  virtual void modifyHp(int delta) override;
  virtual void modifyAtkOffset(double delta);
  virtual double getAtkOffset() const;
  virtual int getAtk() const override; 
  virtual void modifyDefOffset(double delta);
  virtual double getDefOffset() const;
  virtual int getDef() const override;
  virtual void removeBuffs();
  virtual void setOnGold(const std::shared_ptr<Treasure> &onThis);
  std::shared_ptr<Treasure> getOnGold() const;
  Player(std::string name, int hp = 100, int atk = 50, int def = 50);
  virtual atkStatus attack(const std::shared_ptr<Enemy> &aggressor);
  virtual atkStatus wasAttacked(const std::shared_ptr<Enemy> &aggressor, double modifiedDamage);
  virtual std::string actionText(std::shared_ptr<Enemy> &aggressor, atkStatus as);
  virtual int getMaxHp();
  virtual void move(Posn p);
  //virtual void beginTurn();
  virtual void endTurn() override;
  virtual void addGold(int reward);
  //bool useEntity(Cell &cell);
  virtual int finalScore();
  virtual std::shared_ptr<Player> withoutBuffs();
  virtual int getGold();
  virtual void beginTurn();
  //useEntity overloads for visitor pattern
  virtual void useEntity(Potion_RH &p);
  virtual void useEntity(Potion_PH &p);
  virtual void useEntity(Potion_BA &p);
  virtual void useEntity(Potion_BD &p);
  virtual void useEntity(Potion_WA &p);
  virtual void useEntity(Potion_WD &p);
private:
  static int ceil_divide(int numerator, int denom);
};

#endif
