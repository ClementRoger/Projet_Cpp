#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>

#include "missingnumber.hh"

 
void Missingnumber::display(){

    /* Init la fenetre */
    sf::RenderWindow window(sf::VideoMode(APP_SIZE_X, APP_SIZE_Y), "Missingnumber de la mort qui tue"); 
    TextEntry player(window,APP_SIZE_X,APP_SIZE_Y+200);
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
    std::cout<<"la solution est: "<<get_solution()<<std::endl;

}

void Missingnumber:: init_background(sf::RenderWindow &window){
    
    sf::Texture texture;
    sf::Sprite sprite;
    texture.loadFromFile(TEXTURE_BACKGROUND);
    sprite.setTexture(texture);
    window.draw(sprite);

    texture.loadFromFile(TEXTURE_LETTERS);
    texture.setSmooth(true);
    sprite.setTexture(texture);
    sprite.setPosition(sf::Vector2f((APP_SIZE_X-580)/2,(APP_SIZE_Y-307)/2-10));
    window.draw(sprite);

    
    texture.loadFromFile(TEXTURE_GRID);
    sprite.setPosition(sf::Vector2f((APP_SIZE_X-348)/2,185)); 
    sprite.setTexture(texture);
    window.draw(sprite);

    sf::Font font;
    font.loadFromFile("arial.ttf");
    sf::Text text;
    text.setFont(font);
    text.setString("Vies restantes : " + std::to_string(get_nb_try()));
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::White);
    text.setStyle(sf::Text::Bold);
    text.setPosition(sf::Vector2f(APP_SIZE_X/3+30,450));
    window.draw(text);

    text.setString("Press enter to submit :");
    text.setCharacterSize(17);
    text.setFillColor(sf::Color::White);
    text.setStyle(sf::Text::Bold);
    text.setPosition(sf::Vector2f(300,350));
    window.draw(text);
    

    texture.loadFromFile(TEXTURE_BACKNAME);
    sprite.setTexture(texture);
    sprite.setPosition(sf::Vector2f(10,10));
    window.draw(sprite);
 
    text.setString("Test \n 3/6");
    text.setCharacterSize(20);
    text.setFillColor(sf::Color::White);
    text.setStyle(sf::Text::Bold);
    text.setPosition(sf::Vector2f(24,33));
    window.draw(text);

    texture.loadFromFile(TEXTURE_NAME);
    sprite.setPosition(sf::Vector2f(APP_SIZE_X/2-260,15)); 
    sprite.setTexture(texture);
    window.draw(sprite);


     
}



/* Affichage du jeu */ 
void Missingnumber::print_game(sf::RenderWindow &window){

 sf::Font font;
font.loadFromFile("arial.ttf");
sf::Text text;
text.setFont(font);
  for (std::size_t i = 0; i < get_matrice().size(); i++){
    for (std::size_t j = 0; j < get_matrice().size(); j++){
        text.setString(get_matrice()[i][j]);
        text.setCharacterSize(25);
        text.setFillColor(sf::Color::White);
        text.setStyle(sf::Text::Bold);
        text.setPosition(sf::Vector2f( (APP_SIZE_X-348)/2-5 + (2*i+1)*58 , 170 + (2*j+1)*25 ));
        window.draw(text); 

    }
  }
} 


void Missingnumber::print_end(bool winner,sf::RenderWindow &window){

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

void Missingnumber::transition(){

}

