#ifndef _INVALID_BEHAVE_H_
#define _INVALID_BEHAVE_H_
 
class Invalid_behave {
  std::string type;
 public:
  Invalid_behave(std::string type);
  std::string what();
};

#endif
