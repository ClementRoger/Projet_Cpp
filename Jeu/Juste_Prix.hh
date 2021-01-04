#pragma once 
#include <iostream>

#include "../MiniJeu.hh"
#include "../MiniJeuAvecSolution.hh"

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

#define APP_SIZE_X4 800
#define APP_SIZE_Y4 600

class Juste_Prix : public MiniJeuAvecSolution{
 
 public:

  Juste_Prix(const size_t NB_TENTATIVES, const int NMIN, const int NMAX);
  void play();
  bool check_entry(const std::string entry)const;
  
  void init_background(sf::RenderWindow& window)const;
  void display(sf::RenderWindow& window);
  void print_end(const bool winner,sf::RenderWindow &window);
  std::wstring setFinalText(const bool win)const;
  void init_transition(sf::RenderWindow &window)const;

 private:

  std::size_t Nmin;
  std::size_t Nmax;
  sf::String result;

};  