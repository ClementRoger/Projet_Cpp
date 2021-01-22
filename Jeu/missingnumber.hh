#pragma once
#include <cstdlib>
#include <iostream>
#include <string>
#include <fstream> 
#include <vector>
#include <time.h>
#include <sstream>


#include "TextEntry.hh"

#include "MiniJeu.hh"
#include "MiniJeuAvecSolution.hh"

#define TEXTURE_BACKGROUND2 "img_missing/background.png"

#define TEXTURE_BACKNAME2 "img_missing/arrow.png"
#define TEXTURE_NAME2 "img_missing/title.png"
#define TEXTURE_GRID2 "img_missing/grid.png" 
#define TEXTURE_LETTERS2 "img_missing/paint_bg.png" 
#define TEXTURE_WIN2 "img_missing/you_win.png"
#define TEXTURE_LOSE2 "img_missing/game_over.png"
#define TEXTURE_TRANSITION2 "img_missing/wall.jpeg"


#define APP_SIZE_X2 800
#define APP_SIZE_Y2 600

class Missingnumber : public MiniJeuAvecSolution {
 
 public:
 
  Missingnumber(std::fstream& in,const std::size_t count); 
  Missingnumber(const std::size_t nb);

  ~Missingnumber();

  void play();
  void fill_vector(std::fstream& in,std::vector<std::vector<std::string>>&tempmatrice);
  void find_solution(std::stringstream& stream,std::size_t& tmp);
  void find_matrice(std::stringstream& stream,std::vector<std::vector<std::string>>&tempmatrice,std::size_t& tmp) const;
  void affichage(std::vector<std::vector<std::string>>matrice);
  bool check_entry(const std::string entry) const;

  /* SFML */
  void display(sf::RenderWindow &window);
  void init_background(sf::RenderWindow &window)const;
  
  void create_text(sf::RenderWindow &window, const sf::Font font, const std::size_t fontSize, const std::size_t x, const std::size_t y, const std::string input)const;
  void create_text(sf::RenderWindow &window, const sf::Font font, const std::size_t fontSize, const std::size_t x, const std::size_t y, const std::wstring input)const;
  void create_sprite(sf::RenderWindow &window, const std::size_t x, const std::size_t y, const std::string file)const;
  
  void print_end(const bool winner,sf::RenderWindow &window);
  void print_game(sf::RenderWindow &window)const;

  std::wstring setFinalText(const bool win)const;
  void init_transition(sf::RenderWindow &window)const;

  /* Getters & Setters */
  std::vector<std::vector<std::string>> get_matrice() const{ return _matrice;}

 private:
  std::vector<std::vector<std::string>>_matrice;

};
