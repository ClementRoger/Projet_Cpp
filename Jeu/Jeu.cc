#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <iostream>

#include "Jeu.hh"

using namespace std;

Jeu :: Jeu() {

	while(window.isOpen()) {

		sf::Event event;
        while (window.pollEvent(event)) {

            if (event.type == event.Closed) {
            	window.close();
            }
        }

        window.clear();
        init_game();
		window.display();
	}
}

void Jeu :: init_game() {

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

	create_button(Bouton_Facile, Texte_Facile, 100, 430);
	create_button(Bouton_Difficile, Texte_Difficile, 450, 430);

	sf::Text Texte_Titre("Livin' Tomorrow",font,50);
	Texte_Titre.setCharacterSize(55);
    Texte_Titre.setFillColor(sf::Color(0, 0, 139)); // Du bleu foncé stylé
    Texte_Titre.setStyle(sf::Text::Bold);
    Texte_Titre.setPosition(160, 30);

    window.draw(Texte_Titre);

}

void Jeu :: create_button(sf::Sprite Bouton, sf::Text text, size_t x, size_t y) {

	sf::Texture texture;
	
	if (!texture.loadFromFile("button.png")){ //NOTE A MOI MEME : PNG >>>>>>>>>>> JPEG. JPEG EST LE DIABLE ET CAUSE DES BUGS DE MEEEEEEEEEEEEEEEEEERDE

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