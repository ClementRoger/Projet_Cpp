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

	while (window.isOpen() && !win() && get_nb_try() > 0) {

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
                    set_nb_try(get_nb_try()-1);
                    set_win(check_victory());
                }
            }
        }
			
		window.clear();
        init_background(window);
        window.display();
	}

    print_end(win(),window);
}

bool Taquin :: check_move(const int number) const {

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

void Taquin :: init_background(sf::RenderWindow& window)const{   

    sf::Texture texture;
    sf::Sprite sprite;

    texture.loadFromFile("images_taquin/background.jpg");
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

    texture.loadFromFile("images_taquin/taquin.png"); 
    sprite.setTexture(texture);
    sprite.setPosition(sf::Vector2f(10,20));
    sprite.setScale(0.35,0.35);
    window.draw(sprite);

    sf::Font font;
    font.loadFromFile("images_taquin/arial.ttf");
    sf::Text text;
    text.setFont(font);
    text.setString("Test \n 6/6");
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::Black);
    text.setStyle(sf::Text::Bold);
    text.setPosition(sf::Vector2f(28,35));
    window.draw(text);

    font.loadFromFile("images_taquin/lakeshore.ttf");
    text.setFont(font);
    text.setString("Epreuve du Taquin");
    text.setCharacterSize(65);
    text.setFillColor(sf::Color::Black);
    text.setStyle(sf::Text::Bold);
    text.setPosition(sf::Vector2f(APP_SIZE_X5/4,25));
    window.draw(text);

    texture.loadFromFile("images_taquin/paint.png");
    texture.setSmooth(true);
    sprite.setTexture(texture);
    sprite.setScale(1.3,0.9);
    sprite.setPosition(sf::Vector2f(APP_SIZE_X5/4 - 47,480));
    window.draw(sprite);

    font.loadFromFile("images_taquin/arial.ttf");
    text.setString("Mouvements restants : " + std::to_string(get_nb_try()));
    text.setCharacterSize(30);
    text.setFillColor(sf::Color::White);
    text.setStyle(sf::Text::Bold);
    text.setPosition(sf::Vector2f(APP_SIZE_X5/3-48,510));
    window.draw(text);
}

int Taquin :: get_image_number(const int x, const int y) const{

    for (int i = 0; i < 8; ++i) {

        if(x >= v_position[i].x && x <= (v_position[i].x + d) && y >= v_position[i].y && y <= (v_position[i].y + d) ) {

            return i;
        } 
    }

    return -1;
}

bool Taquin :: check_victory() const{

    return v_position == v_solution; //Surcharge d'opérateur
}

void Taquin :: print_end(const bool winner,sf::RenderWindow &window){

    sf::Time delayTime = sf::milliseconds(2500);

    sf::Texture texture;
    sf::Sprite sprite;

    if (winner) {

        texture.loadFromFile("images_taquin/win.png");
        sprite.setTexture(texture);
    }    

    else {

        texture.loadFromFile("images_taquin/game_over.png");
        sprite.setTexture(texture);
    }    

    sprite.setScale(0.9,0.9);
    sprite.setPosition(APP_SIZE_X5/2 - sprite.getLocalBounds().width/2,APP_SIZE_Y5/2 - sprite.getLocalBounds().height/2);
    window.draw(sprite);

    window.display();
    sf::sleep(delayTime);
    transition(window);
}

wstring Taquin :: setFinalText(const bool win)const{

    std::wstring res;

    if (win){

        res = std::wstring(L"Bon, il semblerait que vous ayiez réussi. Vous vous \n" )+ 
        std::wstring(L"attendiez à des cotillons et des feux d’artifices ? Allez,\n" )+ 
        std::wstring(L"ouste, j’ai d’autres gens à faire passer moi ... \n\n") + 
        std::wstring(L"NAN ! Pas cette porte ! c’est celle où Eddy entasse \n") +
        std::wstring(L"ceux qui ont raté. Me regardez pas comme ça, on les rend \n" )+ 
        std::wstring(L"à leur famille après … enfin je crois, faudrait que je \n" )+ 
        std::wstring(L"demande à Thierry du service morgue ... \n\n" );

    }

    else {
        res = std::wstring(L"\n\nOuah si près du but ça fait mal au coeur. Nan je\n")+
        std::wstring(L"vous jure, j’y croyais, , je me disais que vous alliez y \n" )+
        std::wstring(L"arriver. Je suis à deux doigts de vous laisser retenter la\n" )+
        std::wstring(L"dernière épreuve ... Naaan je rigole. Eddy je te laisse \n" )+
        std::wstring(L"t’occuper de lui, je vais me chercher un café.\n\n") +
        std::wstring(L"Comme d’habitude, je te prends un déca ? *Gunshot*\n\n");
    }

    return res;
}

void Taquin :: init_transition(sf::RenderWindow &window)const{

    sf::Font font;
    font.loadFromFile("images_taquin/Type.ttf");
    wstring str = L"Press enter \nto continue...";

    sf::Texture texture;
    sf::Sprite sprite;

    texture.loadFromFile("images_taquin/wall.jpeg");
    sprite.setTexture(texture);
    window.draw(sprite);

    sf::Text text;
    text.setFont(font);
    text.setString(setFinalText(win()));
    text.setCharacterSize(18);
    text.setFillColor(sf::Color::White);
    text.setStyle(sf::Text::Bold);
    text.setPosition(sf::Vector2f((APP_SIZE_X5 - text.getLocalBounds().width)/2,(APP_SIZE_Y5 - text.getLocalBounds().height)/2));
    window.draw(text);

    text.setString(str);
    text.setCharacterSize(16);
    text.setFillColor(sf::Color::White);
    text.setStyle(sf::Text::Bold);
    text.setPosition(sf::Vector2f(510,505));
    window.draw(text);
}

void Taquin :: transition(sf::RenderWindow &window){

    sf::Event event;
    bool cpt = false;

    while(window.isOpen() && !cpt){
    
        while (window.pollEvent(event)) {
            
            if (((event.type == sf::Event::KeyPressed)&&(event.key.code == sf::Keyboard::Enter))) {

               cpt =true ;
            }

            if (event.type == sf::Event::Closed){ 

                    window.close();
                    break;                
            }
        } 

        window.clear();
        init_transition(window);
        window.display();
    }
    
}
