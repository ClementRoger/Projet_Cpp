#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <iostream>
 
#include "Jeu.hh"
#include "Demineur.hh"
#include "pendu.hh"
#include "missingnumber.hh"

using namespace std;

Jeu :: Jeu() {
	// 1 = facile ~ 2 = difficile ~ 0 = indéfini
	_difficulty = 0;
	_passedGames = 0;
}

void Jeu :: run(){
	sf::RenderWindow window(sf::VideoMode(XWINDOW, YWINDOW), "Projet C++");

	std::size_t cpt = 0; // nombre de jeux avec 0 l'intro
	bool Intropassed = false;
	while(window.isOpen()) {

		sf::Event event;
	    while (window.pollEvent(event)) {

	        if (event.type == event.Closed) {
	        	window.close();
	        	break;
	        }
		    if (!cpt){
		        if (event.type == sf::Event::MouseButtonPressed){
		        	Intropassed = Get_Mouse_Click(window);
		        	break;
		        }
		    }
	    }
	     // Si un niveau : facile ou difficile sélectionné on incrémente cpt pour passer aux minijeux
	    if(Intropassed && !cpt){
	    	cpt ++;
	    }
	    // Si niveau facile
	    if (get_difficulty() == 1){
	    	easy_game(window,cpt);
	    }
	    else if (get_difficulty() == 2){
	    	difficult_game(window,cpt);
	    }
	    
	    
	    if (!cpt){
	    	window.clear();
	    	init_game(window);
			window.display();
	    }
	    
	}
}

void Jeu::easy_game(sf::RenderWindow &window,std::size_t& cpt){
	switch (cpt){
		case 1 : {
			std::fstream inFile("img_pendu/mots_faciles.txt", std::fstream::in);
			Pendu game(inFile,8); 
    		game.display(window);
	    	check_end(game,window,cpt);
			break;
		}

		case 2 : {
			std::fstream inFile("img_missing/matrices.txt", std::fstream::in);
			Missingnumber game(inFile,3); 
			game.display(window);
			check_end(game,window,cpt);
			break;
		}

		case 3 : {
			Demineur game(2,8,8); 
    		game.display(window);
    		check_end(game,window,cpt);
			break;
		}
		
		default :
			std::cout<<"end"<<std::endl;
			break;
	}
}

void Jeu::difficult_game(sf::RenderWindow &window,std::size_t& cpt){
    switch (cpt){
		case 1 : {
			std::fstream inFile("img_pendu/mots_difficiles.txt", std::fstream::in);
			Pendu game(inFile,8); 
    		game.display(window);
	    	check_end(game,window,cpt);
			break;
		}

		case 2 : {
			std::fstream inFile("img_missing/matrices.txt", std::fstream::in);
			Missingnumber game(inFile,1); 
			game.display(window);
			check_end(game,window,cpt);
			break;
		}

		case 3 : {
			Demineur game(1,10,8); 
    		game.display(window);
    		check_end(game,window,cpt);
			break;
		}
		
		default :
			std::cout<<"end"<<std::endl;
			break;
	}
}

void Jeu::check_end(MiniJeu& game,sf::RenderWindow &window,std::size_t& cpt){
	if(game.win()){
		cpt++;
	}
	else {
		window.close();
	}
}

/* Permet de determiner la position de la souris lors du click + de savoir si ce click est dans la grille de jeu */
bool Jeu::Get_Mouse_Click(sf::RenderWindow &window){
	sf::Vector2i position;
    static bool pressed=false;
    while (true){
      if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
          if (!pressed){
            position = sf::Mouse::getPosition(window);
            pressed=true;
            break;
          }
      }
      else{
        pressed = false;
      }   
    }
    //std::cout << position.x << " " << position.y << '\n';
    std::size_t tmp = test_button_border(position);
    std::cout<<"tmp :"<<tmp<<std::endl;
    if (tmp > 0){
    	set_difficulty(tmp);
    	return true;
    }
    return false;
}

/* Permet de tester si le click se trouve sur difficile ou facile*/
std::size_t Jeu::test_button_border(const sf::Vector2i position){

    if ( (position.x >= 100)
        && (position.x <= 100 + 960*0.25f)
        && (position.y >= 430)
        && (position.y <= 430 + 480*0.25f )) {
        return 1;
    }

    if ( (position.x >= 450)
        && (position.x <= 450 + 960*0.25f)
        && (position.y >= 430)
        && (position.y <= 430 + 480*0.25f )){

    	return 2;
    }
    
    
    return 0;
}

void Jeu :: init_game(sf::RenderWindow& window) {

	sf::Font font;

	if (!font.loadFromFile("zorque.ttf")) {
        cout << "Erreur de chargement de la police" << endl;
    }

    sf::Sprite Bouton_Facile, Bouton_Difficile;
	sf::Text Texte_Facile("Facile",font,50);
	sf::Text Texte_Difficile("Difficile",font,50);

	sf::Texture bg_texture;
	sf::Sprite bg;
	
	if (!bg_texture.loadFromFile("bg.jpeg")){

    	cout << "Erreur de chargement de l'image de fond" << endl;
	}

	bg.setTexture(bg_texture);
	bg.setScale(1.18,1.48); //Valeur trouvées un peu au pif mdr
	window.draw(bg);

	create_button(window,Bouton_Facile, Texte_Facile, 100, 430);
	create_button(window,Bouton_Difficile, Texte_Difficile, 450, 430);

	sf::Text Texte_Titre("Livin' Tomorrow",font,50);
	Texte_Titre.setCharacterSize(55);
    Texte_Titre.setFillColor(sf::Color(0, 0, 139)); // Du bleu foncé stylé
    Texte_Titre.setStyle(sf::Text::Bold);
    Texte_Titre.setPosition(160, 30);

    window.draw(Texte_Titre);

}

void Jeu :: create_button(sf::RenderWindow& window,sf::Sprite Bouton, sf::Text text, size_t x, size_t y) {

	sf::Texture texture;
	
	if (!texture.loadFromFile("button.png")){ //NOTE A MOI MEME : PNG >>>>>>>>>>> JPEG. JPEG EST LE DIABLE ET CAUSE DES BUGS DE MEEEEEEEEEEEEEEEEEERDE (jsuis grv d'accord jpg ça pu sa daronne)

    	cout << "Erreur de chargement de l'image du bouton" << endl;
	}

	texture.setSmooth(true);
	Bouton.setTexture(texture);
	Bouton.setScale(0.25,0.25);

    text.setCharacterSize(30);
    text.setFillColor(sf::Color(55, 0, 139)); // Du bleu foncé stylé
    text.setStyle(sf::Text::Bold);

    Bouton.setPosition(x,y);
    text.setPosition(x + texture.getSize().x/8 - text.getLocalBounds().width/2, y + texture.getSize().y/8 - text.getLocalBounds().height); //Un peu au pif pour le y (jsp pourquoi y a pas le /2 pour height), le x est logique : le /8 vient de /2 et il faut multiplier par le cofficient de getScale (0.25) donc 1/2 * 1/4 = 1/8

    window.draw(Bouton);
    window.draw(text);
}