#pragma once 
#include <iostream>
#include "../MiniJeu.hh"

class Batonnets : public MiniJeu{
 
 public:

  Batonnets(std::size_t NB_BATONNETS,std::size_t nb);
  void play();
  void print();
  bool user_plays();
  bool IA_plays();
  void transition();
  //bool win();

 private:

  std::size_t nb_batonnets;

};  