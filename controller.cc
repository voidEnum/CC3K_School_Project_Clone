#include "controller.h"

#include "game.h"

Controller::Controller(std::istream &i): in{i}  {}

void Controller::getCommand() {
  std::getline(in, toSend);
}

void Controller::sendRace(Game &g) {
  g.startRound(toSend);
}

std::string Controller::sendCommand(Game &g) {
  return g.processTurn(toSend);
}

void Controller::requestDisplay(Game &g, std::string print_msg) {
  //std::cout << "controller p_msg: " << print_msg << std::endl;
  g.print(print_msg);
}
