
#include <iostream>
#include <string>
#include<fstream>
 

#include "Demineur.hh"
 
   
int main()
{   
 
//fstream inFile("matrices.txt", fstream::in);
Demineur game(2,8,8); 
game.display();
 
  return 0;
} 