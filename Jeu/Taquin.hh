#pragma once 
#include <iostream>
#include "../MiniJeu.hh"
#include <SFML/Graphics.hpp>
#include <string.h>

#define APP_SIZE_X5 800
#define APP_SIZE_Y5 600

class Taquin : public MiniJeu{
 
 public:

  Taquin(const std::size_t NB_TRY);
  void play();
  void init_background(sf::RenderWindow& window)const;
  bool check_move(const int number)const; // Renvoie true si on peut bouger la case, false sinon
  void display(sf::RenderWindow& window);
  void transition(sf::RenderWindow& window);
  void init_names(); //Initialise le vecteur contenant le nom des fichiers images
  void init_position(const std::vector<int> v); //Initialise le vecteur contenant les coordonnées des cases
  void init_case_vide(); //Initialise le vecteur contenant les coordonnées de la case vide
  void init_solution(); // //Initialise le vecteur contenant les coordonéées des cases de la solution
  int get_image_number(const int x, const int y)const; //Renvoie le numéro de l'image (l'index du vecteur) sur laquelle l'utilisateur a cliquée
  bool check_victory()const; //Renvoie true si les cases sont toutes à la bonne place, false sinon
  void read_file(); // Remplit le vecteur avec la grille du fichier
  void init_transition(sf::RenderWindow &window)const;
  std::wstring setFinalText(const bool win)const;
  void print_end(const bool winner,sf::RenderWindow &window);

 private:

  std::vector<sf::Vector2f> v_position;
  std::vector<sf::Vector2f> v_solution;
  std::vector<std::string> v_name;
  sf::Vector2f case_vide;
  int number;
};  

inline bool operator==(std::vector<sf::Vector2f> v1, std::vector<sf::Vector2f> v2) {

  for (int i = 0; i < 8; ++i) { 

    if( (v1[i].x != v2[i].x) || (v1[i].y != v2[i].y) ) {
            
      return false;
    }
  }

  return true;
}

