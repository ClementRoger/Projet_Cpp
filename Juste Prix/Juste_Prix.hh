#pragma once 
#include <iostream>

class Juste_Prix{
 
 public:

  Juste_Prix();
  void play();
  bool check_victory();

 private:

  std::size_t mystery_number;
  std::size_t nb_tentatives;
  bool victory;

};  