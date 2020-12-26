#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>

#include "pendu.hh"

 
void Pendu::display(){

    /* Init la fenetre */
    sf::RenderWindow window(sf::VideoMode(APP_SIZE_X, APP_SIZE_Y), "Pendu de la mort qui tue"); 
    TextEntry player(window,APP_SIZE_X,APP_SIZE_Y+170);
    std::string prev= get_user_entry(); 

    window.clear();
    init_background(window);
    window.display();

    /* Boucle de jeu */
    while (window.isOpen() && !win() && get_nb_try() )
    {
        /* Test les événements */
        sf::Event event;
        while (window.pollEvent(event))
        {
            player.check_events(window,event);
            if (event.type == sf::Event::Closed){ 
                window.close();
                break;                
            }

        } 
        prev= get_user_entry(); 
        if (player.get_finalInput() != "" && prev != player.get_finalInput()){
            set_user_entry(player.get_finalInput());
            play();
        }
        

                /* Affichage de la grille */
        window.clear();
        init_background(window);
        player.display(window);
        print_game(window);
        window.display();

    }  

    print_end(win(),window); 
    std::cout<<"la solution est: "<<get_mistery()<<std::endl;

}

void Pendu:: init_background(sf::RenderWindow &window){
    
    sf::Texture texture;
    sf::Sprite sprite;
    texture.loadFromFile(TEXTURE_BACKGROUND);
    sprite.setTexture(texture);
    window.draw(sprite);

    texture.loadFromFile(TEXTURE_BACKNAME);
    sprite.setTexture(texture);
    sprite.setPosition(sf::Vector2f(10,0));
    window.draw(sprite);
 
    sf::Font font;
    font.loadFromFile("arial.ttf");
    sf::Text text;
    text.setFont(font);
    text.setString("Test \n 3/6");
    text.setCharacterSize(20);
    text.setFillColor(sf::Color::White);
    text.setStyle(sf::Text::Bold);
    text.setPosition(sf::Vector2f(43,78));
    window.draw(text);

    texture.loadFromFile(TEXTURE_NAME);
    sprite.setPosition(sf::Vector2f(APP_SIZE_X/2-74,20)); 
    sprite.setTexture(texture);
    window.draw(sprite);

    texture.loadFromFile(TEXTURE_BACKGAME);
    texture.setSmooth(true);
    sprite.setTexture(texture);
    sprite.setPosition(sf::Vector2f(APP_SIZE_X/4+10,160));
    window.draw(sprite);

    texture.loadFromFile(TEXTURE_LETTERS);
    texture.setSmooth(true);
    sprite.setTexture(texture);
    sprite.setPosition(sf::Vector2f(100,300));
    window.draw(sprite);

    text.setString("Press enter to submit :");
    text.setCharacterSize(17);
    text.setFillColor(sf::Color::White);
    text.setStyle(sf::Text::Bold);
    text.setPosition(sf::Vector2f(300,330));
    window.draw(text);

    text.setString("Lettres deja utilisees :");
    text.setCharacterSize(17);
    text.setFillColor(sf::Color::White);
    text.setStyle(sf::Text::Bold);
    text.setPosition(sf::Vector2f(300,430));
    window.draw(text);

    text.setString("Vies restantes : " + std::to_string(get_nb_try()));
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::White);
    text.setStyle(sf::Text::Bold);
    text.setPosition(sf::Vector2f(APP_SIZE_X/3+30,500));
    window.draw(text); 
}

void Pendu::print_game( sf::RenderWindow &window ){
    print_word(window);
    print_used_letters(window);
}

/* Affichage du jeu */ 
void Pendu::print_word(sf::RenderWindow &window){
    std::string res;

    for (size_t i=0; i<get_found_letters().size();i++){
        if (get_found_letters()[i]){
            res = res + " " + get_mistery()[i];
        }
        else {
            res = res + " _";
        }
    }

    sf::Font font;
    font.loadFromFile("arial.ttf");
    sf::Text text;
    text.setFont(font);
    text.setString(res);
    text.setCharacterSize(25);
    text.setFillColor(sf::Color::White);
    text.setStyle(sf::Text::Bold);
    text.setPosition(sf::Vector2f((APP_SIZE_X-(get_mistery().size()*25))/2,190));
    window.draw(text);
   
}

/* Affichage du jeu */ 
void Pendu::print_used_letters(sf::RenderWindow &window){
    std::string res;
    std::size_t cpt = 0;

    for (size_t i=0; i<get_used_letters().size();i++){
        
            res = res + " " + get_used_letters()[i];
            cpt ++;
        
    }

    sf::Font font;
    font.loadFromFile("arial.ttf");
    sf::Text text;
    text.setFont(font);
    text.setString(res);
    text.setCharacterSize(16);
    text.setFillColor(sf::Color::White);
    text.setStyle(sf::Text::Bold);
    text.setPosition(sf::Vector2f((APP_SIZE_X-(get_used_letters().size()*16))/2,470));
    window.draw(text);
   
}

void Pendu::print_end(bool winner,sf::RenderWindow &window){

    sf::Time delayTime = sf::milliseconds(2500);
    sf::Texture texture;
    sf::Sprite sprite;
    if (winner){ 
        texture.loadFromFile(TEXTURE_WIN);
        sprite.setPosition(sf::Vector2f(530/2,411/2)); }
    else{ 
        texture.loadFromFile(TEXTURE_LOSE); 
        sprite.setPosition(sf::Vector2f(450/2,411/2)); }

    sprite.setTexture(texture);
           
    window.draw(sprite);
    window.display();
    sf::sleep(delayTime);
}

void Pendu::transition(){

}

