#ifndef _GAME_H_
#define _GAME_H_

#include <memory>
#include <vector>
#include <functional>

#include "grid.h"
#include "enemy.h"

class Player;
class Potion;
class Treasure;

class Game {
  bool quit;
  static const int NUM_TREASURE_SPAWN = 10;
  static const int NUM_POTION_SPAWN = 10;

  static const std::vector<int> POTION_SPAWN_RATES;
  static const std::vector<std::function<std::shared_ptr<Potion>()>> POTION_MAKERS;

  static const std::vector<int> TREASURE_SPAWN_RATES;
  static const std::vector<std::function<std::shared_ptr<Treasure>()>> TREASURE_MAKERS;

  class GenericFactory {
    GenericFactory() = default;
  public :
    static GenericFactory &getInstance();
    template <class ToMake>
    std::shared_ptr<ToMake> make(std::vector<int> s_rates,
          std::vector<std::function<std::shared_ptr<ToMake>()>> makers) {
      // get the sum of the spawn rates
      int s_rate_sum = 0;
      for (auto i: s_rates) {
        s_rate_sum += i;
      }
      
      // generate a random number between 1 and s_rate_sum inclusive
      int pType = rand() % s_rate_sum + 1;
      // for each element of S_RATES, add its value to accumulator
      // when the accumulator is >= the random number, use MAKERS
      // to spawn the appropriate Potion type.
      int accumulated_s_rate = 0;
      for (int i = 0, end = s_rates.size();i < end; i++) {
        accumulated_s_rate += s_rates[i];
        if (accumulated_s_rate >= pType) {
          return makers[i]();
        }
      }
    // if function gets here, nothing was spawned. should not happen
      return nullptr;
    }
  };
  /* Not needed if generic works
  class PotionFactory {
    PotionFactory() = default;
    static const std::vector<int> S_RATES;
    static const std::vector<std::function<std::shared_ptr<Potion>()>> MAKERS;
  public:
    static PotionFactory& getInstance();
    std::shared_ptr<Potion> make();
  }; */

  /*class TreasureFactory {
    TreasureFactory() = default;
    static const std::vector<int> S_RATES;
    static const std::vector<std::function<std::shared_ptr<Treasure>()>> MAKERS;
  public:
    static TreasureFactory &getInstance();
    std::shared_ptr<Treasure> make();
  };*/
    
  std::unique_ptr<Grid> theGrid;
  std::shared_ptr<Player> player;
  std::vector<std::shared_ptr<Enemy>>enemies;
  //std::vector<std::shared_ptr<Potion>>potions;
  bool frozen = false;
  bool isHostile = false;
  // methods
 public:
  Game();
  bool startRound(const std::string &race);
  std::string processTurn(const std::string &command);
  void print(std::string printing_msg);
  bool gameOver();
 private:
  void generateEnemies(std::vector<std::vector<Cell *>> &vcham);
  void generatePotions(std::vector<std::vector<Cell *>> &vcham);
  void generateTreasures(std::vector<std::vector<Cell *>> &vcham); // all normal treasures for now
  void generatePlayer(const std::string &race, std::vector<std::vector<Cell *>> &vvc); // generic player for now
  void generateStair(std::vector<std::vector<Cell *>> &vvc);
  std::string moveEnemies();
  void changeFloor(Posn playerposn);
  //void update_display();
  std::string movePlayer(const std::string &direction);
  std::string potion_near();
  int enemy_index(std::shared_ptr<Enemy>e);
  std::string PlayerAttack(std::string direction);
  //void enemyAttack();
  //void Player_usePotion();
  void freeze();
  void chackvalid();
  bool checkIfHostile() const;
  void changeHostile();
  bool isAnyValidNeighbour(Posn p);
  Posn validRandomNeighbour(Posn p);
  bool validSpot(Cell &cell);
  bool isInAttackRange(Posn p);
  static bool sort_function(std::shared_ptr<Enemy>e1, std::shared_ptr<Enemy>e2);
  void enemy_sort(std::vector<std::shared_ptr<Enemy>>&enemy_vector);
};

#endif 
