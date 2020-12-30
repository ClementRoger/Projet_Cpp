#pragma once 
#include <iostream>

#include "../MiniJeu.hh"

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

#define APP_SIZE_X 800
#define APP_SIZE_Y 600

class Juste_Prix : public MiniJeu{
 
 public:

  Juste_Prix(size_t NB_TENTATIVES, int NMIN, int NMAX);
  void play();
  bool check_entry(std::string entry);
  void transition();
  void init_background(sf::RenderWindow& window);
  void display(sf::RenderWindow& window);

 private:

  std::size_t mystery_number;
  std::size_t Nmin;
  std::size_t Nmax;
  std::string user_entry;
  std::string result;

};  