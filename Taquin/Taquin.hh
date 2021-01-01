#pragma once 
#include <iostream>
#include "../MiniJeu.hh"
#include <SFML/Graphics.hpp>
#include <string.h>

#define APP_SIZE_X 800
#define APP_SIZE_Y 600

class Taquin : public MiniJeu{
 
 public:

  Taquin(std::size_t NB_TRY);
  void play();
  void init_background(sf::RenderWindow& window);
  bool check_move();
  void display(sf::RenderWindow& window);
  void transition();
  void init_names();
  void init_position();

 private:

  std::size_t nb_try;
  std::vector<sf::Vector2f> v_position;
  std::vector<std::string> v_name;

};  