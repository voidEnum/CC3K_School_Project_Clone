#ifndef __POTION_H__
#define __POTION_H__

#include "item.h"
#include <memory>

class Potion : public Item { 
protected:
  int potency;  // represents the power of the potion.
  Potion(int n);
public:
  // All subclasses must implement isRevealed and reveal
  // to keep track of if one potion of that type has been
  // used.
  virtual bool isRevealed() const = 0;
  virtual void reveal() = 0;


  virtual bool isUsable() const override;
  virtual int getPotency() const;

  // All subclass potions must implement beUsedBy to properly
  // interact with player classes
  virtual std::shared_ptr<Player> beUsedBy(std::shared_ptr<Player> user) = 0;
};

// Declaring default potions here as well to reduce number of files
class Potion_RH : public Potion, public std::enable_shared_from_this<Potion_RH> {
  static bool revealed;
public:
  Potion_RH(int p = 10);
  bool isRevealed() const override;
  void reveal() override;
  std::shared_ptr<Player> beUsedBy(std::shared_ptr<Player> user) override;
};

class Potion_PH : public Potion, public std::enable_shared_from_this<Potion_PH> {
  static bool revealed;
public:
  Potion_PH(int p = 10);
  bool isRevealed() const override;
  void reveal() override;
  std::shared_ptr<Player> beUsedBy(std::shared_ptr<Player> user) override;
};

class Potion_BA : public Potion, public std::enable_shared_from_this<Potion_BA> {
  static bool revealed;
public:
  Potion_BA(int p = 5);
  bool isRevealed() const override;
  void reveal() override;
  std::shared_ptr<Player> beUsedBy(std::shared_ptr<Player> user) override;
};

class Potion_WA : public Potion, public std::enable_shared_from_this<Potion_WA>{
  static bool revealed;
public:
  Potion_WA(int p = 5);
  bool isRevealed() const override;
  void reveal() override;
  std::shared_ptr<Player> beUsedBy(std::shared_ptr<Player> user) override;
};

class Potion_BD : public Potion, public std::enable_shared_from_this<Potion_BD> {
  static bool revealed;
public:
  Potion_BD(int p = 5);
  bool isRevealed() const override;
  void reveal() override;
  std::shared_ptr<Player> beUsedBy(std::shared_ptr<Player> user) override;
};

class Potion_WD : public Potion, public std::enable_shared_from_this<Potion_WD> {
  static bool revealed;
public:
  Potion_WD(int p = 5);
  bool isRevealed() const override;
  void reveal() override;
  std::shared_ptr<Player> beUsedBy(std::shared_ptr<Player> user) override;
};

#endif
