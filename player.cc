#include "player.h"
#include "cell.h"
using namespace std;

Player::Player(): Creature('@', "Player"), gold{0} {}

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

/*atkStatus Player::attack(Cell &target) {
  if (target.getOccupant() == nullptr) {
    return atkStatus::EmptyTarget;
  }
  return target.getOccupant()->wasAttacked<Player *>(this);
}*/

/*int ceil_divide(int numerator, int denom) {
  if (numerator % denom == 0) {
    return numerator / denom;
  }
  return (numerator / denom) + 1;
}*/

atkStatus Player::wasAttacked(Creature *aggressor) {
  int randomAction = rand() % 2;
  if (randomAction == 0) { 
    hp -= damage(aggressor->getAtk(), getDef());
    return atkStatus::Hit;
  }
  else {
    return atkStatus::Miss;
  }
}

void Player::move(Posn target) {
  this->setPos(target);
} 

void Player::die() {
  pos = {-1,-1};
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
  
