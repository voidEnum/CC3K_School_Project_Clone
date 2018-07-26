#include <iostream>
#include "player.h"
#include "cell.h"
#include "enemy.h"
#include "treasure.h"
#include <cstdlib>
#include <string>
#include <cmath>
using namespace std;

Player::Player(string name, int hp, int atk, int def): 
  Creature('@', name, hp, atk, def), gold{0},
           maxHp{hp}, atkOffset{0}, defOffset{0} {}

/*void Player::usePotion(Potion &target) {
  target.occupant.applyEffect(this);
}*/

void Player::modifyHp(int delta) {
  hp = (hp + delta > maxHp) ? maxHp : hp + delta;
  hp = (hp <= 0) ? 0 : hp;  
}

int Player::finalScore() {
  return gold;
}

// for decorators
shared_ptr<Player>Player::withoutBuffs() {
  return shared_from_this();
}

void Player::removeBuffs() {
  atkOffset = 0;
  defOffset = 0;
}

void Player::setOnGold(const shared_ptr<Treasure> &onThis) {
  onGold = onThis;
}

shared_ptr<Treasure> Player::getOnGold() const {
  return onGold;
}

void Player::endTurn() {
  if (onGold && onGold->canBeAdded()) {
    addGold(onGold->getValue());
    setOnGold(nullptr);
  }
}

//bool Player::useEntity(Entity &e) {
//  return e.wasUsed(&(shared_from_this()));
//}

void Player::addGold(int reward) {
  gold += reward;
}

void Player::modifyAtkOffset(double delta){atkOffset += delta;}

double Player::getAtkOffset() const {return atkOffset;}

int Player::getAtk() const {return  (round(atk + atkOffset) <= 0) ? 0 : round(atk + atkOffset);}

void Player::modifyDefOffset(double delta){defOffset += delta;}

double Player::getDefOffset() const {return defOffset;}

int Player::getDef() const {return (round(def + defOffset) <= 0) ? 0 : round(def + defOffset);}

atkStatus Player::attack(const shared_ptr<Enemy> &aggressor) {
    return aggressor->wasAttacked(shared_from_this());
}

atkStatus Player::wasAttacked(const shared_ptr<Enemy> &aggressor, double modifiedDamage) {
  int randomAction = rand() % 2;
  if (randomAction == 0) { 
    this->setHp(this->getHp() - modifiedDamage * damage(aggressor->getAtk(), getDef()));
    if (this->getHp() <= 0) {
      setHp(0);
      return atkStatus::Kill;
    }
    return atkStatus::Hit;
  }
  else {
    return atkStatus::Miss;
  }
}

void Player::move(Posn target) {
  this->setPos(target);
} 

string Player::actionText(shared_ptr<Enemy> &aggressor, atkStatus as) {
  string newActionText;
  if(as == atkStatus::Hit) {
    string atkAsString = to_string(damage(getAtk(), aggressor->getDef()));
    string enemyHpAsString = to_string(aggressor->getHp());
    newActionText = "PC deals " + atkAsString + " damage to " + aggressor->getName() +  "(" + enemyHpAsString + ").";
  } else if (as == atkStatus::Kill){
      char sym = aggressor->getSymbol();
      if(sym != 'M' && sym != 'H' && sym != 'D') {
        int whatTreasure = rand() % 2;
        
        addGold(whatTreasure + 1);
        newActionText = "PC killed " + aggressor->getName() + ", PC earned " + to_string(whatTreasure + 1) + " gold.";
        /*if (whatTreasure == 0) {
          shared_from_this()->addGold(1);
          newActionText = "PC killed " + aggressor->getName() + ", PC earn 1 gold ";
        } else  {
          shared_from_this()->addGold(2);
          newActionText = "PC killed " + aggressor->getName() + ", PC earn 2 gold ";
        }*/
      } else newActionText = "PC killed " + aggressor->getName() + ".";
  } else if (as == atkStatus::Miss){
      newActionText = "PC attacks " + aggressor->getName() + " but it missed.";
  } else {
      newActionText = "There is no enemy at that direction.";
  }
  return newActionText; 
}
  
int Player::getGold() {
  return gold;
}

int Player::getMaxHp() {
  return maxHp;
}

void Player::beginTurn() {
}

// useEntity overloads for visitor pattern
void Player::useEntity(Potion_RH &p) {modifyHp(p.getPotency());}
void Player::useEntity(Potion_PH &p) {modifyHp(-(p.getPotency()));}
void Player::useEntity(Potion_BA &p) {modifyAtkOffset(p.getPotency());}
void Player::useEntity(Potion_BD &p) {modifyDefOffset(p.getPotency());}
void Player::useEntity(Potion_WA &p) {modifyAtkOffset(-(p.getPotency()));}
void Player::useEntity(Potion_WD &p) {modifyDefOffset(-(p.getPotency()));}

