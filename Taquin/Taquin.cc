#include "Taquin.hh"
#include <cstdlib>
#include <iostream>
#include <unistd.h>
#include <ctime>

using namespace std;

#define X_init 200
#define Y_init 200
#define d 50

Taquin :: Taquin(size_t NB_TRY) : MiniJeu(NB_TRY,false) {

	nb_try = NB_TRY;

	init_position();
	init_names();
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

void Taquin :: play() {

}