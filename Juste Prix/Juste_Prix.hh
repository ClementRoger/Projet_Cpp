#pragma once 
#include <iostream>

#include "../MiniJeu.hh"

class Juste_Prix : public MiniJeu{
 
 public:

  Juste_Prix(size_t NB_TENTATIVES, int NMIN, int NMAX);
  void play();
  bool check_entry(double number);
  void transition();

	//bool win();
 private:

  std::size_t mystery_number;
  std::size_t Nmin;
  std::size_t Nmax;

};  