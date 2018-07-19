#include "player.h"
#include "cell.h"
using namespace std;

Player::Player(int mHp): Creature(nullptr, '@'), gold{0}, maxHp{mHp} {}

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
  return target.getOccupant()->wasAttacked<Player *>(this);
}

atkStatus Player::wasAttacked(Creature *aggressor) {
  int randomAction = rand() % 2;
  if (randomAction == 0) { 
    int damage = damage(aggressor->getAtk(),getDef());    
    hp -= damage;
    return atkStatus::Hit;
  }
  else {
    return atkStatus::Miss;
  }
}


void Player::move(Cell *target) {
  this->setCell(target);
} 
