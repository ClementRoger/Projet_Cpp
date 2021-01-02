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
#include "../MiniJeuAvecSolution.hh"

#define TEXTURE_BACKGROUND2 "img_missing/background.png"

#define TEXTURE_BACKNAME2 "img_missing/arrow.png"
#define TEXTURE_NAME2 "img_missing/title.png"
#define TEXTURE_GRID2 "img_missing/grid.png" 
#define TEXTURE_LETTERS2 "img_missing/tab.png" 
#define TEXTURE_WIN2 "img_missing/you_win.png"
#define TEXTURE_LOSE2 "img_missing/game_over.png"
#define TEXTURE_TRANSITION2 "img_missing/wall.jpeg"


#define APP_SIZE_X2 800
#define APP_SIZE_Y2 600

class Missingnumber : public MiniJeuAvecSolution {
 
 public:
 
  Missingnumber(std::fstream& in,const std::size_t count); 

  ~Missingnumber();

  void play();
  void affichage(std::vector<std::vector<std::string>>matrice);
  bool check_entry(const std::string entry);

  /* SFML */
  void display(sf::RenderWindow &window);
  void init_background(sf::RenderWindow &window);
  
  void create_text(sf::RenderWindow &window, const sf::Font font, const std::size_t fontSize, const std::size_t x, const std::size_t y, const std::string input);
  void create_text(sf::RenderWindow &window, const sf::Font font, const std::size_t fontSize, const std::size_t x, const std::size_t y, const std::wstring input);
  void create_sprite(sf::RenderWindow &window, const std::size_t x, const std::size_t y, const std::string file);
  
  void print_end(bool winner,sf::RenderWindow &window);
  void print_game(sf::RenderWindow &window);

  void transition(sf::RenderWindow &window);
  std::wstring setFinalText(bool win);
  void init_transition(sf::RenderWindow &window);

  /* Getters & Setters */
  std::vector<std::vector<std::string>> get_matrice() const{ return _matrice;}

  std::string get_user_entry() const { return _user_entry; }
  void  set_user_entry(const std::string tmp) { _user_entry = tmp; }

 private:
  std::vector<std::vector<std::string>>_matrice;
  std::string _solution;
  std::string _user_entry;

};
