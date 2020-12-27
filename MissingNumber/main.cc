
#include <iostream>
#include <string>
#include<fstream>
 
using namespace std;

#include "missingnumber.hh"
 
   
int main()
{   
  
fstream inFile("matrices.txt", fstream::in);
Missingnumber game(inFile,3); 
game.display();
 
  return 0;
} 