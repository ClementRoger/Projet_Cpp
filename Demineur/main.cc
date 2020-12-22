
#include <iostream>
#include <string>
#include<fstream>
 
using namespace std;

#include "Demineur.hh"
 
   
int main()
{   
 
//fstream inFile("matrices.txt", fstream::in);
Demineur game(2,8,8); 
game.play();
 
  return 0;
} 