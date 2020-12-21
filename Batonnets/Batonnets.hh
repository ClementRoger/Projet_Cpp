#pragma once 
#include <iostream>

class Batonnets{
 
 public:

  Batonnets(int NB_BATONNETS);
  void play();
  bool check_victory();
  void print();
  bool user_plays();
  bool IA_plays();

 private:

  std::size_t nb_batonnets;
  bool victory;

};  