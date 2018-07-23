#include "player_decorators.h"

using namespace std;

PlayerDecorator::PlayerDecorator(shared_ptr<Player> p): Player("decorator"),
                                                        thePlayer{p} {}

shared_ptr<Player> PlayerDecorator::withoutBuffs() {return thePlayer;}

// PlayerDecoratorAtk Implementation
PlayerDecoratorAtk::PlayerDecoratorAtk(shared_ptr<Player> p, int n):
                                       PlayerDecorator(p), adjustment{n} {}

int PlayerDecoratorAtk::getAtk() const {
  return thePlayer->getAtk() + adjustment;
}

// PlayerDecoratorDef Implementation
PlayerDecoratorDef::PlayerDecoratorDef(shared_ptr<Player> p, int n):
                                       PlayerDecorator(p), adjustment{n} {}

int PlayerDecoratorDef::getDef() const {
  return thePlayer->getDef() + adjustment;
}
