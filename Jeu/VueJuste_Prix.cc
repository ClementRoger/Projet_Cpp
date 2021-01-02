#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include <vector>
#include <stdexcept>  // std::invalid_argument

#include "Juste_Prix.hh"
#include "TextEntry.hh"

using namespace std;
 
void Juste_Prix :: display(sf::RenderWindow& window){

	window.clear();
	init_background(window);
    string prev;

	TextEntry textbar(window,APP_SIZE_X4,APP_SIZE_Y4 + 50);
	window.display();
	while (window.isOpen() && !win() && get_nb_try() > 0) {

		sf::Event event;

        while (window.pollEvent(event)) {

            textbar.check_events(window,event);

            if (event.type == sf::Event::Closed){ 
                window.close();
                break;                
            }
        }

        prev = get_user_entry();

		if(check_entry(textbar.get_finalInput()) && textbar.get_finalInput() != "" && prev != textbar.get_finalInput()){

            set_user_entry(textbar.get_finalInput());
			play();
		}	
			
		window.clear();
        init_background(window);
        textbar.display(window);
        window.display();
	}
    print_end(win(),window);
}

bool Juste_Prix :: check_entry(string entry) {

	int number;

	try {

		number = stoi(entry, nullptr, 10); //Convertir le string entry en entier (base 10). Si la conversion échoue, soulève une exception invalid argument
	}

	catch (const std::invalid_argument& ia) {

		return false;
	}	


	if(number >= 1 && number <= 100) { //Le nombre est compris entre 1 et 100

		return true;
	}

	return false;
}

void Juste_Prix :: init_background(sf::RenderWindow& window) {

    sf::Texture texture;
    sf::Sprite sprite;
    texture.loadFromFile("images_justep/background.jpg");
    sprite.setTexture(texture);
    window.draw(sprite);

    texture.loadFromFile("images_justep/target.png"); 
    sprite.setTexture(texture);
    sprite.setPosition(sf::Vector2f(-30,-20));
    sprite.setScale(0.35,0.35);
    window.draw(sprite);
 
    sf::Font font;
    font.loadFromFile("images_justep/arial.ttf");
    sf::Text text;
    text.setFont(font);
    text.setString("Test \n 1/6");
    text.setCharacterSize(24);
    text.setFillColor(sf::Color(255,255,153));
    text.setStyle(sf::Text::Bold);
    text.setPosition(sf::Vector2f(32,35));
    window.draw(text);

    font.loadFromFile("images_justep/lakeshore.ttf");
    text.setFont(font);
    text.setString("Epreuve du Plus ou Moins");
    text.setCharacterSize(65);
    text.setFillColor(sf::Color::Black);
    text.setStyle(sf::Text::Bold);
    text.setPosition(sf::Vector2f(APP_SIZE_X4/4-30,25));
    window.draw(text);

    font.loadFromFile("images_justep/arial.ttf");

	text.setFont(font);
    text.setString(result);
    text.setCharacterSize(37);
    text.setFillColor(sf::Color(0,0,139));
    text.setStyle(sf::Text::Bold);
    text.setPosition(sf::Vector2f(400 - text.getLocalBounds().width/2,200));
    window.draw(text);    

    font.loadFromFile("images_justep/Trouble.otf");

    text.setFont(font);
    text.setString("Press Enter to submit");
    text.setCharacterSize(25);
    text.setFillColor(sf::Color(0,0,0));
    text.setStyle(sf::Text::Bold);
    text.setPosition(sf::Vector2f(400 - text.getLocalBounds().width/2,345));
    window.draw(text);

    texture.loadFromFile("images_justep/paint.png");
    texture.setSmooth(true);
    sprite.setTexture(texture);
    sprite.setScale(1.3,0.9);
    sprite.setPosition(sf::Vector2f(APP_SIZE_X4/4 - 47,430));
    window.draw(sprite);

    font.loadFromFile("images_justep/arial.ttf");
    text.setString("Tentatives restantes : " + std::to_string(get_nb_try()));
    text.setCharacterSize(30);
    text.setFillColor(sf::Color::White);
    text.setStyle(sf::Text::Bold);
    text.setPosition(sf::Vector2f(APP_SIZE_X4/3-30,460));
    window.draw(text);

}


void Juste_Prix::print_end(bool winner,sf::RenderWindow &window){
    sf::Time delayTime = sf::milliseconds(2500);
    sf::Texture texture;
    sf::Sprite sprite;
    if (winner){ 
        texture.loadFromFile("images_justep/you_win.png");
        sprite.setPosition(sf::Vector2f(530/2,411/2)); }
    else{ 
        texture.loadFromFile("images_justep/game_over.png"); 
        sprite.setPosition(sf::Vector2f(450/2,411/2)); }

    sprite.setTexture(texture);
           
    window.draw(sprite);
    window.display();
    sf::sleep(delayTime);
}