#pragma once
#include <cstdlib>
#include <iostream>
#include <vector>
#include <time.h>
#include <string>
#include <SFML/Graphics.hpp>

#define TEXTURE_CELL "img_demineur/cell.png"
#define TEXTURE_1 "img_demineur/1.png"
#define TEXTURE_2 "img_demineur/2.png"
#define TEXTURE_3 "img_demineur/3.png"
#define TEXTURE_4 "img_demineur/4.png"
#define TEXTURE_5 "img_demineur/5.png"
#define TEXTURE_6 "img_demineur/6.png"
#define TEXTURE_7 "img_demineur/7.png"
#define TEXTURE_8 "img_demineur/8.png"
#define TEXTURE_BOMB "img_demineur/explodedBomb.png"
#define TEXTURE_NONE "img_demineur/none.png"
#define TEXTURE_WIN "img_demineur/you_win.png"
#define TEXTURE_LOSE "img_demineur/game_over.png"
#define TEXTURE_NAME "img_demineur/demineur.png"
#define TEXTURE_BACKGROUND "img_demineur/background.jpg"
#define TEXTURE_BACKNAME "img_demineur/bomb.png"
#define TEXTURE_BACKGAME "img_demineur/nb_try.png"

#define APP_SIZE_X 800
#define APP_SIZE_Y 600
#define IMG_SIZE 32 

#include "../MiniJeu.hh"

class Demineur:public MiniJeu{
 
 public:
 
  Demineur(const std::size_t count, const std::size_t bomb, const std::size_t gridsize);

  ~Demineur();

  void initBomb(std::vector<std::vector<int>>&tab,const std::size_t gridsize);
  void checkBomb(std::vector<std::vector<int>>&tab, const std::size_t gridsize);
  bool checkBool(const std::vector<std::vector<bool>>tab);
  void reveal( const std::size_t i, const std::size_t j);

  /* Console */
  void affichage(const std::vector<std::vector<bool>>matrice);
  
  /* For SFML */
  void display(sf::RenderWindow& window);
  void play();
  bool test_grid_border(const sf::Vector2i position);
  bool Get_Mouse_Click(sf::RenderWindow& window,sf::Vector2i& position);
  void print_grid(sf::RenderWindow &window,const std::vector<std::vector<bool>>matrice);
  void number_texture(const int val, sf::Texture& texture);
  void print_end(bool winner,sf::RenderWindow &window);
  void init_background(sf::RenderWindow &window);
  void transition();

  /* Getters & Setters */
  std::size_t get_nb_bomb() const { return _nb_bomb; }
  std::vector<std::vector<int>> get_plateau() const{ return _plateau;}
  std::vector<std::vector<bool>> get_open_tiles() const{ return _open_tiles;}
  void set_open_tiles(const bool val, const size_t x, const size_t y) { _open_tiles[x][y] = val;}
  std::vector<std::size_t> get_bomb_x() const{ return _bomb_x;}
  std::vector<std::size_t> get_bomb_y() const{ return _bomb_y;}
  int get_pos_x() const { return pos_x;}
  int get_pos_y() const { return pos_y;}
  void set_pos_x(const int position){ pos_x = position; }
  void set_pos_y(const int position){ pos_y = position; }


 private:
  std::vector<std::vector<int>>_plateau;
  std::size_t _nb_bomb; //nombre de bombes
  std::vector<std::size_t> _bomb_x; // coordonnées des bombes en x
  std::vector<std::size_t> _bomb_y; // coordonnées des bombes en y
  std::vector<std::vector<bool>>_open_tiles;

  int pos_x;
  int pos_y;

};
