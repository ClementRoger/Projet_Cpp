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
  bool check_move(int number); // Renvoie true si on peut bouger la case, false sinon
  void display(sf::RenderWindow& window);
  void transition(sf::RenderWindow& window);
  void init_names(); //Initialise le vecteur contenant le nom des fichiers images
  void init_position(); //Initialise le vecteur contenant les coordonnées des cases
  void init_case_vide(); //Initialise le vecteur contenant les coordonnées de la case vide
  void init_solution(); // //Initialise le vecteur contenant les coordonéées des cases de la solution
  int get_image_number(int x, int y); //Renvoie le numéro de l'image (l'index du vecteur) sur laquelle l'utilisateur a cliquée
  bool check_victory();

 private:

  std::size_t nb_try;
  std::vector<sf::Vector2f> v_position;
  std::vector<sf::Vector2f> v_solution;
  std::vector<std::string> v_name;
  sf::Vector2f case_vide;
  int number;
};  

bool operator==(std::vector<sf::Vector2f> v1, std::vector<sf::Vector2f> v2) {

  for (int i = 0; i < 8; ++i) { 

        if( (v1[i].x != v2[i].x) || (v1[i].y != v2[i].y) ) {
            
            return false;
        }
    }

  return true;
}
