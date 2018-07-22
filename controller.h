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
  std::string sendCommand(Game &g);
  void requestDisplay(Game &g, std::string);
};

#endif
