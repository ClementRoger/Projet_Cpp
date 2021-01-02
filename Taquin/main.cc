#include <iostream>
#include <fstream>
#include "Taquin.hh"

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

using namespace std;

#define FACILE 150
#define DIFFICILE 1

int main() {

	sf::RenderWindow window(sf::VideoMode(APP_SIZE_X, APP_SIZE_Y), "Epreuve du Taquin");
	Taquin T1(DIFFICILE);
	T1.display(window);

	return EXIT_SUCCESS;
}