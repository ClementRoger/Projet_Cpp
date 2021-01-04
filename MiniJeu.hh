#pragma once
#include <cstdlib>
#include <iostream>
#include <string>
#include <fstream>
#include <SFML/Graphics.hpp>

class MiniJeu{

public:

  MiniJeu(std::size_t nb_try, bool victory){
    _victory = victory;
    _nb_try = nb_try;
  }

  virtual ~MiniJeu(){};

  virtual void play() = 0;
  virtual void display(sf::RenderWindow &window) = 0;
  virtual void init_background(sf::RenderWindow& window)const = 0;
  
  virtual void transition(sf::RenderWindow &window) = 0;
  virtual void print_end(const bool winner,sf::RenderWindow &window) = 0;

  /* Getters & Setters */
  size_t get_nb_try() const { return _nb_try; }
  void set_nb_try(const size_t nb){ _nb_try = nb;}
  bool win() const {return _victory;}
  void set_win(const bool flag) {_victory = flag; }


protected:
  std::size_t _nb_try;
  bool _victory;

};