#pragma once 
#include <iostream>
#include "MiniJeu.hh"
#include <SFML/Graphics.hpp>
#include <string.h>

#define APP_SIZE_X3 800
#define APP_SIZE_Y3 600

class Batonnets : public MiniJeu{
 
 public:

  Batonnets(const std::size_t NB_BATONNETS,const std::size_t nb);
  void play();
  void print()const;
  bool user_plays();
  bool IA_plays();
  int generer_nb_aleatoire(const int min, const int max)const;
  void init_background(sf::RenderWindow& window)const;
  bool check_entry(const std::string entry)const;
  void display(sf::RenderWindow& window);
  void affiche_batonnets(sf::RenderWindow& window)const;
  void print_end(const bool winner,sf::RenderWindow &window);
  void init_transition(sf::RenderWindow &window)const;
  std::wstring setFinalText(const bool win)const;

  void set_number(const int nb) {
    number = nb;
  }
  void set_user_entry(const std::string str) {
    user_entry = str;
  }
  std::size_t get_nb_batonnets() const{
    return nb_batonnets;
  }
  std::size_t get_last_move() const{
    return last_move;
  }
  bool get_tour() const{
    return tour;
  }

 private:

  std::size_t nb_batonnets;
  bool difficulty; // True if easy, false if difficult
  bool tour; // A l'IA de jouer si tour == false, sinon au tour du joueur. Le joueur commence
  std::size_t last_move;
  std::string user_entry;
  int number;

};  