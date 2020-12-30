#include <iostream>
#include <fstream>
#include "Batonnets.hh"

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

using namespace std;

#define NB_BATONNETS 20

int main() {

	sf::RenderWindow window(sf::VideoMode(APP_SIZE_X, APP_SIZE_Y), "Epreuve des Bâtonnets");
	Batonnets B1(NB_BATONNETS,2); //1 easy, 2 difficult
	B1.display(window);

	return EXIT_SUCCESS;
}