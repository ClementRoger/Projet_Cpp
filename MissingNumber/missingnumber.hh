#pragma once
#include <cstdlib>
#include <iostream>
#include <string>
#include <fstream> 
#include <vector>
#include <time.h>
#include <sstream>


#include "TextEntry.hh"

#include "../MiniJeu.hh"

#define TEXTURE_BACKGROUND "img/background.png"

#define TEXTURE_BACKNAME "img/arrow.png"
#define TEXTURE_NAME "img/title.png"
#define TEXTURE_GRID "img/grid.png" 
#define TEXTURE_LETTERS "img/tab.png" 
#define TEXTURE_WIN "img/you_win.png"
#define TEXTURE_LOSE "img/game_over.png"


#define APP_SIZE_X 800
#define APP_SIZE_Y 600

class Missingnumber : public MiniJeu {
 
 public:
 
  Missingnumber(std::fstream& in,const std::size_t count); 

  ~Missingnumber();

  void play();
  void affichage(std::vector<std::vector<std::string>>matrice);
  bool validity_test(const std::string tmp);

  /* SFML */
  void display();
  void init_background(sf::RenderWindow &window);
  void print_end(bool winner,sf::RenderWindow &window);
  void print_game(sf::RenderWindow &window);
  void transition();

  /* Getters & Setters */
  std::string get_solution() const { return _solution; }
  std::vector<std::vector<std::string>> get_matrice() const{ return _matrice;}

  std::string get_user_entry() const { return _user_entry; }
  void  set_user_entry(const std::string tmp) { _user_entry = tmp; }

 private:
  std::vector<std::vector<std::string>>_matrice;
  std::string _solution;
  std::string _user_entry;

};
