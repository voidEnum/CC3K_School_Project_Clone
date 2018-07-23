#include <iostream>
#include "player.h"
#include "player_decorators.h"
#include "cell.h"
#include "enemy.h"
using namespace std;

Player::Player(string name, int hp, int atk, int def): 
  Creature('@', name, hp, atk, def), gold{0}, maxHp{hp} {}

/*void Player::usePotion(Potion &target) {
  target.occupant.applyEffect(this);
}*/


int Player::finalScore() {
  return gold;
}

shared_ptr<Player>Player::withoutBuffs() {
  return shared_from_this();
}

//bool Player::useEntity(Entity &e) {
//  return e.wasUsed(&(shared_from_this()));
//}

void Player::addGold(int reward) {
  gold += reward;
}

atkStatus Player::attack(Cell &target) {
  if (target.getOccupant() == nullptr) {
    return atkStatus::EmptyTarget;
  }
  char entity_sym = target.getOccupant()->getSymbol();
  if (entity_sym == 'E' || entity_sym == 'M' ||
      entity_sym == 'H' || entity_sym == 'E' ||
      entity_sym == 'W' || entity_sym == 'D') {
    shared_ptr<Enemy> enemy = static_pointer_cast<Enemy>(target.getOccupant());
    shared_ptr<Player> player(this);
    return enemy->wasAttacked(player);
  }
  return atkStatus::InvalidTarget;
}

atkStatus Player::wasAttacked(Creature *aggressor) {
  int randomAction = rand() % 2;
  if (randomAction == 0) { 
    hp -= damage(aggressor->getAtk(), getDef());
    if (hp <= 0) {
      return atkStatus::Kill;
    }
    //cout << "hit" <<endl;
    return atkStatus::Hit;
  }
  else {
    //cout << "miss" <<endl;
    return atkStatus::Miss;
  }
}

void Player::move(Posn target) {
  this->setPos(target);
} 

string Player::actionText(Creature *aggressor) {
 string newActionText;
  if(wasAttacked(aggressor) == atkStatus::Hit) {
    string atkAsString = to_string(damage(getAtk(), aggressor->getDef()));
    string enemyHpAsString = to_string(aggressor->getHp());
    newActionText = getSymbol() + " deals " + atkAsString + " damage to PC " + "(" + enemyHpAsString + "). ";
  } else {
    newActionText = aggressor->getSymbol() + "attacks you but it missed";
  }
  //p->actionText(newActionText);
  return newActionText; 
}
  
int Player::getGold() {
  return gold;
}

void Player::beginTurn() {
}

// useEntity overloads for visitor pattern
/*
shared_ptr<Player> Player::useEntity(shared_ptr<Potion> p) {
  (void)p;
  cout << "this is getting called because everyone hates me" << endl;
  return shared_from_this();
}*/
shared_ptr<Player> Player::useEntity(shared_ptr<Potion_RH> p) {
  modifyHp(p->getPotency());
  cout << "my hp is " << getHp() << endl;
  return shared_from_this();
}
shared_ptr<Player> Player::useEntity(shared_ptr<Potion_PH> p) {
  modifyHp(-(p->getPotency()));
  return shared_from_this();
}
shared_ptr<Player> Player::useEntity(shared_ptr<Potion_BA> p) {
  return make_shared<PlayerDecoratorAtk>(shared_from_this(), p->getPotency());
}
shared_ptr<Player> Player::useEntity(shared_ptr<Potion_WA> p) {
  return make_shared<PlayerDecoratorAtk>(shared_from_this(), -(p->getPotency()));
}
shared_ptr<Player> Player::useEntity(shared_ptr<Potion_BD> p) {
  return make_shared<PlayerDecoratorDef>(shared_from_this(), p->getPotency());
}
shared_ptr<Player> Player::useEntity(shared_ptr<Potion_WD> p) {
  return make_shared<PlayerDecoratorDef>(shared_from_this(), -(p->getPotency()));
}
