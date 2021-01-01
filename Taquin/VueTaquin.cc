#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include <vector>
#include <stdexcept>  // std::invalid_argument

#include "Taquin.hh"

using namespace std;
 
void Taquin :: display(sf::RenderWindow& window){

    window.clear();
    init_background(window);
    window.display();    

	while (window.isOpen() && !win() && nb_try > 0) {

		sf::Event event;
 
        while (window.pollEvent(event)) {

            if (event.type == sf::Event::Closed){ 
                window.close();
                break;                
            }
        }
			
		window.clear();
        init_background(window);
        window.display();
	}
}

bool Taquin :: check_move() {

	return true;
}

void Taquin :: init_background(sf::RenderWindow& window) {   

    //cout << v_name.size() << endl;
    //cout << v_position.size() << endl; 
    
    for (int i = 0; i < 8; ++i){

        cout << i << endl;
        cout << v_name[i] << endl;
        cout << "(" << v_position[i].x << "," << v_position[i].y << ")" << endl;

        sf::Texture texture;
        sf::Sprite sprite;
        texture.loadFromFile(v_name[i]);
        sprite.setTexture(texture);
        sprite.setScale(0.35,0.35);
        sprite.setPosition(v_position[i]);
        window.draw(sprite);
    }

    sf::Texture texture;
    sf::Sprite sprite;
    texture.loadFromFile("images/background.jpg");
    sprite.setTexture(texture);
    window.draw(sprite);

    texture.loadFromFile("images/taquin.png"); 
    sprite.setTexture(texture);
    sprite.setPosition(sf::Vector2f(10,20));
    sprite.setScale(0.35,0.35);
    window.draw(sprite);

    sf::Font font;
    font.loadFromFile("images/arial.ttf");
    sf::Text text;
    text.setFont(font);
    text.setString("Test \n 6/6");
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::Black);
    text.setStyle(sf::Text::Bold);
    text.setPosition(sf::Vector2f(28,35));
    window.draw(text);

    font.loadFromFile("images/lakeshore.ttf");
    text.setFont(font);
    text.setString("Epreuve du Taquin");
    text.setCharacterSize(65);
    text.setFillColor(sf::Color::Black);
    text.setStyle(sf::Text::Bold);
    text.setPosition(sf::Vector2f(APP_SIZE_X/4,25));
    window.draw(text);

    texture.loadFromFile("images/paint.png");
    texture.setSmooth(true);
    sprite.setTexture(texture);
    sprite.setScale(1.3,0.9);
    sprite.setPosition(sf::Vector2f(APP_SIZE_X/4 - 47,480));
    window.draw(sprite);

    font.loadFromFile("images/arial.ttf");
    text.setString("Tentatives restantes : " + std::to_string(nb_try));
    text.setCharacterSize(30);
    text.setFillColor(sf::Color::White);
    text.setStyle(sf::Text::Bold);
    text.setPosition(sf::Vector2f(APP_SIZE_X/3-30,510));
    window.draw(text);
}

void Taquin :: transition() {


}