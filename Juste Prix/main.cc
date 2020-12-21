#include <iostream>
#include <fstream>
#include "Juste_Prix.hh"

#define NB_TENTATIVES 7
#define Nmin 1
#define Nmax 100

using namespace std;

int main() {

	Juste_Prix J1(NB_TENTATIVES, Nmin, Nmax);
	J1.play();

	if(J1.check_victory()){

		cout << "\nFélicitations ! Vous avez gagné !" << endl;
	}

	else{

		cout << "\nDésolé. Vous avez perdu !" << endl;
	}
}