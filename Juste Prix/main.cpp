#include <iostream>
#include <fstream>
#include "Juste_Prix.hh"

using namespace std;

int main() {

	Juste_Prix J1;

	if(J1.check_victory()){

		cout << "\nFélicitations ! Vous avez gagné !" << endl;
	}

	else{

		cout << "\nDésolé. Vous avez perdu !" << endl;
	}
}