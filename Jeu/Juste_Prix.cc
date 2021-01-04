#include "Juste_Prix.hh"
#include <cstdlib>
#include <iostream>
#include <ctime>
#include <string.h>

using namespace std;

Juste_Prix :: Juste_Prix(const size_t NB_TENTATIVES, const int NMIN, const int NMAX) : MiniJeuAvecSolution(NB_TENTATIVES,false) {

	Nmin = NMIN;
	Nmax = NMAX;
	std::srand(std::time(nullptr)); //Initialise le générateur de nombres aléatoires
	set_solution(std::to_string(rand()%Nmax + Nmin)); //Nombre aléatoire entre Nmin et Nmax
	cout << get_solution() << endl;

}

void Juste_Prix :: play() {

	size_t number = (size_t) stoi(get_user_entry(), nullptr, 10);
	size_t solution = (size_t) stoi(get_solution(), nullptr, 10);

	if(number > solution) {

		result = "C'est moins";
	}

	else if(number < solution){

		result = "C'est plus";
	}

	else {
		set_win(true);
		result = L"C'est gagné";
	}

	set_nb_try(get_nb_try() - 1);
}

