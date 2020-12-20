#include <iostream>
#include <fstream>
#include "Batonnets.hh"

using namespace std;

int main() {

	Batonnets B1;

	if(B1.check_victory()){

		cout << "\nFélicitations ! Vous avez gagné !" << endl;
	}

	else{

		cout << "\nDésolé. Vous avez perdu !" << endl;
	}
}