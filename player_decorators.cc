#include "player_decorators.h"

using namespace std;

PlayerDecorator::PlayerDecorator(shared_ptr<Player> p): Player(*p),
                                                        thePlayer{p} {}

shared_ptr<Player> PlayerDecorator::withoutBuffs() {return thePlayer->withoutBuffs();}

// overriding public virtual functions
// most will just call thePlayer->overrridedFn(sameParams)
// this will probably need to be changed
char PlayerDecorator::getSymbol() const {return thePlayer->getSymbol();}
bool PlayerDecorator::wasUsed(std::shared_ptr<Player> *user) {return thePlayer->wasUsed(user);}
void PlayerDecorator::setPos(Posn p) {thePlayer->setPos(p);}
Posn PlayerDecorator::getPosn() const {return thePlayer->getPosn();}
bool PlayerDecorator::isUsable() const {return thePlayer->isUsable();}
Player * PlayerDecorator::beUsedBy(Player * user) {return thePlayer->beUsedBy(user);}
void PlayerDecorator::beginTurn() {thePlayer->beginTurn();}
void PlayerDecorator::endTurn() {thePlayer->endTurn();}
int PlayerDecorator::getAtk() const {return thePlayer->getAtk();}
int PlayerDecorator::getDef() const {return thePlayer->getDef();}
int PlayerDecorator::getHp() const {return thePlayer->getHp();}
string PlayerDecorator::getName() const {return thePlayer->getName();}
int PlayerDecorator::damage(int atk, int def) {return thePlayer->damage(atk, def);}
void PlayerDecorator::modifyHp(int delta) {return thePlayer->modifyHp(delta);}
// attack and wasAttacked wll probably need to be fixed
atkStatus PlayerDecorator::attack(Cell &target) {return thePlayer->attack(target);}
atkStatus PlayerDecorator::wasAttacked(Creature *aggressor) {return thePlayer->wasAttacked(aggressor);}
void PlayerDecorator::move(Posn p) {return thePlayer->move(p);}
void PlayerDecorator::addGold(int reward) {return thePlayer->addGold(reward);}
int PlayerDecorator::finalScore() {return thePlayer->finalScore();}
string PlayerDecorator::actionText(Creature * aggressor) {return thePlayer->actionText(aggressor);}
int PlayerDecorator::getGold() {return thePlayer->getGold();}
//these will probably need to be fixed
shared_ptr<Player> PlayerDecorator::useEntity(shared_ptr<Potion_RH> p) {return thePlayer->useEntity(p);}
shared_ptr<Player> PlayerDecorator::useEntity(shared_ptr<Potion_PH> p) {return thePlayer->useEntity(p);}
shared_ptr<Player> PlayerDecorator::useEntity(shared_ptr<Potion_BA> p) {return thePlayer->useEntity(p);}
shared_ptr<Player> PlayerDecorator::useEntity(shared_ptr<Potion_WA> p) {return thePlayer->useEntity(p);}
shared_ptr<Player> PlayerDecorator::useEntity(shared_ptr<Potion_BD> p) {return thePlayer->useEntity(p);}
shared_ptr<Player> PlayerDecorator::useEntity(shared_ptr<Potion_WD> p) {return thePlayer->useEntity(p);}

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
