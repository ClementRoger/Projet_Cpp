#include "Taquin.hh"
#include <cstdlib>
#include <iostream>
#include <unistd.h>
#include <ctime>

using namespace std;

#define X_init 250 //X de la case en haut à gauche
#define Y_init 150 // Y de la case en haut à gauche
#define d 100 // ecart entre deux cases adjacentes

Taquin :: Taquin(const size_t NB_TRY) : MiniJeu(NB_TRY,false) {

	read_file();
	init_names();
	init_case_vide();
	init_solution();
}

void Taquin :: init_names() {

	v_name.push_back("images_taquin/1.png");
	v_name.push_back("images_taquin/2.png");
	v_name.push_back("images_taquin/3.png");
	v_name.push_back("images_taquin/4.png");
	v_name.push_back("images_taquin/5.png");
	v_name.push_back("images_taquin/6.png");
	v_name.push_back("images_taquin/7.png");
	v_name.push_back("images_taquin/8.png");
}

void Taquin :: read_file() { 
	
	ifstream file( "grilles.txt" ); 
  
    string line; 

    int cpt = 1;

    srand((unsigned)time(0)); 
    int numero_grille = (rand()%7); //Entre 1 et 6
   	int numero_ligne = 9*numero_grille + 1; //8 chiffres + un saut de lignes = 9, le +1 car le fichier commence ligne 1 et non 0
   	std::vector<int> v; 

    if ( file ) {

        std::string line;
  
        while ( getline( file, line ) )  { 

        	if(cpt >= numero_ligne && cpt <= numero_ligne + 7){
             
             	int number = stoi(line, nullptr, 10);
             	v.push_back(number);
        	}

        	cpt++;
        }

        init_position(v); 
    } 
}

void Taquin :: init_position(std::vector<int> v){

	int number = 1;

	/*for (int i = 0; i < 8; ++i){

		cout << v[i];

		if(i == 2 || i == 5) {

			cout << endl;
		}
	}*/

	cout << endl;

	while(v_position.size() != 8) {

		for (int i = 0; i < 8; ++i) {
		
			if(v[i] == number){

				switch(i) {

					case 0 :

						v_position.push_back(sf::Vector2f(X_init,Y_init)); // 0 => en haut à gauche => (X_INIT,Y_INIT)
						break;

					case 1 :

						v_position.push_back(sf::Vector2f(X_init + d,Y_init)); // 1 => deuxième case, à droite du 0 => (X_INIT + d, Y_INIT) 
						break;

					case 2 :

						v_position.push_back(sf::Vector2f(X_init + 2*d,Y_init)); //etc
						break;

					case 3 :	

						v_position.push_back(sf::Vector2f(X_init,Y_init + d));
						break;

					case 4 :
						
						v_position.push_back(sf::Vector2f(X_init + d,Y_init + d));
						break;

					case 5 :	

						v_position.push_back(sf::Vector2f(X_init + 2*d,Y_init + d));
						break;
					
					case 6 :

						v_position.push_back(sf::Vector2f(X_init,Y_init + 2*d));
						break;

					case 7 :

						v_position.push_back(sf::Vector2f(X_init + d,Y_init + 2*d));
						break;				
					}	

				number++;
			}
		}	
	}
}

void Taquin :: init_case_vide() { // Initialement la case vide est la case tout en bas à droite

	case_vide.x = X_init + 2 * d;
	case_vide.y = Y_init + 2 * d;
}

void Taquin :: init_solution() { 

	v_solution.push_back(sf::Vector2f(X_init,Y_init)); // La case 1 est tout en haut à gauche dans la solution
	v_solution.push_back(sf::Vector2f(X_init + d,Y_init)); //La case deux est juste à coté (X + d)
	v_solution.push_back(sf::Vector2f(X_init + 2*d,Y_init)); // ... etc
	v_solution.push_back(sf::Vector2f(X_init,Y_init + d));
	v_solution.push_back(sf::Vector2f(X_init + d,Y_init + d));
	v_solution.push_back(sf::Vector2f(X_init + 2*d,Y_init + d));
	v_solution.push_back(sf::Vector2f(X_init,Y_init + 2*d));
	v_solution.push_back(sf::Vector2f(X_init + d,Y_init + 2*d));
}

void Taquin :: play() { // Echange les coordonées de la case cliquée et de la case vide

	int temp;

	temp = v_position[number].x; 
	v_position[number].x = case_vide.x;
	case_vide.x = temp;

	temp = v_position[number].y; 
	v_position[number].y = case_vide.y;
	case_vide.y = temp;
}