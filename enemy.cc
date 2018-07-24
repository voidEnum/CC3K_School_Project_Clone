#include "enemy.h"
#include <string>
#include <cstdlib>
#include <iostream>
#include "player.h"
using namespace std;

Enemy::Enemy(char sym, string name, int hp, int atk, int def): 
  Creature(sym, name, hp, atk, def) {} 

Enemy::~Enemy(){}

atkStatus Enemy::attack(shared_ptr<Player> p) {
  return p->wasAttacked(shared_from_this(),1); 
}

atkStatus Enemy::wasAttacked(shared_ptr<Player>player) {
  this->setHp(this->getHp() -  damage(player->getAtk(), getDef()));
    if (this->getHp() <= 0) {
      return atkStatus::Kill;
    }
    return atkStatus::Hit;
}

string Enemy::actionText(shared_ptr<Player>p, atkStatus as) {
  string newActionText;
  if(as == atkStatus::Hit) {
    string atkAsString = to_string(damage(getAtk(),p->getDef()));
    string playerHpAsString = to_string(p->getHp());
    newActionText = " " + getName() + " deals " + atkAsString + " damage to " + p->getName() + "(" + playerHpAsString + ").";
  } else if (as == atkStatus::Miss){
    newActionText = " " + getName() + " attacks you but it missed.";
  } else if (as == atkStatus::Kill && p->getHp() >= 0){
    newActionText = " " + getName() + " killed the player.";
  }else newActionText = "";
  //p->actionText(newActionText);
  return newActionText;
}

