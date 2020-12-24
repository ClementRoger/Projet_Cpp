#include "Juste_Prix.hh"
#include <cstdlib>
#include <iostream>
#include <ctime>

using namespace std;

Juste_Prix :: Juste_Prix(size_t NB_TENTATIVES, int NMIN, int NMAX):MiniJeu(NB_TENTATIVES,false) {

	Nmin = NMIN;
	Nmax = NMAX;
	std::srand(std::time(nullptr)); //Initialise le générateur de nombres aléatoires
	mystery_number = rand()%Nmax + Nmin; //Nombre aléatoire entre Nmin et Nmax

}

void Juste_Prix :: play() {

	cout << "Vous avez " << get_nb_try() << " tentatives pour trouver un nombre aléatoire entre " << Nmin << " et " << Nmax << endl << endl;
	double number;
	bool flag = true; //Sert à savoir si on décrémente le nombre de tentatives

	while ( !win() && get_nb_try() > 0) { // Tant que le joueur n'a pas gagné et qu'il reste des tentatives

		cout << "Veuillez entrer un nombre entre " << Nmin << " et " << Nmax << endl;
		cin >> number; 

		if(!(cin.fail()) ){ // Si l'entrée est un double

			flag = check_entry(number);
		}

		else {

			cin.clear();
			cin.ignore();
			flag = false;
			cout << "Erreur ! Veuillez entrer un nombre entier entre 1 et 100 ..." << endl;
			
		}

		if(flag){

			set_nb_try(get_nb_try()-1);
			cout << "Il vous reste " << get_nb_try() << " tentatives !" << endl << endl;
		}
	}
}



bool Juste_Prix :: check_entry(double number) {

	int int_number = (int) number;

	if(number != int_number){ //L'utilisateur a entré un nombre non entier

		cout << "Erreur ! Veuillez entrer un entier !" << endl;
		return false;
	}

	else if( (number < Nmin) || (number > Nmax) ){ //L'utilisateur a entré un nombre non compris entre Nmin et Nmax

		cout << "Erreur ! Veuillez entrer un nombre entier entre " << Nmin << " et " << Nmax << " ..." << endl;
		return false;
	}

	else if((size_t)number > mystery_number) {

		cout << "C'est moins !" << endl;
		return true;
	}

	else if ((size_t)number < mystery_number) {

		cout << "C'est plus !" << endl;
		return true;
	}

	else{

		set_win(true);
		return false;
	}
}

void Juste_Prix :: transition(){

}

/*
bool Juste_Prix :: win() {

	return victory;
}*/