#include "game.h"

#include "cell.h"
#include "player.h"

#include "human.h"
#include "dwarf.h"
#include "elf.h"
#include "merchant.h"

#include "halfling.h"
#include "orc.h"

#include "treasure.h"
#include "treasure_normal.h"
#include "treasure_small.h"
#include "treasure_merchant.h"
#include "treasure_dragon.h"
#include "invalid_behave.h"
#include "posn.h"
#include "potion.h"

#include "shade.h"
#include "drow.h"
#include "vampire.h"
#include "troll.h"
#include "goblin.h"

#include <sstream>
#include <iostream>
#include <iterator>
#include <algorithm>
#include <stdlib.h>
using namespace std;

Game::Game(): theGrid(new Grid()), player{nullptr}, /*enemies{nullptr}, potions{nullptr},*/ frozen{false} {
  theGrid->init("maps/basicFloor.txt", 1);
}

/*
Game::PotionFactory & Game::PotionFactory::getInstance() {
  static PotionFactory theFactory;
  return theFactory;
}*/

Game::GenericFactory & Game::GenericFactory::getInstance() {
  static GenericFactory theFactory;
  return theFactory;
}

const vector<int> Game::POTION_SPAWN_RATES =
  {Potion_RH::SPAWN_RATE, Potion_PH::SPAWN_RATE,
   Potion_BA::SPAWN_RATE, Potion_WA::SPAWN_RATE,
   Potion_BD::SPAWN_RATE, Potion_WD::SPAWN_RATE}; 
const vector<function<shared_ptr<Potion>()>> Game::POTION_MAKERS =
  {[&]{return make_shared<Potion_RH>();},[&]{return make_shared<Potion_PH>();},
   [&]{return make_shared<Potion_BA>();},[&]{return make_shared<Potion_WA>();},
   [&]{return make_shared<Potion_BD>();},[&]{return make_shared<Potion_WD>();}};

const vector<int> Game::TREASURE_SPAWN_RATES =
  {Treasure_Small::SPAWN_RATE, Treasure_Normal::SPAWN_RATE,
   Treasure_Merchant::SPAWN_RATE, Treasure_Dragon::SPAWN_RATE};
const vector<function<shared_ptr<Treasure>()>> Game::TREASURE_MAKERS =
  {[&]{return make_shared<Treasure_Small>();},
   [&]{return make_shared<Treasure_Normal>();},
   [&]{return make_shared<Treasure_Merchant>();},
   [&]{return make_shared<Treasure_Dragon>();}};

/*
const vector<int> Game::PotionFactory::S_RATES =
  {Potion_RH::SPAWN_RATE, Potion_PH::SPAWN_RATE,
   Potion_BA::SPAWN_RATE, Potion_WA::SPAWN_RATE,
   Potion_BD::SPAWN_RATE, Potion_WD::SPAWN_RATE};

//vector of lambda functions that return shared_ptrs to subtype
const vector<function<shared_ptr<Potion>()>> Game::PotionFactory::MAKERS = 
  {[&]{return make_shared<Potion_RH>();},[&]{return make_shared<Potion_PH>();},
   [&]{return make_shared<Potion_BA>();},[&]{return make_shared<Potion_WA>();},
   [&]{return make_shared<Potion_BD>();},[&]{return make_shared<Potion_WD>();}};

shared_ptr<Potion> Game::PotionFactory::make() {
  // get the sum of the spawn rates
  int s_rate_sum = 0;
  for (auto i: S_RATES) {
    s_rate_sum += i;
  }

  // generate a random number between 1 and s_rate_sum inclusive
  int pType = rand() % s_rate_sum + 1;

  // for each element of S_RATES, add its value to accumulator
  // when the accumulator is >= the random number, use MAKERS
  // to spawn the appropriate Potion type.
  int accumulated_s_rate = 0;
  for (int i = 0, end = S_RATES.size();i < end; i++) {
    accumulated_s_rate += S_RATES[i];
    if (accumulated_s_rate >= pType) {
        return MAKERS[i]();
    }
  }

  // if function gets here, nothing was spawned. should not happen
  return nullptr;
}
*/

  /* original
  switch (pType) {
    case 0 : return make_shared<Potion_RH>();
    case 1 : return make_shared<Potion_PH>();
    case 2 : return make_shared<Potion_BA>();
    case 3 : return make_shared<Potion_WA>();
    case 4 : return make_shared<Potion_BD>();
    case 5 : return make_shared<Potion_WD>();
    default: return nullptr; // should not happen
  }
}*/

/*
Game::TreasureFactory & Game::TreasureFactory::getInstance() {
  static TreasureFactory theFactory;
  return theFactory;
}
const vector<int> Game::TreasureFactory::S_RATES =
  {Potion_RH::SPAWN_RATE, Potion_PH::SPAWN_RATE,
   Potion_BA::SPAWN_RATE, Potion_WA::SPAWN_RATE,
   Potion_BD::SPAWN_RATE, Potion_WD::SPAWN_RATE};

//vector of lambda functions that return shared_ptrs to subtype
const vector<function<shared_ptr<Potion>()>> Game::PotionFactory::MAKERS = 
  {[&]{return make_shared<Potion_RH>();},[&]{return make_shared<Potion_PH>();},
   [&]{return make_shared<Potion_BA>();},[&]{return make_shared<Potion_WA>();},
   [&]{return make_shared<Potion_BD>();},[&]{return make_shared<Potion_WD>();}};

//shared_ptr<Treasure> Game::TreasureFactory::make() {
//  int tType = rand() %
*/

void Game::generateEnemies(vector<vector<Cell *>> &vcham) {
  if(!enemies.empty())enemies.clear();
  for (int i = 0; i < 20; ++i) {
    int numChambers = vcham.size();
    int selectedChamberIdx = rand() % (numChambers);
    vector<Cell *> &vc = vcham[selectedChamberIdx];
    int numCells = vc.size();
    int selectedCellIdx = rand() % (numCells);
    int enemyType = rand() % 18 + 1;
    while (!validSpot(*(vc[selectedCellIdx]))){
      selectedCellIdx = rand() % (numCells);
    }
    Cell &selected = *(vc[selectedCellIdx]);
    if(enemyType >= 1 && enemyType <= 4) {
      shared_ptr<Human> H(new Human());
      theGrid->placeEntity(H, {selected.getRow(), selected.getCol()});
      enemies.emplace_back(H);
    } else if(enemyType >= 5 && enemyType <= 7) {
      shared_ptr<Dwarf> D(new Dwarf());
      theGrid->placeEntity(D, {selected.getRow(), selected.getCol()});
      enemies.emplace_back(D);
    } else if(enemyType >= 8 && enemyType <= 12) {
      shared_ptr<Halfling> Ha(new Halfling());
      theGrid->placeEntity(Ha, {selected.getRow(), selected.getCol()});
      enemies.emplace_back(Ha);
    } else if(enemyType >= 13 && enemyType <= 14) {
      shared_ptr<Elf> E(new Elf());
      theGrid->placeEntity(E, {selected.getRow(), selected.getCol()});
      enemies.emplace_back(E);
    } else if(enemyType >= 15 && enemyType <= 16) {
      shared_ptr<Orc> O(new Orc());
      theGrid->placeEntity(O, {selected.getRow(), selected.getCol()});
      enemies.emplace_back(O);
    } else {
      shared_ptr<Merchant> M(new Merchant());
      if(checkIfHostile()) M->turnHostile();
      theGrid->placeEntity(M, {selected.getRow(), selected.getCol()});
      enemies.emplace_back(M);
    }
    vc.erase(vc.begin() + selectedCellIdx); // remove cell from candidate spawn locations
  }
}
  /*int size = theGrid.size();
  int randomrange = 0;
  int randomnumber = 0;
  Vector<Cell>candidates;
  for (int i = 0; i < size; ++i) {
    for (int j = 0; j < size; ++j) {
      if (theGrid[i][j].cell.tile == Terrain::Chamfloor) {
        ++randomrange;
        candidates.emplace_back(theGrid[i][j]);
      }
    }
  }
  for (int k = 0; k < 20; ++k) {
    randomnumber = rand() % randomrange;
    Enemy &e = Enemy{&candidates[randomnumber]};
    placeEntity(e, candidates[randomnumber]);
    enemies.emplace_back(e);
  }
}*/  
    
void Game::generatePotions(vector<vector<Cell *>> &vcham) {
  Game::GenericFactory pf = Game::GenericFactory::getInstance(); // get factory
  for (int i = 0; i < NUM_POTION_SPAWN; i++) {
    vector<Cell*> &vc = vcham[rand() % vcham.size()]; // select rand chamber

    int selectedCellIdx = rand() % vc.size(); // get random cell index
    Cell &selected = *(vc[selectedCellIdx]);  // select random cell
    vc.erase(vc.begin() + selectedCellIdx);   // remove cell from candidates

    shared_ptr<Potion> to_place = 
      pf.make<Potion>(POTION_SPAWN_RATES, POTION_MAKERS); // make a random potion
    
    // place the random potion in the selected cell
    theGrid->placeEntity(to_place, {selected.getRow(), selected.getCol()});
  }
}  
 
 
void Game::generateTreasures(vector<vector<Cell *>> &vvc) {
  Game::GenericFactory tf = Game::GenericFactory::getInstance();
  for (int i = 0; i < NUM_TREASURE_SPAWN; i++) {
    int numChambers = vvc.size();
    int selectedChamberIdx = rand() % numChambers;

    vector<Cell *> &vc = vvc[selectedChamberIdx];
    int numCells = vc.size();
    int selectedCellIdx = rand() % numCells;

    Cell &selected = *(vc[selectedCellIdx]);
    vc.erase(vc.begin() + selectedCellIdx); // remove cell from candidate spawn locations

    shared_ptr<Treasure> toPlace =
      tf.make<Treasure>(TREASURE_SPAWN_RATES, TREASURE_MAKERS); 
    theGrid->placeEntity(toPlace, {selected.getRow(), selected.getCol()});
  }
}


void Game::generatePlayer(const string &race, vector<vector<Cell *>> &vvc) {
  (void)race;
  int numChambers = vvc.size();
  int selectedChamberIdx = rand() % numChambers;
  vector<Cell *> &vc = vvc[selectedChamberIdx];
  int numCells = vc.size();
  int selectedCellIdx = rand() % numCells;
  Cell &selected = *(vc[selectedCellIdx]);
  vc.erase(vc.begin() + selectedCellIdx); // remove cell from candidate spawn locations
  
  //shared_ptr<Player> test(new Player());
  //player = test;
  if (race == "s") {
    player = make_shared<Shade>();
  }
  else if (race == "d") {
    player = make_shared<Drow>();
  }
  else if (race == "v") {
    player = make_shared<Vampire>();
  }
  else if (race == "t") {
    player = make_shared<Troll>();
  }
  else if (race == "g") {
    player = make_shared<Goblin>();
  }
  else {player = make_shared<Player>("Player");}
  
  theGrid->placeEntity(player, {selected.getRow(), selected.getCol()});
 /* int stairChamberIdx = rand() % (numChambers - 1);
  if (stairChamberIdx >= selectedChamberIdx) stairChamberIdx++;
  vector<Cell *> &stairChamber = vvc[stairChamberIdx];
  int stairIdx = rand() % stairChamber.size();
  Cell &stairway = *(stairChamber[stairIdx]);
  stairChamber.erase(stairChamber.begin() + stairIdx);
  theGrid->placeStairs({stairway.getRow(), stairway.getCol()});
*/
}         

void Game::generateStair(vector<vector<Cell *>> &vvc) {
  int stairChamberIdx = rand() % (vvc.size() - 1);
  int selectedChamberIdx = (theGrid->getCell(player->getPosn())).getChamber() - 1;
  if (stairChamberIdx >= selectedChamberIdx) stairChamberIdx++;
  vector<Cell *> &stairChamber = vvc[stairChamberIdx];
  int stairIdx = rand() % stairChamber.size();
  Cell &stairway = *(stairChamber[stairIdx]);
  stairChamber.erase(stairChamber.begin() + stairIdx);
  theGrid->placeStairs({stairway.getRow(), stairway.getCol()});
}

bool Game::startRound(const string &race) {
  // Copy the chamber layout
  vector<vector<Cell *>> candidateCells = theGrid->getChambers();
  
  generatePlayer(race, candidateCells);
  generateStair(candidateCells);
  generatePotions(candidateCells);
  generateTreasures(candidateCells);
  generateEnemies(candidateCells);
  return true;
}
string Game::moveEnemies(bool frozen) {
  enemy_sort(enemies);
  string full_action_text = "";
  for(auto e : enemies) {
    Posn e_Posn = e->getPosn();
    //cout << "e_posn: " << e_Posn.r << ", " << e_Posn.c << endl;
    if (dynamic_pointer_cast<Merchant>(e)&& isInAttackRange(e_Posn)) {
      auto m = static_pointer_cast<Merchant>(e);
      if (m->checkHostile()){
        atkStatus as = m->attack(player);
        full_action_text += m->actionText(player, as);
      }else if (!frozen && isAnyValidNeighbour(e_Posn)) {
        theGrid->moveEntity(e_Posn,validRandomNeighbour(e_Posn));
      }
    }
    else if (isInAttackRange(e_Posn)) {
      atkStatus as = e->attack(player);
      //cout << "after_attacking player: " << e->actionText(player) <<endl;
      full_action_text += e->actionText(player, as);
    }
    else if (!frozen && isAnyValidNeighbour(e_Posn)) {
      theGrid->moveEntity(e_Posn,validRandomNeighbour(e_Posn));
    }
  }
  return full_action_text;
  /*int size = enemies.size();
  int randomrange = 0;
  int randomnumber = 0;
  vector<Cell>candidates;
  for (int i = 0; i < size; ++i) {
    row = enemies.cell.getRow();
    col = enemies.cell.getCol();
    for (int r = ((row == 0) ? 0 : -1); r <= ((row == size - 1) ? 0 : 1); ++r) {
        //checks for all neighbors
      for (int c = ((col == 0) ? 0 : -1); c <= ((col == size - 1) ? 0 : 1); ++c) {
        if (!(r == 0 && c == 0)) {
          candidates.emplace_back(theGrid[row + r][col + c]);
          ++randomrange;
        }
      }
    }
    randomnumber = rand() % randomrange;
    theGrid.moveEntity(enemies.at(i).cell, candidates.at(randomnumber));
    randomnumber = 0;
    randomrange = 0;
  }*/
}

bool Game::isAnyValidNeighbour(Posn p) {
  for (int i = p.r - 1; i <= p.r + 1; ++i) {
    for (int j = p.c - 1; j <= p.c + 1; ++j) {
      //cout << "i: " << i << " j: " << j << endl;
      if (i != p.r && i != p.c && validSpot(theGrid->getCell({i,j}))) return true;
    }
  }
  return false;
}

Posn Game::validRandomNeighbour(Posn p) {
  vector<Cell *>candidates;
  int candidatesize = 0;
  for (int i = p.r - 1; i <= p.r + 1; ++i) {
    for (int j = p.c - 1; j <= p.c + 1; ++j) {
      if (i != p.r && i != p.c && validSpot(theGrid->getCell({i,j}))) {
        candidatesize++;
        candidates.emplace_back(&(theGrid->getCell({i,j})));
      }
    }
  }
  int randNum = rand() % candidatesize;
  //cout << "candidate_pos: " << candidates[randNum]->getPosn().r << ", " << candidates[randNum]->getPosn().c << endl;
  return candidates[randNum]->getPosn();
}

bool Game::validSpot(Cell &cell) {
  return cell.getTerrain() == Terrain::ChamFloor && cell.getOccupant() == nullptr;
}

bool Game::isInAttackRange(Posn p) {
  return (abs(p.r - player->getPosn().r) <= 1 && abs(p.c - player->getPosn().c) <= 1);
}

bool Game::sort_function(shared_ptr<Enemy>e1, shared_ptr<Enemy>e2) {
  if ((e1->getPosn()).r < (e2->getPosn()).r) {
    return true;
  }
  else if ((e1->getPosn()).r == (e2->getPosn()).r &&
           (e1->getPosn()).c < (e2->getPosn()).c) {
    return true;
  }
  else {
    return false;
  }
}

void Game::enemy_sort(vector<shared_ptr<Enemy>>&enemy_vector) {
  sort(enemy_vector.begin(), enemy_vector.end(), &sort_function);
}

void Game::changeFloor(Posn playerPosn) {
  theGrid->init("maps/basicFloor.txt",theGrid->getLevel());
  vector<vector<Cell *>> candidateCells = theGrid->getChambers();
  theGrid->placeEntity(player,playerPosn);
  generateStair(candidateCells);
  generatePotions(candidateCells);
  generateTreasures(candidateCells);
  generateEnemies(candidateCells);
}
/*  
void Game::update_display() {
  theGrid.td.update();
}*/

Posn dir_to_posn(Posn currPosn, string direction) {
  int row = currPosn.r;
  int col = currPosn.c;
  if (direction == "ea") return {row, col + 1};
  else if (direction == "no") return {row - 1, col};
  else if (direction == "we") return {row, col - 1};
  else if (direction == "so") return {row + 1, col};
  else if (direction == "nw") return {row - 1, col - 1};
  else if (direction == "ne") return {row - 1, col + 1};
  else if (direction == "sw") return {row + 1, col - 1};
  else if (direction == "se") return {row + 1, col + 1};
  else return {-1, -1};
}

string Game::movePlayer(const string &direction) {
  string full_action_text = "";
  Posn player_Posn = player->getPosn();
  Posn heading_dir = dir_to_posn(player_Posn, direction); 
  if (theGrid->canStep(heading_dir, *player)) {
    theGrid->moveEntity(player_Posn, heading_dir);
    full_action_text += player->getName() + " moves " + direction + ".";
  }else {
    throw Invalid_behave("");
  }
  return full_action_text;
  /* original
  Posn heading_dir = dir_to_posn(theGrid->getCell(player_Posn), direction);
  char heading_tile = theGrid->getCell(heading_dir).getSymbol();
  if (heading_tile == '#' || heading_tile == '.' || heading_tile == '+') { 
    theGrid->moveEntity(player_Posn, heading_dir);
    full_action_text += player->getName() + " moves " + direction;
  }
  else if (heading_tile == '\\') {
    theGrid->levelUp();
    changeFloor(dir_to_posn(player_Posn,direction));
    string stringAsLevel = to_string(theGrid->getLevel());
    full_action_text += player->getName() + " moves to next floor current floor(" + stringAsLevel +").";
  } else {
    throw Invalid_behave("");
  }
  return full_action_text; */
}

string Game::potion_near() {
  for (int i = -1; i <= 1; ++i) {
    for (int j = -1; j <= 1; ++j) {
      //cout << "r: " << player->getPosn().r + i << " c: " << player->getPosn().c + i << endl;
      shared_ptr<Entity> cell_occupant = (theGrid->getCell({player->getPosn().r + i, player->getPosn().c + j}).getOccupant()); 
      //cout << cell_occupant << endl;
      if (cell_occupant != nullptr && cell_occupant->getSymbol() == 'P') {
        return " and sees a" + cell_occupant->getName() + ".";
      }
    }
  }
  return "";
}

int Game::enemy_index(shared_ptr<Enemy> e) {
  int enemy_num = enemies.size();
  for (int i = 0; i < enemy_num; ++i) {
    if (e->getPosn().r == enemies[i]->getPosn().r &&
        e->getPosn().c == enemies[i]->getPosn().c) {
      return i;
    }
  }
  return -1;
}

string Game::PlayerAttack(string direction) {
  Posn player_Posn = player->getPosn();
  Cell &target_cell = theGrid->getCell(dir_to_posn(player_Posn,direction));
  if(target_cell.getOccupant() == nullptr) {
    return "There is no enemy at that direction.";
  } else {
    char entity_sym = target_cell.getOccupant()->getSymbol();
    auto e = static_pointer_cast<Enemy>(target_cell.getOccupant());
    if (entity_sym == 'E' || entity_sym == 'L' ||
        entity_sym == 'H' || entity_sym == 'O' ||
        entity_sym == 'W' || entity_sym == 'D' ) {
      atkStatus as = player->attack(e);
      if (as == atkStatus::Kill) {
        theGrid->removeEntity(e->getPosn());
        enemies.erase(enemies.begin() + enemy_index(e));
      }
      return player->actionText(e, as);
    } else if (entity_sym == 'M') {
      changeHostile();
      auto mt  = static_pointer_cast<Merchant>(e);
      if(!mt->checkHostile()) {
        for (auto en : enemies) {
          if (dynamic_pointer_cast<Merchant>(en)) {
            auto m = static_pointer_cast<Merchant>(en);
            m->turnHostile();
          }
        }
      }
      atkStatus as = player->attack(e);
      return player->actionText(e, as);
    }else return player->actionText(e, atkStatus::InvalidTarget);
  }
}
/*  
void Game::Player_usePotion(string direction) {
  int size = potions.size();
  int target_row = target.getRow();
  int target_col = target.getCol();
  for (int i = 0; i < size; ++size) { 
    if (target_row == potions.at(i).getRow() &&
        target_col == potions.at(i).getCol()) {
      player->usePotion(dir_to_cell(player.cell, direction));
      shared_ptr<Potion>removed_potion = potions.back();
      potions.pop_back();
      removeEntity(removed_potion.cell);
      return;
    }
  }
}
*/

bool Game::checkIfHostile() const {
  return isHostile;
}

void Game::changeHostile() {
  isHostile = true;
}

void Game::freeze() {
  frozen = !frozen;
}

bool valid_dir(string dir) {
  if (dir == "ea" || dir == "no" || dir == "so" || dir == "we" ||
      dir == "sw" || dir == "se" || dir == "nw" || dir == "ne") {
    return true;
  }
  else {
    throw Invalid_behave("");
    return false;
  }
}

void useTogether(shared_ptr<Player> &user, const shared_ptr<Entity> &used) {
  user = used->beUsedBy(user);
}

/*string Game::processTurn(const string &command) {
  string full_printing_msg = "";
  istringstream iss(command);
  string s;
  iss >> s;
  player->beginTurn();
  if (s == "a") {
    iss >> s;
}*/

string Game::processTurn(const string &command) {
  string full_printing_msg = "";
  istringstream iss(command);
  string s;
  iss >> s;
  player->beginTurn();
  if (s == "a") {
    iss >> s;
    if (valid_dir(s)) {
      full_printing_msg += PlayerAttack(s);
    }
  }
  
  else if (s == "use") {
    iss >> s;
    //cout << "use detected" << endl;
    if (valid_dir(s)) {
      Posn target = dir_to_posn(player->getPosn(), s);
      //cout << "target posn: " << target.r << " , " << target.c << endl;
      if (theGrid->hasUsable(target)) { // if the occupant of target can be used
        //cout << "target can be used " << endl;
        useTogether(player, theGrid->getCell(target).getOccupant()); // make player use the occupant of target
        full_printing_msg += "PC uses " + theGrid->getCell(target).getOccupant()->getName() + ".";
        theGrid->removeEntity(target);  //remove target from the board
        movePlayer(s); //fdsmakmfdskmfsdlfdkslk
        //todo generate action text
      }
    }
  }/*
  else if (s == "r") {
    //changeFloor();
  }*/
  else if (s == "f") {
    freeze();
  } 
  else if (s == "q") {
    cout<<"You quit the game."<<endl;
    //throw 0;
  }
  else if (valid_dir(s)) {
    full_printing_msg += movePlayer(s);
    full_printing_msg += potion_near();
  } 
  full_printing_msg += moveEnemies(frozen);
  return full_printing_msg;
}

void Game::print(string printing_msg) {
  cout << *theGrid;
  cout << "Race: " << player->getName() << " Gold: " << to_string(player->finalScore()) << endl;
  cout << "HP: " << to_string(player->getHp()) << endl;
  cout << "Atk: " << to_string(player->getAtk()) << endl;
  cout << "Def: " << to_string(player->getDef()) << endl;
  cout << "Action: " << printing_msg << endl; 
}

bool Game::gameOver() {
  if(player->getHp() <= 0) {
    cout<< "You have been slained! Game Over."<<endl;
    return true;
  } else if (theGrid->getLevel() == 6) {
    cout<< "Congratulations, you reach the top of the floor, you won the game!"<<endl;
    return true;
  } else return false;
}
