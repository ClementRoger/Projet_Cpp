#pragma once
#include <cstdlib>
#include <iostream>
#include <string>
#include <fstream>
#include <SFML/Graphics.hpp>

#include "MiniJeu.hh"

class MiniJeuAvecSolution : public MiniJeu{

public:

  MiniJeuAvecSolution(std::size_t nb_try, bool victory):MiniJeu(nb_try,false){

  }

  ~MiniJeuAvecSolution(){};

  virtual void play() = 0;
  virtual void transition(sf::RenderWindow &window) = 0;
  virtual void print_end(bool winner,sf::RenderWindow &window) = 0;
  virtual bool check_entry(const std::string entry) = 0;

  /* Getters & Setters */
  std::string get_user_entry() const { return _user_entry; }
  void  set_user_entry(const std::string tmp) { _user_entry = tmp; }

  std::string get_solution() const { return _solution; }
  void set_solution( const std::string tmp ) { _solution = tmp;}
  
protected:
  std::string _user_entry;
  std::string _solution;

};