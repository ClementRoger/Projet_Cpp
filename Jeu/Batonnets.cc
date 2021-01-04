#include "Batonnets.hh"
#include <cstdlib>
#include <iostream>
#include <unistd.h>
#include <ctime>

using namespace std;

Batonnets :: Batonnets(const size_t NB_BATONNETS, const size_t dif) : MiniJeu(dif,false) {

	nb_batonnets = NB_BATONNETS;
	tour = true;

	if(dif == 1) {//Easy
		difficulty = true;
	}	
	else {
		difficulty = false;
	}
}

void Batonnets :: play() {
	
	if(!tour) {

		tour = IA_plays();
	}

	else {

		tour = user_plays();			
	}			
}

int Batonnets :: generer_nb_aleatoire(const int min, const int max)const {

    std::srand(std::time(nullptr)); //Initialise le générateur de nombres aléatoires

    return rand()%(max - min + 1) + min;
}

void Batonnets :: print() const{ //Utilisée pour le test dans le terminal

	for (size_t i = 0; i < nb_batonnets; ++i) {
		
		cout << "| ";
	}

	cout << endl;
}

bool Batonnets :: IA_plays() {

	int IA_number;

	if (nb_batonnets == 1){

		IA_number = 1;
		set_win(true); //Il ne reste qu'un bâtonnet, l'IA est obligée de le prendre, elle a perdu
	}

	else if(nb_batonnets <= 4) { // l'IA peut gagner

		IA_number = nb_batonnets - 1; //Le joueur sera obligé de prendre le dernier bâtonnet
	}

	else{

		if(difficulty){

			IA_number = generer_nb_aleatoire(1,3); //Sinon on prend au hasard un nombre entre 1 et 3 (la difficulté est moyenne)
		}

		else {

			if(generer_nb_aleatoire(1,2) == 1){ //Une chance sur deux

				IA_number = 4 - last_move; // L'IA prend 4 - nombre de batonnets pris par l'utilisateur (technique infaillibe pour gagner)
			}

			else {

				IA_number = generer_nb_aleatoire(1,3);
			}
		}
	}

	if(! win()){

		nb_batonnets -= IA_number; // L'adversaire s'empare des bâtonnets
		last_move = IA_number;
		//cout << "\nL'adversaire a pris " << IA_number << " bâtonnet(s)" << endl;
		//print(); // Affiche les bâtonnets restants

		return true;
	}

	return false;
}

bool Batonnets :: user_plays() {

	double number;

	if(nb_batonnets == 1) { ///Il ne reste qu'un bâtonnet, le joueur est obligé de le prendre, il a perdu

		nb_batonnets--;
		//cout << "Vous avez pris le dernier bâtonnet." << endl;
		return true;
	}

	else{

		number = stoi(user_entry, nullptr, 10);;
		nb_batonnets -= number;
		last_move = number;
		return false;
	}
}
