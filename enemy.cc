#include "enemy.h"
#include <string>
#include <cstdlib>
#include <iostream>
#include "player.h"
using namespace std;

Enemy::Enemy(string name, int hp, int atk, int def): 
  Creature('E', name, hp, atk, def) {} 

Enemy::~Enemy(){}

atkStatus Enemy::attack(shared_ptr<Player> p) {
   /*if (atkStatus == 1) {
      int PlayerHp = p->getHp();
      int PlayerDef = p->getDef();
      int myAtk = getAtk();
      int damage = damage(PlayerDef, atkStatus::Hit);
      p->setHp(PlayerHp - damage);
   }*/
  return p->wasAttacked(this);
  //attackText(p,atkStatus); 
}

atkStatus Enemy::wasAttacked(shared_ptr<Creature>player) {
  int randomAction = rand() % 2;
  if (randomAction == 0) {
    hp -= damage(player->getAtk(), getDef());
    if (hp <= 0) {
      return atkStatus::Kill;
    }
    return atkStatus::Hit;
  }
  else {
    return atkStatus::Miss;
  }
}

string Enemy::actionText(shared_ptr<Player>p) {
  string newActionText;
  if(wasAttacked(p) == atkStatus::Hit) {
    string atkAsString = to_string(damage(getAtk(), p->getDef()));
    string heroHpAsString = to_string(p->getHp());
    //cout << "the symbol: " << getSymbol() << endl;
    //cout << getPosn().r << " " << getPosn().c << endl;
    newActionText = " " + getName() + " deals " + atkAsString + " damage to PC " + "(" + heroHpAsString + ")";
  } else {
    newActionText = p->getSymbol() + "attacks you but it missed";
  }
  //p->actionText(newActionText);
  return newActionText;
}
