
#include <iostream>
#include <string>
#include<fstream>
 
using namespace std;
   
#include "pendu.hh"
 
   
int main()
{   
 
fstream inFile("mots_difficiles.txt", fstream::in);
Pendu game(inFile,10); 
game.display();
 
  return 0;
} 