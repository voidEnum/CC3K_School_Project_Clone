#include "enemy.h"
#include <string>
#include <cstdlib>
#include <iostream>

using namespace std;

Enemy::Enemy(shared_ptr<Cell> cellptr, char symbol, int hp, int atk, int def): 
   Creature{cellptr, symbol, hp, atk, def} {}

void Enemy::attack(shared_ptr<Player> p) {
   int atkStatus = rand() % 2;
   if (atkStatus == 1) {
      int PlayerHp = p->getHp();
      int PlayerDef = p->getDef();
      int myAtk = getAtk();
      int damage = damage(PlayerDef, atkStatus::Hit);
      p->setHp(PlayerHp - damage);
   }
   attackText(p,atkStatus); 
}

void Enemy::attackText(shared_ptr<Player> p, atkStatus atkstatus) {
  string newActionText;
  if(atkstatus == atkStatus::Hit) {
    string atkAsString = to_string(getAtk());
    string heroHpAsString = to_string(p->getHp());
    newActionText = Symbol + " deals " + atkAsString + " damage to PC " + "(" + heroHpAsString + "). ";
  } else {
    newActionText = Symbol + "attacks you but it missed";
  }
  p->actionText(newActionText);
}


