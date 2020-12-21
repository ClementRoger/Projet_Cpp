#pragma once 
#include <iostream>

class Juste_Prix{
 
 public:

  Juste_Prix(size_t NB_TENTATIVES, int NMIN, int NMAX);
  void play();
  bool check_victory();
  bool check_entry(double number);

 private:

  std::size_t mystery_number;
  std::size_t nb_tentatives;
  bool victory;
  std::size_t Nmin;
  std::size_t Nmax;

};  