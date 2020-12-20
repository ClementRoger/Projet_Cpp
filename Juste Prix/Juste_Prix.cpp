#include "Juste_Prix.hh"
#include <cstdlib>
#include <iostream>

#define Nmin 1
#define Nmax 100
#define NB_TENTATIVES 8

using namespace std;

Juste_Prix :: Juste_Prix() {

	mystery_number = rand()%Nmax + Nmin; //Nombre aléatoire entre 1 et 100
	nb_tentatives = NB_TENTATIVES;
	play();

}

void Juste_Prix :: play() {

	cout << "Vous avez " << nb_tentatives << " tentatives pour trouver un nombre aléatoire entre " << Nmin << " et " << Nmax << endl << endl;
	victory = false;
	double number;
	bool flag = true; //Sert à savoir si on décrémente le nombre de tenttives

	while ( !victory && nb_tentatives > 0) { // Tant que le joueur n'a pas gagné et qu'il reste des tentatives

		cout << "Veuillez entrer un nombre entre " << Nmin << " et " << Nmax << endl;
		cin >> number;
		int int_number = (int)number; 

		if(!(cin.fail()) ){ // Si l'entrée est un double

			if(number != int_number){ //L'utilisateur a entré un nombre non entier

				cout << "Erreur ! Veuillez entrer un entier !" << endl;
				flag = false;
			}

			else if( (number < 1) || (number > 100) ){ //L'utilisateur a entré un nombre non compris entre 1 et 100

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
			cout << "Il vous reste " << nb_tentatives << " tentatives !" << endl << endl;
		}
	}
}

bool Juste_Prix :: check_victory() {

	return victory;
}