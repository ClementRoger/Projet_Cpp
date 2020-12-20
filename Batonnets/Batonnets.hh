#pragma once 
#include <iostream>

class Batonnets{
 
 public:

  Batonnets();
  void play();
  bool check_victory();
  void print();

 private:

  std::size_t nb_batonnets;
  bool victory;

};  