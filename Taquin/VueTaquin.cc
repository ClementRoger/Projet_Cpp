#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include <vector>
#include <stdexcept>  // std::invalid_argument
#include <math.h>

#include "Taquin.hh"

#define d 100

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

            if (event.type == sf::Event::MouseButtonPressed){

                int x = sf::Mouse::getPosition(window).x;
                int y = sf::Mouse::getPosition(window).y;
                int image_number = get_image_number(x,y);
                number = image_number;

                if (check_move(image_number)) {

                    play();
                    nb_try--;
                    set_win(check_victory());
                }
            }
        }
			
		window.clear();
        init_background(window);
        window.display();
	}
}

bool Taquin :: check_move(int number) {

    int x1 = v_position[number].x;
    int y1 = v_position[number].y;

    int x2 = case_vide.x;
    int y2 = case_vide.y;

    int module = sqrt( pow((x2 - x1),2) + pow((y2 - y1),2) );

    if ( module == d ){

        return true;
    }

	return false;
}

void Taquin :: init_background(sf::RenderWindow& window) {   

    sf::Texture texture;
    sf::Sprite sprite;

    texture.loadFromFile("images/background.jpg");
    sprite.setTexture(texture);
    window.draw(sprite);

      for (int i = 0; i < 8; ++i){

        sf::Texture texture;
        sf::Sprite sprite;
        texture.loadFromFile(v_name[i]);
        sprite.setTexture(texture);
        sprite.setScale(0.5,0.5);
        sprite.setPosition(v_position[i]);
        window.draw(sprite);
    }

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
    text.setString("Mouvements restants : " + std::to_string(nb_try));
    text.setCharacterSize(30);
    text.setFillColor(sf::Color::White);
    text.setStyle(sf::Text::Bold);
    text.setPosition(sf::Vector2f(APP_SIZE_X/3-48,510));
    window.draw(text);
}

int Taquin :: get_image_number(int x, int y) {

    for (int i = 0; i < 8; ++i) {

        if(x >= v_position[i].x && x <= (v_position[i].x + d) && y >= v_position[i].y && y <= (v_position[i].y + d) ) {

            return i;
        } 
    }

    return -1;
}

bool Taquin :: check_victory() {

    for (int i = 0; i < 8; ++i) { 

        if( (v_position[i].x != v_solution[i].x) || (v_position[i].y != v_solution[i].y) ) {
            
            return false;
        }
    }

    return true;
}

void Taquin :: transition(sf::RenderWindow& window) {


}