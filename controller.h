#ifndef __CONTROLLER_H__
#define __CONTROLLER_H__

#include <istream>
#include <string>

class Game;

class Controller {
  std::istream &in;
  std::string toSend;
public:
  Controller(std::istream &i);
  void getCommand();
  void sendRace(Game &g);
  void sendCommand(Game &g);
};

#endif
