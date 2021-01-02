#include "Taquin.hh"
#include <cstdlib>
#include <iostream>
#include <unistd.h>
#include <ctime>

using namespace std;

#define X_init 250 //X de la case en haut à gauche
#define Y_init 150 // Y de la case en haut à gauche
#define d 100 // ecart entre deux cases adjacentes

Taquin :: Taquin(size_t NB_TRY) : MiniJeu(NB_TRY,false) {

	nb_try = NB_TRY;

	init_position();
	init_names();
	init_case_vide();
	init_solution();
}

void Taquin :: init_names() {

	v_name.push_back("images/1.png");
	v_name.push_back("images/2.png");
	v_name.push_back("images/3.png");
	v_name.push_back("images/4.png");
	v_name.push_back("images/5.png");
	v_name.push_back("images/6.png");
	v_name.push_back("images/7.png");
	v_name.push_back("images/8.png");
}

void Taquin :: init_position() { // La grille est 481 / 576 / 23. La case 1 aura donc comme position (X_init + 2*d, Y_init) par exemple, d étant la largeur d'une case (toutes les cases sont carrées et ont la même taille) 
	
	v_position.push_back(sf::Vector2f(X_init + 2*d,Y_init)); // Case 1
	v_position.push_back(sf::Vector2f(X_init,Y_init + 2*d)); // Case 2
	v_position.push_back(sf::Vector2f(X_init + d,Y_init + 2*d)); // Case 3
	v_position.push_back(sf::Vector2f(X_init,Y_init)); // Case 4
	v_position.push_back(sf::Vector2f(X_init,Y_init + d)); // Case 5
	v_position.push_back(sf::Vector2f(X_init + 2*d,Y_init + d)); // Case 6
	v_position.push_back(sf::Vector2f(X_init + d,Y_init + d)); // Case 7
	v_position.push_back(sf::Vector2f(X_init + d,Y_init)); // Case 8

}

void Taquin :: init_case_vide() { // Initialement la case vide est la case tout en bas à droite

	case_vide.x = X_init + 2 * d;
	case_vide.y = Y_init + 2 * d;
}

void Taquin :: init_solution() { 

	v_solution.push_back(sf::Vector2f(X_init,Y_init)); // La case 1 est tout en haut à gauche dans la solution
	v_solution.push_back(sf::Vector2f(X_init + d,Y_init)); //La case deux est juste à coté (X + d)
	v_solution.push_back(sf::Vector2f(X_init + 2*d,Y_init)); // ... etc
	v_solution.push_back(sf::Vector2f(X_init,Y_init + d));
	v_solution.push_back(sf::Vector2f(X_init + d,Y_init + d));
	v_solution.push_back(sf::Vector2f(X_init + 2*d,Y_init + d));
	v_solution.push_back(sf::Vector2f(X_init,Y_init + 2*d));
	v_solution.push_back(sf::Vector2f(X_init + d,Y_init + 2*d));
}

void Taquin :: play() { // Echange les coordonées de la case cliquée et de la case vide

	int temp;

	temp = v_position[number].x; 
	v_position[number].x = case_vide.x;
	case_vide.x = temp;

	temp = v_position[number].y; 
	v_position[number].y = case_vide.y;
	case_vide.y = temp;
}