#pragma once
#include <cstdlib>
#include <iostream>
#include <vector>
#include <time.h>
#include <string>
#include <SFML/Graphics.hpp>

#define TEXTURE_CELL "img/cell.png"
#define TEXTURE_1 "img/1.png"
#define TEXTURE_2 "img/2.png"
#define TEXTURE_3 "img/3.png"
#define TEXTURE_4 "img/4.png"
#define TEXTURE_5 "img/5.png"
#define TEXTURE_6 "img/6.png"
#define TEXTURE_7 "img/7.png"
#define TEXTURE_8 "img/8.png"
#define TEXTURE_BOMB "img/explodedBomb.png"
#define TEXTURE_NONE "img/none.png"
#define TEXTURE_WIN "img/you_win.png"
#define TEXTURE_LOSE "img/game_over.png"
#define TEXTURE_NAME "img/demineur.png"
#define TEXTURE_BACKGROUND "img/background.jpg"
#define TEXTURE_BACKNAME "img/bomb.png"
#define TEXTURE_BACKGAME "img/nb_try.png"

#define APP_SIZE_X 800
#define APP_SIZE_Y 600
#define IMG_SIZE 32 

class Demineur {
 
 public:
 
  Demineur(const std::size_t count, const std::size_t bomb, const std::size_t gridsize); //constructeur par défaut

  ~Demineur();

  void initBomb(std::vector<std::vector<int>>&tab,const std::size_t gridsize);
  void checkBomb(std::vector<std::vector<int>>&tab, const std::size_t gridsize);
  bool checkBool(const std::vector<std::vector<bool>>tab);
  void reveal(std::vector<std::vector<bool>>&tmp, const std::vector<std::vector<int>>tab, const std::size_t i, const std::size_t j);
  bool win(const bool flag);

  /* Console */
  void play();
  void affichage(const std::vector<std::vector<bool>>matrice);
  
  /* For SFML */
  void display();
  bool test_grid_border(const sf::Vector2i position);
  bool Get_Mouse_Click(sf::RenderWindow& window, sf::Vector2i& position);
  void print_grid(sf::RenderWindow &window,const std::vector<std::vector<bool>>matrice);
  void number_texture(const int val, sf::Texture& texture);
  void print_end(bool winner,sf::RenderWindow &window);
  void init_background(sf::RenderWindow &window);

  /* Getters & Setters */
  std::size_t get_nb_try() const { return _nb_try; }
  void set_nb_try(size_t nb){ _nb_try = nb;}
  std::size_t get_nb_bomb() const { return _nb_bomb; }
  std::vector<std::vector<int>> get_plateau() const{ return _plateau;}
  std::vector<std::size_t> get_bomb_x() const{ return _bomb_x;}
  std::vector<std::size_t> get_bomb_y() const{ return _bomb_y;}


 private:
  std::vector<std::vector<int>>_plateau;
  std::size_t _nb_try; // nombre d'erreurs possible 
  std::size_t _nb_bomb; //nombre de bombes
  std::vector<std::size_t> _bomb_x; // coordonnées des bombes en x
  std::vector<std::size_t> _bomb_y; // coordonnées des bombes en y

};
