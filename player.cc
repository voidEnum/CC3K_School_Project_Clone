#include "player.h"

Player::Player(Entity &entity): Entity{entity}, gold{0} {}

void Player::usePotion(Potion &target) {
  target.occupant.applyEffect(this);
}


int Player::finalScore() {
  return gold;
}

shared_ptr<Player>Player::withoutBuffs() {
  return this;
}

void Player::addGold(int reward) {
  gold += reward;
}

atkStatus Player::attack(Cell &target) {
  if (target.occupant == nullptr) {
    return atkStatus::EmptyTarget;
  }
  return target.occupant.wasAttacked(this);
}

int Player::ceil_divide(int numerator, int denom) {
  if (numerator % denom == 0) {
    return numerator / denom;
  }
  return (numerator / denom) + 1;
}

atkStatus Player::wasAttacked(Creature &aggressor) {
  int randomAction = rand() % 2;
  if (randomAction = 0) { 
    int damage = ceil_divide(100 * aggressor.atk, 100 + def);    
    hp -= damage;
    return atkStatus::Hit;
  }
  else {
    return atkStatus::Miss;
  }
}

void Player::move(Cell &target) {
  cell = target;
} 

void Player::die() {
  cell = nullptr;
}
