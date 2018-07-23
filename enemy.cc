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
   /*if (atkStatus == 1) {
      int PlayerHp = p->getHp();
      int PlayerDef = p->getDef();
      int myAtk = getAtk();
      int damage = damage(PlayerDef, atkStatus::Hit);
      p->setHp(PlayerHp - damage);
   }*/
  //shared_ptr<Enemy> enemy(make_shared_from_this());
  return p->wasAttacked(shared_from_this());
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

string Enemy::actionText(shared_ptr<Player>p, atkStatus as) {
  string newActionText;
  if(as == atkStatus::Hit) {
    string atkAsString = to_string(damage(p->getAtk(), getDef()));
    string enemyHpAsString = to_string(getHp());
    //cout << "the symbol: " << getSymbol() << endl;
    //cout << getPosn().r << " " << getPosn().c << endl;
    newActionText = " " + p->getName() + " deals " + atkAsString + " damage to " + getName() + "(" + enemyHpAsString + ").";
  } else {
    newActionText = " " +  p->getName() + " attacks you but it missed.";
  }
  //p->actionText(newActionText);
  return newActionText;
}
