#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include <vector>

#include "Demineur.hh"



void Demineur::display(){

    /* Init la fenetre */
    sf::RenderWindow window(sf::VideoMode(APP_SIZE_X, APP_SIZE_Y), "Demineur de la mort qui tue"); 
    
    std::vector<std::vector<bool>>tmp(get_plateau().size(),std::vector<bool>(get_plateau().size(),false));

    bool flag = false;
    bool gridclick = false;

    std::size_t tmp_x,tmp_y;
    sf::Vector2i position;

    window.clear();
    init_background(window);
    print_grid(window,tmp);
    window.display();

    /* Boucle de jeu */
    while (window.isOpen() && !win(flag) && get_nb_try() )
    {
        /* Test les événements */
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed){
                window.close();
                break;                
            }

            if (event.type == sf::Event::MouseButtonPressed){
                gridclick = Get_Mouse_Click(window,position);
                break;
            }
        } 

    /********************************************************/
        // Click dans la zone de jeu ?
        if (gridclick){
            // Permet de récuperer les indices des cases cliqués 
            tmp_x = (std::size_t)(position.x - (APP_SIZE_X-(IMG_SIZE*get_plateau().size()))/2)/IMG_SIZE;
            tmp_y = (std::size_t)(position.y - (APP_SIZE_Y-(IMG_SIZE*get_plateau().size()))/2)/IMG_SIZE;

            if (!tmp[tmp_x][tmp_y]){

                reveal(tmp,get_plateau(),tmp_x,tmp_y);
                tmp[tmp_x][tmp_y] = true;

                if( get_plateau()[tmp_x][tmp_y] == -1 ){
                    set_nb_try(get_nb_try()-1);
                    std::cout<<"Aie, vous etes tombé sur une bombe... Il vous reste : "<<get_nb_try()<<std::endl;
                }
                flag=checkBool(tmp);
            }
            else {
                std::cout<<"Vous avez deja ouvert cette case."<<std::endl;
            }

            gridclick = false;
        }  

                /* Affichage de la grille */
        window.clear();
        init_background(window);
        print_grid(window,tmp);
        window.display();

    }  

    print_end(win(flag),window);
}

void Demineur:: init_background(sf::RenderWindow &window){
    
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
    font.loadFromFile("img/arial.ttf");
    sf::Text text;
    text.setFont(font);
    text.setString("Test \n 5/6");
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::White);
    text.setStyle(sf::Text::Bold);
    text.setPosition(sf::Vector2f(28,43));
    window.draw(text);


    texture.loadFromFile(TEXTURE_BACKGAME);
    texture.setSmooth(true);
    sprite.setTexture(texture);
    sprite.setPosition(sf::Vector2f(APP_SIZE_X/4,450));
    window.draw(sprite);

    text.setString("Vies restantes : " + std::to_string(get_nb_try()));
    text.setCharacterSize(30);
    text.setFillColor(sf::Color::White);
    text.setStyle(sf::Text::Bold);
    text.setPosition(sf::Vector2f(APP_SIZE_X/3+5,480));
    window.draw(text);

    texture.loadFromFile(TEXTURE_NAME);
    sprite.setPosition(sf::Vector2f(APP_SIZE_X/4,0)); 
    sprite.setTexture(texture);
    window.draw(sprite);
}

/* Permet de determiner la position de la souris lors du click + de savoir si ce click est dans la grille de jeu */
bool Demineur::Get_Mouse_Click(sf::RenderWindow &window, sf::Vector2i& position){
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
    return test_grid_border(position);
}

/* Permet de tester si le click se trouve sur la grille de jeu */
bool Demineur::test_grid_border(const sf::Vector2i position){

    if ( (position.x >= (int)(APP_SIZE_X-(IMG_SIZE*get_plateau().size()))/2 )
        && (position.x <= (int)((APP_SIZE_X-(IMG_SIZE*get_plateau().size()))/2+IMG_SIZE*get_plateau().size()))
        && (position.y >= (int)(APP_SIZE_Y -(IMG_SIZE*get_plateau().size()))/2 )
        && (position.y <= (int)((APP_SIZE_X-(IMG_SIZE*get_plateau().size()))/2+IMG_SIZE*get_plateau().size())) ) {
        return true;
    }
    
    return false;
}

/* Affichage du jeu */ 
void Demineur::print_grid(sf::RenderWindow &window,const std::vector<std::vector<bool>>matrice){

    sf::Texture texture;
    sf::Sprite sprite;
    for(std::size_t x=0; x < get_plateau().size(); x++){
        for(std::size_t y=0; y < get_plateau().size(); y++){

            if (matrice[x][y]){

                if(get_plateau()[x][y]>0){number_texture(get_plateau()[x][y],texture);}

                else if (get_plateau()[x][y]<0){ texture.loadFromFile(TEXTURE_BOMB);}

                else{ texture.loadFromFile(TEXTURE_NONE); }
            }
            else { texture.loadFromFile(TEXTURE_CELL); } 
            sprite.setTexture(texture);
            sprite.setPosition(sf::Vector2f(IMG_SIZE*x,IMG_SIZE*y));
            sprite.move((APP_SIZE_X-(IMG_SIZE*get_plateau().size()))/2, (APP_SIZE_Y-(IMG_SIZE*get_plateau().size()))/2);
            window.draw(sprite);
        } 
    }
}

void Demineur::number_texture(const int val, sf::Texture& texture){
    switch(val){
        case 1 : 
                texture.loadFromFile(TEXTURE_1);
                break;
        case 2 : 
                texture.loadFromFile(TEXTURE_2);
                break;
        case 3 : 
                texture.loadFromFile(TEXTURE_3);
                break;
        case 4 : 
                texture.loadFromFile(TEXTURE_4);
                break;
        case 5 : 
                texture.loadFromFile(TEXTURE_5);
                break;
        case 6 : 
                texture.loadFromFile(TEXTURE_6);
                break;
        case 7 : 
                texture.loadFromFile(TEXTURE_7);
                break;
        case 8 : 
                texture.loadFromFile(TEXTURE_8);
                break;
        default:
                texture.loadFromFile(TEXTURE_CELL);
                break;
    }
}


void Demineur::print_end(bool winner,sf::RenderWindow &window){

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
    

