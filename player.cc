#include <iostream>
#include "player.h"
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

void Player::addGold(int reward) {
  gold += reward;
}

atkStatus Player::attack(shared_ptr<Enemy> aggressor) {
    return aggressor->wasAttacked(shared_from_this());
}

atkStatus Player::wasAttacked(shared_ptr<Enemy> aggressor, int modifiedDamage) {
  int randomAction = rand() % 2;
  if (randomAction == 0) { 
    this->setHp(this->getHp() - modifiedDamage * damage(aggressor->getAtk(), getDef()));
    if (this->getHp() <= 0) {
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

string Player::actionText(shared_ptr<Enemy> aggressor, atkStatus as) {
  string newActionText;
  if(as == atkStatus::Hit) {
    string atkAsString = to_string(damage(getAtk(), aggressor->getDef()));
    string enemyHpAsString = to_string(aggressor->getHp());
    newActionText = getName() + " deals " + atkAsString + " damage to " + aggressor->getName() +  "(" + enemyHpAsString + ").";
  } else if (as == atkStatus::Kill){
      newActionText = getName() + " killed " + aggressor->getName() + ".";
  } else if (as == atkStatus::Miss){
      newActionText = getName() + " attacks " + aggressor->getName() + " but it missed.";
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
