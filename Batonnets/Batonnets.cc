#include "Batonnets.hh"
#include <cstdlib>
#include <iostream>
#include <unistd.h>
#include <ctime>

using namespace std;

Batonnets :: Batonnets(int NB_BATONNETS) {

	nb_batonnets = NB_BATONNETS;
	std::srand(std::time(nullptr)); //Initialise le générateur de nombres aléatoires
}

void Batonnets :: play() {

	victory = false;
	bool tour = true; // A l'IA de jouer si tour == false, sinon au tour du joueur. Le joueur commence

	cout << "Au début il y a 20 bâtonnets" << endl;
	print();
	cout << "Vous ne pouvez prendre que 1, 2 ou 3 bâtonnets. Le joueur qui s'empare du dernier a perdu. Bonne chance !" << endl << endl;
	
	while ( !victory && nb_batonnets > 0) { // Tant qu'un joueur n'a pas gagné et qu'il reste des batonnets

		if(!tour) {

			tour = IA_plays();
		}

		else {

			tour = user_plays();			
		}
	}			
}

bool Batonnets :: check_victory() {

	return victory;
}

void Batonnets :: print() {

	for (size_t i = 0; i < nb_batonnets; ++i) {
		
		cout << "| ";
	}

	cout << endl;
}

bool Batonnets :: IA_plays() {

	int IA_number;

	if (nb_batonnets == 1){

		IA_number = 1;
		victory = true; //Il ne reste qu'un bâtonnet, l'IA est obligée de le prendre, elle a perdu
		cout << "\nL'adversaire a pris le dernier bâtonnet." << endl;
	}

	else if(nb_batonnets <= 4) { // l'IA peut gagner

		IA_number = nb_batonnets - 1; //Le joueur sera obligé de prendre le dernier bâtonnet
	}

	else{

		IA_number = rand()%3 + 1; //Sinon on prend au hasard un nombre entre 1 et 3 (la difficulté est moyenne)
	}

	if(!victory){

		nb_batonnets -= IA_number; // L'adversaire s'empare des bâtonnets
		sleep(1);
		cout << "\nL'adversaire a pris " << IA_number << " bâtonnet(s)" << endl;
		print(); // Affiche les bâtonnets restants

		return true;
	}

	return false;
}

bool Batonnets :: user_plays() {

	double number;

	if(nb_batonnets == 1) { ///Il ne reste qu'un bâtonnet, le joueur est obligé de le prendre, il a perdu

		nb_batonnets--;
		cout << "Vous avez pris le dernier bâtonnet." << endl;
		return true;
	}

	else{

		cout << "\nIndiquez le nombre de bâtonnets que vous souhaitez prendre : ";
		cin >> number;
		int int_number = (int)number;

		if(!(cin.fail()) ){ // Si l'entrée est un int

			if(number != int_number){
	
				cout << "Erreur ! Veuillez entrer un entier !" << endl;
				return true;

			}
					
			else if( (number >= 1) && (number <= 3) ){ //On ne peut sélectionner que 1, 2 ou 3 bâtonnets

				nb_batonnets -= number;
				print(); // Affiche les bâtonnets restants
				return false;
			}
			
			else{

				cout << "Erreur ! Vous ne pouvez prendre que 1, 2 ou 3 bâtonnets !" << endl;
				return true;
			}
		}

		else {

			cout << "Erreur ! Veuillez entrer un entier entre 1 et 3 ..." << endl;
			cin.clear();
			cin.ignore();
			return true;
		}
	}
}