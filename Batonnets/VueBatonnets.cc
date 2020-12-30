#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include <vector>
#include <stdexcept>  // std::invalid_argument

#include "Batonnets.hh"
#include "TextEntry.hh"

using namespace std;
 
void Batonnets :: display(sf::RenderWindow& window){

	window.clear();
	init_background(window);
	affiche_batonnets(window);
	TextEntry textbar(window,APP_SIZE_X,APP_SIZE_Y + 220);
	window.display();

	while (window.isOpen() && !win() && nb_batonnets > 0) {

		sf::Event event;

        while (window.pollEvent(event)) {

            textbar.check_events(window,event);

            if (event.type == sf::Event::Closed){ 
                window.close();
                break;                
            }

        }

        user_entry = textbar.get_finalInput();

		if(tour) {
			if(check_entry(user_entry)){

				play();
			}
		}

		else {

			play();
			sf::Time delay = sf::milliseconds(1600);
			sf::sleep(delay);
		}	
			
		window.clear();
        init_background(window);
        affiche_batonnets(window);
        textbar.display(window);
        window.display();
	}

}

bool Batonnets :: check_entry(string entry) {

	int number;

	try {

		number = stoi(entry, nullptr, 10); //Convertir le string entry en entier (base 10). Si la conversion échoue, soulève une exception invalid argument
	}

	catch (const std::invalid_argument& ia) {

		return false;
	}	


	if(number >= 1 && number <= 3) { //On ne peut prendre que 1, 2 ou 3 bâtonnets

		return true;
	}

	return false;
}

void Batonnets :: init_background(sf::RenderWindow& window) {

    sf::Texture texture;
    sf::Sprite sprite;
    texture.loadFromFile("images/background.jpg");
    sprite.setTexture(texture);
    window.draw(sprite);

    texture.loadFromFile("images/tiger.png"); 
    sprite.setTexture(texture);
    sprite.setPosition(sf::Vector2f(10,20));
    sprite.setScale(0.35,0.35);
    window.draw(sprite);
 
    sf::Font font;
    font.loadFromFile("images/arial.ttf");
    sf::Text text;
    text.setFont(font);
    text.setString("Test \n 3/6");
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::White);
    text.setStyle(sf::Text::Bold);
    text.setPosition(sf::Vector2f(32,43));
    window.draw(text);

    font.loadFromFile("images/lakeshore.ttf");
    text.setFont(font);
    text.setString("Epreuve des Batonnets");
    text.setCharacterSize(65);
    text.setFillColor(sf::Color::Black);
    text.setStyle(sf::Text::Bold);
    text.setPosition(sf::Vector2f(APP_SIZE_X/4,25));
    window.draw(text);

    string str;

    if(tour) {

    	str = "A vous de jouer";
    }

    else {

    	str = "Au tour d'Eddy de jouer";	
    }

    font.loadFromFile("images/Trouble.otf");

	text.setFont(font);
    text.setString(str);
    text.setCharacterSize(37);
    text.setFillColor(sf::Color(0,0,139));
    text.setStyle(sf::Text::Bold);
    text.setPosition(sf::Vector2f(400 - text.getLocalBounds().width/2,155));
    window.draw(text);    

    text.setFont(font);
    text.setString("Press Enter to submit");
    text.setCharacterSize(25);
    text.setFillColor(sf::Color(0,0,0));
    text.setStyle(sf::Text::Bold);
    text.setPosition(sf::Vector2f(400 - text.getLocalBounds().width/2,430));
    window.draw(text);

    texture.loadFromFile("images/paint.png");
    texture.setSmooth(true);
    sprite.setTexture(texture);
    sprite.setScale(1.3,0.9);
    sprite.setPosition(sf::Vector2f(APP_SIZE_X/4 - 47,480));
    window.draw(sprite);

    font.loadFromFile("images/arial.ttf");
    text.setString("Batonnets restants : " + std::to_string(nb_batonnets));
    text.setCharacterSize(30);
    text.setFillColor(sf::Color::White);
    text.setStyle(sf::Text::Bold);
    text.setPosition(sf::Vector2f(APP_SIZE_X/3-30,510));
    window.draw(text);

}

void Batonnets :: affiche_batonnets(sf::RenderWindow& window) {

	sf::Texture texture;
    sf::Sprite sprite;
    texture.loadFromFile("images/metal.jpeg");
    sprite.setTexture(texture);
    sprite.setPosition(30, 220);
    sprite.setScale(1.04,0.3);
    window.draw(sprite);

	for (int i = 0; i < nb_batonnets; ++i) {

		sf::Texture texture;
    	sf::Sprite sprite;
		
		if (!texture.loadFromFile("images/batonnet.png")){

			cout << "Erreur lors du chargement de l'image" << endl;
		}	

		sprite.setTexture(texture);
		sprite.setPosition(700 * i /19, 233);
		sprite.setScale(0.2,0.2);
		window.draw(sprite);
	}
}