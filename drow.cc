#include <iostream>
#include "drow.h"
#include "player_decorators.h"

using namespace std;

Drow::Drow(): Player("Drow", 150, 25, 15) {}

                    
void Drow::useEntity(Potion_RH &p) {modifyHp(p.getPotency() * 3 / 2);}
void Drow::useEntity(Potion_PH &p) {modifyHp(-(p.getPotency()) * 3 / 2);}
void Drow::useEntity(Potion_BA &p) {modifyAtkOffset(p.getPotency() * 3 / 2);}
void Drow::useEntity(Potion_BD &p) {modifyDefOffset(p.getPotency() * 3 / 2);}
void Drow::useEntity(Potion_WA &p) {modifyAtkOffset(-(p.getPotency() * 3 / 2));}
void Drow::useEntity(Potion_WD &p) {modifyDefOffset(-(p.getPotency() * 3 / 2));}
