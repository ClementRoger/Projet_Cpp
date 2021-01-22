#define CATCH_CONFIG_MAIN

#include <iostream>
#include <fstream>

#include "Taquin.hh"
#include "catch.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

using namespace std;

#define NBTRY 150
#define APP_SIZE_X 800
#define APP_SIZE_Y 600

#define X_centre 300 
#define Y_centre 200 // (300,200) est le centre de la case en haut à gauche (case 1)

#define X_init 250 
#define Y_init 150 // (250,150) est le coin haut supérieur de la case en haut à gauche (case 1)

#define d 100 // ecart entre deux cases adjacentes


sf::RenderWindow window(sf::VideoMode(APP_SIZE_X, APP_SIZE_Y), "Epreuve du Taquin");
char grille[9] = "12346875"; 

// La grille de départ est :
// 123
// 468
// 75

Taquin T1(NBTRY,grille);

TEST_CASE("1 : Test de la position des images") {

	REQUIRE( T1.get_image_number(X_centre, Y_centre) == 0); //get_image_number retourne un numéro d'image entre 0 et 7 (car utilisé pour un indice de vecteur). La case en haut à gauche est l'image 1 donc renvoie 0
	REQUIRE( T1.get_image_number(X_centre + d, Y_centre) == 1); //L'image à sa droite est un 2
	REQUIRE( T1.get_image_number(X_centre + 2*d, Y_centre) == 2); // etc
	REQUIRE( T1.get_image_number(X_centre, Y_centre + d) == 3);
	REQUIRE( T1.get_image_number(X_centre + d, Y_centre + d) == 5);
	REQUIRE( T1.get_image_number(X_centre + 2*d, Y_centre + d) == 7);
	REQUIRE( T1.get_image_number(X_centre, Y_centre + 2*d) == 6);
	REQUIRE( T1.get_image_number(X_centre + d, Y_centre + 2*d) == 4);
	REQUIRE( T1.get_case_vide().x == X_init + 2*d );
	REQUIRE( T1.get_case_vide().y == Y_init + 2*d );
}	

TEST_CASE("2 : Test de la possibilité de déplacement d'une case") { //Seules les cases 5 et 8 (donc numéros 4 et 7) peuvent être déplacées, les autres sont bloquées

	REQUIRE(T1.check_move(0) == false); //Case 1
	REQUIRE(T1.check_move(1) == false);
	REQUIRE(T1.check_move(2) == false);
	REQUIRE(T1.check_move(3) == false);
	REQUIRE(T1.check_move(4) == true);
	REQUIRE(T1.check_move(5) == false);
	REQUIRE(T1.check_move(6) == false);
	REQUIRE(T1.check_move(7) == true);
}
	
TEST_CASE("3 : Test du déplacement de la case") { //On bouge la case 8, on peut maintenant déplacer la case 6 mais plus la 5

	REQUIRE( T1.get_nb_try() == NBTRY); //Nombre de tentatives restantes

	T1.set_image_number(7); 
	T1.play(); // On bouge la case 8

	REQUIRE( T1.get_nb_try() == NBTRY - 1);
	REQUIRE( T1.check_move(5) == true); //Case 6
	REQUIRE( T1.check_move(4) == false);
	REQUIRE( T1.check_move(7) == true);
	REQUIRE( T1.get_case_vide().x == X_init + 2*d );
	REQUIRE( T1.get_case_vide().y == Y_init + d );

	T1.set_image_number(5);
	T1.play(); // On bouge la case 6

	REQUIRE( T1.get_nb_try() == NBTRY - 2);
	REQUIRE( T1.check_move(1) == true);
	REQUIRE( T1.check_move(3) == true);
	REQUIRE( T1.check_move(5) == true);
	REQUIRE( T1.check_move(4) == true);
	REQUIRE( T1.get_case_vide().x == X_init + d );
	REQUIRE( T1.get_case_vide().y == Y_init + d ); //case du milieu		
}	

TEST_CASE("4 : Test de victoire") {

	REQUIRE(T1.win() == false);

	T1.set_image_number(4); // On bouge la case 5
	T1.play(); 
	REQUIRE( T1.get_nb_try() == NBTRY - 3);

	T1.set_image_number(7); // On bouge la case 8, le taquin est résolu
	T1.play(); 
	REQUIRE( T1.get_nb_try() == NBTRY - 4);

	REQUIRE(T1.win() == true);
}	