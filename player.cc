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

atkStatus Player::attack(Cell &target) {
  if (target.getOccupant() == nullptr) {
    return atkStatus::EmptyTarget;
  }
  char entity_sym = target.getOccupant()->getSymbol();
  if (entity_sym == 'E' || entity_sym == 'M' ||
      entity_sym == 'H' || entity_sym == 'E' ||
      entity_sym == 'W' || entity_sym == 'D') {
    shared_ptr<Enemy> enemy = static_pointer_cast<Enemy>(target.getOccupant());
    //shared_ptr<Player> player(this);
    return enemy->wasAttacked(shared_from_this());
  }
  return atkStatus::InvalidTarget;
}

atkStatus Player::wasAttacked(shared_ptr<Enemy> aggressor) {
  int randomAction = rand() % 2;
  if (randomAction == 0) { 
    cout << damage(aggressor->getAtk(), getDef()) << endl;
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

string Player::actionText(shared_ptr<Enemy>aggressor, atkStatus as) {
 string newActionText;
  if(as == atkStatus::Hit) {
    string atkAsString = to_string(damage(aggressor->getAtk(), getDef()));
    string PlayerHpAsString = to_string(getHp());
    newActionText = " " + aggressor->getName() + " deals " + atkAsString + " damage to PC " + "(" + PlayerHpAsString + ").";
  } else {
    newActionText = " " + aggressor->getName() + " attacks you but it missed.";
  }
  //p->actionText(newActionText);
  return newActionText; 
}
  
int Player::getGold() {
  return gold;
}

void Player::beginTurn() {
}
