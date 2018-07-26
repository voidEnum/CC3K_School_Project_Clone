#include "game.h"

#include "cell.h"
#include "player.h"

#include "human.h"
#include "dwarf.h"
#include "elf.h"
#include "merchant.h"
#include "dragon.h"
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
#include <vector>
using namespace std;

Game::Game(): theGrid{make_unique<Grid>()}, player{nullptr},frozen{false} {
  theGrid->init("maps/basicFloor.txt", 1);
}

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
   [&]{shared_ptr<Treasure_Dragon> temp = make_shared<Treasure_Dragon>();
       temp->makeDragon(); // Guard Dragon must be initialized
       return temp;}};

void Game::generateEnemies(vector<vector<Cell *>> &vcham) {
  for (int i = 0; i < 20; ++i) {
    int numChambers = vcham.size();
    int selectedChamberIdx = rand() % (numChambers);
    vector<Cell *> &vc = vcham[selectedChamberIdx];
    int numCells = vc.size();
    int selectedCellIdx = rand() % (numCells);
    int enemyType = rand() % 18 + 1;
    Cell &selected = *(vc[selectedCellIdx]);
    if(enemyType >= 1 && enemyType <= 4) {
      shared_ptr<Human> H(make_shared<Human>());
      theGrid->placeEntity(H, {selected.getRow(), selected.getCol()});
      enemies.emplace_back(H);
    } else if(enemyType >= 5 && enemyType <= 7) {
      shared_ptr<Dwarf> D(make_shared<Dwarf>());
      theGrid->placeEntity(D, {selected.getRow(), selected.getCol()});
      enemies.emplace_back(D);
    } else if(enemyType >= 8 && enemyType <= 12) {
      shared_ptr<Halfling> Ha(make_shared<Halfling>());
      theGrid->placeEntity(Ha, {selected.getRow(), selected.getCol()});
      enemies.emplace_back(Ha);
    } else if(enemyType >= 13 && enemyType <= 14) {
      shared_ptr<Elf> E(make_shared<Elf>());
      theGrid->placeEntity(E, {selected.getRow(), selected.getCol()});
      enemies.emplace_back(E);
    } else if(enemyType >= 15 && enemyType <= 16) {
      shared_ptr<Orc> O(make_shared<Orc>());
      theGrid->placeEntity(O, {selected.getRow(), selected.getCol()});
      enemies.emplace_back(O);
    } else {
      shared_ptr<Merchant> M(make_shared<Merchant>());
      theGrid->placeEntity(M, {selected.getRow(), selected.getCol()});
      enemies.emplace_back(M);
    }
    vc.erase(vc.begin() + selectedCellIdx); // remove cell from candidate spawn locations
  }
}
    
void Game::generatePotions(vector<vector<Cell *>> &vcham) {
  Game::GenericFactory pf = Game::GenericFactory::getInstance(); // get factory
  for (int i = 0; i < NUM_POTION_SPAWN; i++) {
    vector<Cell*> &vc = vcham[rand() % vcham.size()]; // select rand chamber

    int selectedCellIdx = rand() % vc.size(); // get random cell index
    Cell &selected = *(vc[selectedCellIdx]);  // select random cell
    vc.erase(vc.begin() + selectedCellIdx);   // remove cell from candidates
      
    
    // place the random potion in the selected cell
    theGrid->placeEntity(pf.make<Potion>(POTION_SPAWN_RATES, POTION_MAKERS), // make a random potion 
                         {selected.getRow(), selected.getCol()});
  }
}  
 
 
void Game::generateTreasures(vector<vector<Cell *>> &vvc) {
  Game::GenericFactory tf = Game::GenericFactory::getInstance();
  for (int i = 0; i < NUM_TREASURE_SPAWN; i++) {
    int numChambers = vvc.size();
    int selectedChamberIdx = rand() % numChambers;
    
    shared_ptr<Treasure> toPlace = tf.make<Treasure>(
                                   TREASURE_SPAWN_RATES, TREASURE_MAKERS);
    vector<Cell *> &vc = vvc[selectedChamberIdx];
    int numCells = vc.size();
    int selectedCellIdx = rand() % numCells;
    

    if (Treasure_Dragon *td = dynamic_cast<Treasure_Dragon *>(toPlace.get())) {
      vector<int> tdNeighboursCellsIdx;
      while (tdNeighboursCellsIdx.empty()) {
        Posn s_posn = vc[selectedCellIdx]->getPosn();
        for (int i = 0; i < numCells; i++) { 
          Posn c_posn = vc[i]->getPosn();
          int rdiff = abs(c_posn.r - s_posn.r);
          int cdiff = abs(c_posn.c - s_posn.c);
          if (rdiff <= 1 && cdiff <= 1 && !(s_posn == c_posn) && !vc[i]->getOccupant()) {
            tdNeighboursCellsIdx.push_back(i);
          }
        }
        if (tdNeighboursCellsIdx.empty()) {
          selectedCellIdx = rand() % numCells;
        }
      }
      int selectedNeighbourIdx = tdNeighboursCellsIdx[rand() 
                              % tdNeighboursCellsIdx.size()];
      theGrid->placeEntity(td->getDragonAsEnemy(), 
                           vc[selectedNeighbourIdx]->getPosn());
      vc.erase(vc.begin() + selectedNeighbourIdx);
      enemies.push_back(td->getDragonAsEnemy());
      if (selectedNeighbourIdx < selectedCellIdx) {
        selectedCellIdx--; //if an ealier index was deleted, decrement the index by one to compensate
      }
    }

    Cell &selected = *(vc[selectedCellIdx]);
    theGrid->placeEntity(toPlace, selected.getPosn());
    vc.erase(vc.begin() + selectedCellIdx); // remove cell from candidate spawn locations
    }
}


void Game::generatePlayer(vector<vector<Cell *>> &vvc, const string &race = "") {
  if (!player) {
    int numChambers = vvc.size();
    int selectedChamberIdx = rand() % numChambers;
    vector<Cell *> &vc = vvc[selectedChamberIdx];
    int numCells = vc.size();
    int selectedCellIdx = rand() % numCells;
    Cell &selected = *(vc[selectedCellIdx]);
    vc.erase(vc.begin() + selectedCellIdx); // remove cell from candidate spawn locations
  
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
    else {player = make_shared<Player>("Player");
    }
    theGrid->placeEntity(player, selected.getPosn());
  }else { //find the players index in vvc
    bool done = false;
    for (auto vc : vvc) {
      for (auto it = vc.begin(); it != vc.end(); it++) {
        if ((*it)->getPosn() == player->getPosn()) {
          vc.erase(it); // remove the cell the player will be place in from candidate cells
          done = true;
          break;
        }
      }
      if (done) break;
    }
    theGrid->placeEntity(player, player->getPosn());
  }
}     
  
void Game::generateStair(vector<vector<Cell *>> &vvc) {
  int stairChamberIdx = rand() % (vvc.size() - 1);
  int selectedChamberIdx = (theGrid->getCell(player->getPosn())).getChamber() - 1;
  if (stairChamberIdx >= selectedChamberIdx) stairChamberIdx++;
  vector<Cell *> &stairChamber = vvc[stairChamberIdx];
  int stairIdx = rand() % stairChamber.size();
  Cell &stairway = *(stairChamber[stairIdx]);
  stairChamber.erase(stairChamber.begin() + stairIdx);
  theGrid->placeStairs(stairway.getPosn());
}

bool Game::startRound(const string &race) {
  quit = false;
  if (race != "s" && race != "d" && race != "v" &&
      race != "t" && race != "g") {
    throw Invalid_behave("Please enter one of (s), (d), (v), (t), (g)");
  }
  // Copy the chamber layout
  vector<vector<Cell *>> candidateCells = theGrid->getChambers();
  generatePlayer(candidateCells, race);
  generateStair(candidateCells);
  generatePotions(candidateCells);
  generateTreasures(candidateCells);
  generateEnemies(candidateCells);
  
  return true;
}
string Game::moveEnemies() {
  enemy_sort(enemies);
  string full_action_text = "";
  for(auto e : enemies) {
    Posn e_Posn = e->getPosn();
    if (dynamic_pointer_cast<Merchant>(e) && isInAttackRange(e_Posn))  {
      auto m = static_pointer_cast<Merchant>(e);
      if (m->checkHostile()){
        atkStatus as = m->attack(player);
        full_action_text += m->actionText(player, as);
      }else if (isAnyValidNeighbour(e_Posn)) {
        theGrid->moveEntity(e_Posn,validRandomNeighbour(e_Posn));
      }
    } else if (Dragon *d = dynamic_cast<Dragon *>(e.get())) {
        if (isInAttackRange(e_Posn) || isInAttackRange(d->getHoard()->getPosn())) {
          atkStatus as = d->attack(player);
          full_action_text += d->actionText(player, as);
        }
    } else if (isInAttackRange(e_Posn)) {
      atkStatus as = e->attack(player);
      full_action_text += e->actionText(player, as);
    } else if(isAnyValidNeighbour(e_Posn)) {
      theGrid->moveEntity(e_Posn,validRandomNeighbour(e_Posn));
    }
  }
  return full_action_text;
}

bool Game::isAnyValidNeighbour(Posn p) {
  for (int i = p.r - 1; i <= p.r + 1; ++i) {
    for (int j = p.c - 1; j <= p.c + 1; ++j) {
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

void Game::changeFloor() {
  theGrid->init("maps/basicFloor.txt",theGrid->getLevel() + 1);
  vector<vector<Cell *>> candidateCells = theGrid->getChambers();
  
  enemies.clear();
  generatePlayer(candidateCells);
  generateStair(candidateCells);
  generatePotions(candidateCells);
  generateTreasures(candidateCells);
  generateEnemies(candidateCells);
  player->removeBuffs();
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

string dirToDirection(const string &direction) {
    if (direction == "ea") return "east";
  else if (direction == "no") return "north";
  else if (direction == "we") return "west";
  else if (direction == "so") return "south";
  else if (direction == "nw") return "north_west";
  else if (direction == "ne") return "north-east";
  else if (direction == "sw") return "south-west";
  else return "south-east";
}

string Game::movePlayer(const string &direction) {
  string full_action_text = "";
  string directionAsString = dirToDirection(direction);
  Posn player_Posn = player->getPosn();
  Posn heading_dir = dir_to_posn(player_Posn, direction); 
  if (theGrid->canStep(heading_dir, *player)) {
    if (theGrid->getCell(heading_dir).getSymbol() == '\\') {
      theGrid->moveEntity(player_Posn, heading_dir);
      changeFloor();
      string levelAsString = to_string(theGrid->getLevel());
      full_action_text += player->getName() + " moves to next floor current floor(" + levelAsString + ").";
    } else if (theGrid->getCell(heading_dir).getSymbol() == 'G') {
      auto t = static_pointer_cast<Treasure>(theGrid->getCell(heading_dir).getOccupant());
      string goldAsString = to_string(t->getValue());
      full_action_text += "PC moves " + directionAsString + ". PC picked up " + t->getName() + ", PC earned " + goldAsString +" gold.";
      theGrid->moveEntity(player_Posn, heading_dir);
    } else {
      theGrid->moveEntity(player_Posn, heading_dir);
      full_action_text += "PC moves " + directionAsString + ".";
    }
  }else {
    throw Invalid_behave("Please, enter a valid move direction!");
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
        return " and sees " + cell_occupant->getName() + ".";
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
  } 
  char entity_sym = target_cell.getOccupant()->getSymbol();
  auto e = static_pointer_cast<Enemy>(target_cell.getOccupant());
  if (entity_sym == 'E' || entity_sym == 'L' ||
      entity_sym == 'W' || entity_sym == 'O' || entity_sym == 'D') {
    atkStatus as = player->attack(e);
    if (as == atkStatus::Kill) {
      theGrid->removeEntity(e->getPosn());
      enemies.erase(enemies.begin() + enemy_index(e));
    }  
    return player->actionText(e, as);
  } 
  else if (entity_sym == 'M') {
    auto mt  = static_pointer_cast<Merchant>(e);
    mt->turnHostile();
    atkStatus as = player->attack(e);
    if (as == atkStatus::Kill) {
      Posn e_Posn = e->getPosn();
      theGrid->removeEntity(e->getPosn());
      enemies.erase(enemies.begin() + enemy_index(e));
      auto tm = make_shared<Treasure_Merchant>();
      theGrid->placeEntity(tm,e_Posn);
    }
    return player->actionText(e, as);
  }
  else if (entity_sym == 'H') {
    atkStatus as = player->attack(e);
    if (as == atkStatus::Kill) {
      Posn e_Posn = e->getPosn();
      theGrid->removeEntity(e->getPosn());
      enemies.erase(enemies.begin() + enemy_index(e));
      auto tn1 = make_shared<Treasure_Normal>();
      theGrid->placeEntity(tn1,e_Posn);
      if (isAnyValidNeighbour(e_Posn)) {
        auto tn2 = make_shared<Treasure_Normal>();
        theGrid->placeEntity(tn2,validRandomNeighbour(e_Posn));
      }
      else player->addGold(2);
      }
     return player->actionText(e, as);
   }
   return player->actionText(e, atkStatus::InvalidTarget);
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
}*/

void Game::freeze() {
  frozen = !frozen;
}

bool valid_dir(string dir) {
  if (dir == "ea" || dir == "no" || dir == "so" || dir == "we" ||
      dir == "sw" || dir == "se" || dir == "nw" || dir == "ne") {
    return true;
  }
  else {
    return false;
  }
}

void useTogether(Player &user, Entity &used) {
  used.beUsedBy(user);
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
  if (s == "r") {
    enemies.clear();
    player = nullptr;
    theGrid->init("maps/basicFloor.txt", 1);
    //player = make_shared<Shade>();
    //print("");
    cout << "Insert a new race please" << endl;
    while (true) {
      getline(cin, s);
      try {
        startRound(s);
      } catch (Invalid_behave& ib) {
        cout << ib.what() << endl;
        continue;
      }
      break;
    }
    return "The player entered the dungeon";
  }
  else if (s == "a") {
    iss >> s;
    if (valid_dir(s)) {
      full_printing_msg += PlayerAttack(s);
      player->endTurn();
    }
  }
  else if (s == "u") {
    iss >> s;
    //cout << "use detected" << endl;
    if (valid_dir(s)) {
      Posn target = dir_to_posn(player->getPosn(), s);
      //cout << "target posn: " << target.r << " , " << target.c << endl;
      if (theGrid->hasUsable(target)) { // if the occupant of target can be used
        //cout << "target can be used " << endl;
        useTogether(*player, *(theGrid->getCell(target).getOccupant())); // make player use the occupant of target
        full_printing_msg += "PC uses " + theGrid->getCell(target).getOccupant()->getName() + ".";
        theGrid->removeEntity(target);  //remove target from the board
        movePlayer(s); //fdsmakmfdskmfsdlfdkslk
        player->endTurn();
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
    quit = true;
    //throw 0;
  }
  else if (valid_dir(s)) {
    full_printing_msg += movePlayer(s);
    full_printing_msg += potion_near();
    player->endTurn();
  } 
  if (!frozen) {
    full_printing_msg += moveEnemies();
  }
  return full_printing_msg;
}

void Game::print(string printing_msg) {
  cout << *theGrid;
  cout << "Race: " << player->getName() << " Gold: " << to_string(player->finalScore()) 
       << "                                                  Floor "<<theGrid->getLevel()<<endl;
  cout << "HP: " << to_string(player->getHp()) << endl;
  cout << "Atk: " << to_string(player->getAtk()) << endl;
  cout << "Def: " << to_string(player->getDef()) << endl;
  cout << "Action: " << printing_msg << endl; 
}

bool Game::gameOver() {
  int p_score = player->finalScore();
  if(player->getHp() <= 0) {
    cout<< "You have been slain! Game Over."<<endl;
    if(dynamic_pointer_cast<Shade>(player)) p_score *= 1.5;
    cout<< "Your final score: " <<p_score<<"."<<endl;
    return true;
  } else if (theGrid->getLevel() == 6) {
    cout<< "Congratulations, you reach the top of the floor, you won the game!"<<endl;
    if(dynamic_pointer_cast<Shade>(player)) p_score *= 1.5;
    cout<< "Your final score: " <<p_score<<"."<<endl;
    return true;
  } 
  else if (quit == true) {
    quit = false;
    return true;
  }
  else return false;
}
