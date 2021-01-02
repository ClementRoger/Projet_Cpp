#pragma once 
#include <iostream>
#include "../MiniJeu.hh"
#include <SFML/Graphics.hpp>
#include <string.h>

#define APP_SIZE_X3 800
#define APP_SIZE_Y3 600

class Batonnets : public MiniJeu{
 
 public:

  Batonnets(std::size_t NB_BATONNETS,std::size_t nb);
  void play();
  void print();
  bool user_plays();
  bool IA_plays();
  void transition(sf::RenderWindow &window);
  int generer_nb_aleatoire(int min, int max);
  void init_background(sf::RenderWindow& window);
  bool check_entry(std::string entry);
  void display(sf::RenderWindow& window);
  void affiche_batonnets(sf::RenderWindow& window);
  void print_end(bool winner,sf::RenderWindow &window);
  void init_transition(sf::RenderWindow &window);
  std::wstring setFinalText(bool win);

 private:

  std::size_t nb_batonnets;
  bool difficulty; // True if easy, false if difficult
  bool tour; // A l'IA de jouer si tour == false, sinon au tour du joueur. Le joueur commence
  std::size_t last_move;
  std::string user_entry;

};  