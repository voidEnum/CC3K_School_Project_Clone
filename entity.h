#ifndef __ENTITY_H__
#define __ENTITY_H__

#include <string>
#include "posn.h"

#include <memory>

class Creature;
class Player;

enum class atkStatus {EmptyTarget, InvalidTarget, Miss, Hit, Kill};

class Entity {
protected:
  Posn pos;
  char symbol;
  std::string name;
public:
  Entity(char sym = 'Y', std::string name = "Entity");
  virtual atkStatus wasAttacked(Creature *aggressor);
  //virtual atkStatus wasAttacked(Player *aggressor);
  virtual char getSymbol() const;
  // returns true when used successfully, false when entity cannot be used
  // or was otherwise not able to be used for some reason. User might be
  // changed to point at a decorator containing the original user.
  // User cannot be nullptr.
  virtual bool wasUsed(std::shared_ptr<Player> *user);
  virtual void setPos(Posn p);
  virtual Posn getPosn() const;
  virtual bool isUsable() const;
  // return a pointer to a player that has used this entity. will return user
  // if this entity does nothing or the entity does not need to apply a
  // decorator. May return a decorator that decorates user if this entity
  // applies a buff/debuff to user when used.
  virtual std::shared_ptr<Player> beUsedBy(std::shared_ptr<Player> user);
};

#endif
