#include "Juste_Prix.hh"
#include <cstdlib>
#include <iostream>
#include <ctime>
#include <string.h>

using namespace std;

Juste_Prix :: Juste_Prix(size_t NB_TENTATIVES, int NMIN, int NMAX) : MiniJeu(NB_TENTATIVES,false) {

	Nmin = NMIN;
	Nmax = NMAX;
	std::srand(std::time(nullptr)); //Initialise le générateur de nombres aléatoires
	mystery_number = rand()%Nmax + Nmin; //Nombre aléatoire entre Nmin et Nmax
	//cout << mystery_number << endl;

}

void Juste_Prix :: play() {

	size_t number = (size_t) stoi(user_entry, nullptr, 10);

	if(number > mystery_number) {

		result = "C'est moins";
	}

	else if(number < mystery_number){

		result = "C'est plus";
	}

	else {
		set_win(true);
		result = L"C'est gagné";
	}

	set_nb_try(get_nb_try() - 1);
}

void Juste_Prix::transition(sf::RenderWindow &window){

}
