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

  Juste_Prix(size_t NB_TENTATIVES, int NMIN, int NMAX);
  void play();
  bool check_entry(const std::string entry);
  void transition(sf::RenderWindow &window);
  void init_background(sf::RenderWindow& window);
  void display(sf::RenderWindow& window);
  void print_end(bool winner,sf::RenderWindow &window);

 private:

  std::size_t Nmin;
  std::size_t Nmax;
  sf::String result;

};  