
#include <iostream>
#include <string>
#include<fstream>
 

#include "Demineur.hh"
    
int main()
{   
 sf::RenderWindow window(sf::VideoMode(APP_SIZE_X, APP_SIZE_Y), "Demineur de la mort qui tue");
Demineur game(2,10,8); 
game.display(window);
 
  return 0;
} 