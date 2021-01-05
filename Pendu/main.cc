
#include <iostream>
#include <string>
#include<fstream>
#include <SFML/Graphics.hpp>
 
using namespace std;
   
#include "pendu.hh"
 
   
int main()
{   
sf::RenderWindow window(sf::VideoMode(APP_SIZE_X1, APP_SIZE_Y1), "Epreuve du Pendu");
fstream inFile("img_pendu/mots_difficiles.txt", fstream::in);
Pendu game(inFile,8); 
game.display(window);
 
  return 0;
} 