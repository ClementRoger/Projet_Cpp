#include "Juste_Prix.hh"
#include <cstdlib>
#include <iostream>

#define Nmin 1
#define Nmax 100
#define NB_TENTATIVES 7

using namespace std;

Juste_Prix :: Juste_Prix() {

	mystery_number = rand()%Nmax + Nmin; //Nombre aléatoire entre 1 et 100
	nb_tentatives = NB_TENTATIVES;
	play();

}

void Juste_Prix :: play() {

	cout << "Vous avez " << nb_tentatives << " tentatives pour trouver un nombre aléatoire entre " << Nmin << " et " << Nmax << endl << endl;
	victory = false;
	int number;
	bool flag = true; //Sert à savoir si on décrémente le nombre de tenttives

	while ( !victory && nb_tentatives > 0) { // Tant que le joueur n'a pas gagné et qu'il reste des tentatives

		cin >> number;

		if(!(cin.fail()) ){ // Si l'entrée est un int

			if(number < 1) {

				cout << "Erreur ! Veuillez entrer un nombre entier entre 1 et 100 ..." << endl;
				flag = false;
			}

			else if((size_t)number > mystery_number) {

				cout << "C'est moins !" << endl;
				flag = true;
			}

			else if ((size_t)number < mystery_number) {

				cout << "C'est plus !" << endl;
				flag = true;
			}

			else{

				cout << "Gagné !" << endl;
				victory = true;
				flag = false;
			}
		}

		else {

			cin.clear();
			cin.ignore();
			flag = false;
			cout << "Erreur ! Veuillez entrer un nombre entier entre 1 et 100 ..." << endl;
			
		}

		if(flag){

			nb_tentatives--;
			cout << "Il vous reste " << nb_tentatives << " tentatives !" << endl;
		}
	}
}

bool Juste_Prix :: check_victory() {

	return victory;
}