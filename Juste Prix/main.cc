#include <iostream>
#include <fstream>
#include "Juste_Prix.hh"

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

#define NB_TENTATIVES 7
#define Nmin 1
#define Nmax 100

using namespace std;

int main() {

	sf::RenderWindow window(sf::VideoMode(APP_SIZE_X, APP_SIZE_Y), "Epreuve du Plus ou Moins");

	Juste_Prix J1(NB_TENTATIVES, Nmin, Nmax);
	J1.display(window);

	return EXIT_SUCCESS;
}
