#include <iostream>
#include "drow.h"
#include "player_decorators.h"

using namespace std;

Drow::Drow(): Player("Drow", 150, 25, 15) {}

shared_ptr<Player> Drow::useEntity(shared_ptr<Potion_RH> p) {
  modifyHp(p->getPotency() * 3 / 2);
  cout << "my hp is " << getHp() << endl;
  if (getHp() >= getMaxHp()) {
    setHp(getMaxHp());
  }
  return shared_from_this();
}
shared_ptr<Player> Drow::useEntity(shared_ptr<Potion_PH> p) {
  modifyHp(-(p->getPotency()) * 3 / 2);
  return shared_from_this();
}
shared_ptr<Player> Drow::useEntity(shared_ptr<Potion_BA> p) {
  return make_shared<PlayerDecoratorAtk>(shared_from_this(), (p->getPotency()) * 3 / 2);
}
shared_ptr<Player> Drow::useEntity(shared_ptr<Potion_WA> p) {
  return make_shared<PlayerDecoratorAtk>(shared_from_this(), -(p->getPotency() * 3 / 2));
}
shared_ptr<Player> Drow::useEntity(shared_ptr<Potion_BD> p) {
  return make_shared<PlayerDecoratorDef>(shared_from_this(), p->getPotency() * 3 / 2);
}
shared_ptr<Player> Drow::useEntity(shared_ptr<Potion_WD> p) {
  return make_shared<PlayerDecoratorDef>(shared_from_this(), -(p->getPotency() * 3 /2));
}
                     
