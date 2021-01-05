
#include <iostream>
#include <string>
#include<fstream>
#include <SFML/Graphics.hpp>
 
using namespace std;

#include "missingnumber.hh"
 
   
int main()
{   
	sf::RenderWindow window(sf::VideoMode(APP_SIZE_X2, APP_SIZE_Y2), "Epreuve du Nombre Manquant");
	fstream inFile("img_missing/matrices.txt", fstream::in);
	Missingnumber game(inFile,3); 
	game.display(window);
 
  return 0;
} 