#include <iostream>
#include <fstream>
#include "Batonnets.hh"

using namespace std;

#define NB_BATONNETS 20

int main() {

	Batonnets B1(NB_BATONNETS);
	B1.play();

	if(B1.check_victory()){

		cout << "\nFélicitations ! Vous avez gagné !" << endl;
	}

	else{

		cout << "\nDésolé. Vous avez perdu !" << endl;
	}
}