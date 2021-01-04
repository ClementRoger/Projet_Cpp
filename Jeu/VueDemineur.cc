#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include <vector>

#include "Demineur.hh"

 
void Demineur::display(sf::RenderWindow& window){

    /* Init la fenetre */ 
    bool gridclick = false;
    sf::Vector2i position;

    /* Boucle de jeu */
    while (window.isOpen() && !win() && get_nb_try() )
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

        // Click dans la zone de jeu ?
        if (gridclick){
            set_pos_x(position.x);
            set_pos_y(position.y);
            play();
            gridclick = false;
        }  

                /* Affichage de la grille */
        window.clear();
        init_background(window);

        print_grid(window,get_open_tiles());
        window.display();

    }  

    print_end(win(),window);
}

/* Permet de crée un sprite et de le dessiner sur la fenetre */
void Demineur::create_sprite(sf::RenderWindow &window, const std::size_t x, const std::size_t y, const std::string file)const{
    sf::Texture texture;
    sf::Sprite sprite;
    texture.loadFromFile(file);
    sprite.setTexture(texture);
    sprite.setPosition(sf::Vector2f(x,y));
    window.draw(sprite);
}

/* Permet de crée un texte et de le dessiner sur la fenetre */
void Demineur::create_text(sf::RenderWindow &window, const sf::Font font, const std::size_t fontSize, const std::size_t x, const std::size_t y, const std::string input)const{
    sf::Text text;
    text.setFont(font);
    text.setString(input);
    text.setCharacterSize(fontSize);
    text.setFillColor(sf::Color::White);
    text.setStyle(sf::Text::Bold);
    text.setPosition(sf::Vector2f(x,y));
    window.draw(text);
}


/* Permet de crée un texte et de le dessiner sur la fenetre */
void Demineur::create_text(sf::RenderWindow &window, const sf::Font font, const std::size_t fontSize, const std::size_t x, const std::size_t y, const std::wstring input)const{
    sf::Text text;
    text.setFont(font);
    text.setString(input);
    text.setCharacterSize(fontSize);
    text.setFillColor(sf::Color::White);
    text.setStyle(sf::Text::Bold);
    text.setPosition(sf::Vector2f(x,y));
    window.draw(text);
}

void Demineur:: init_background(sf::RenderWindow &window)const{

    sf::Font font;
    font.loadFromFile("img_missing/arial.ttf");
    create_sprite(window,0,0,TEXTURE_BACKGROUND);
    create_sprite(window,10,0,TEXTURE_BACKNAME);
    create_text(window,font,24,28,43,"Test \n 5/6");
    create_sprite(window,APP_SIZE_X/4+10,450,TEXTURE_BACKGAME);

    create_text(window,font,30,APP_SIZE_X/3-8,480,"Erreurs restantes : " + std::to_string(get_nb_try()));

    create_sprite(window,APP_SIZE_X/4,0,TEXTURE_NAME);
}

/* Permet de determiner la position de la souris lors du click + de savoir si ce click est dans la grille de jeu */
bool Demineur::Get_Mouse_Click(sf::RenderWindow &window,sf::Vector2i& position)const{
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
bool Demineur::test_grid_border(const sf::Vector2i position)const{

    if ( (position.x >= (int)(APP_SIZE_X-(IMG_SIZE*get_plateau().size()))/2 )
        && (position.x <= (int)((APP_SIZE_X-(IMG_SIZE*get_plateau().size()))/2+IMG_SIZE*get_plateau().size()))
        && (position.y >= (int)(APP_SIZE_Y -(IMG_SIZE*get_plateau().size()))/2 )
        && (position.y <= (int)((APP_SIZE_Y-(IMG_SIZE*get_plateau().size()))/2+IMG_SIZE*get_plateau().size())) ) {
        return true;
    }
    
    return false;
}

/* Affichage du jeu */ 
void Demineur::print_grid(sf::RenderWindow &window,const std::vector<std::vector<bool>>matrice)const{

    sf::Texture texture;
    sf::Sprite sprite;
    for(std::size_t x=0; x < get_plateau().size(); x++){
        for(std::size_t y=0; y < get_plateau().size(); y++){

            if (matrice[x][y]){

                if(get_plateau()[x][y]>0){number_texture(get_plateau()[x][y],texture);}

                else if (get_plateau()[x][y]<0){ texture.loadFromFile(TEXTURE_BOMB);}

                else{ 
                    texture.loadFromFile(TEXTURE_NONE); }
            }
            else { texture.loadFromFile(TEXTURE_CELL); } 
            sprite.setTexture(texture);
            sprite.setPosition(sf::Vector2f(IMG_SIZE*x,IMG_SIZE*y));
            sprite.move((APP_SIZE_X-(IMG_SIZE*get_plateau().size()))/2, (APP_SIZE_Y-(IMG_SIZE*get_plateau().size()))/2);
            window.draw(sprite);
        } 
    }
}

void Demineur::number_texture(const int val, sf::Texture& texture)const{
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


void Demineur::print_end(const bool winner,sf::RenderWindow &window){

    sf::Time delayTime = sf::milliseconds(2500);

    if (winner) create_sprite(window,530/2,411/2,TEXTURE_WIN);
    else create_sprite(window,450/2,411/2,TEXTURE_LOSE);

    window.display();
    sf::sleep(delayTime);
    transition(window);
}



std::wstring Demineur::setFinalText(const bool win)const{
    std::wstring res;

    if (win){
        res = std::wstring(L"\n\nSixième et dernière épreuve. Ouah que le temps \n" )+ 
        std::wstring(L"passe vite quand on s’amuse ! Pour celle-là,\n" )+ 
        std::wstring(L"vous devrez résoudre un taquin. Quoi ? Vous savez \n") + 
        std::wstring(L"pas ce que c’est c’est ça ? Mais si, je suis sûr\n") +
        std::wstring(L"que vous avez déjà vu ça, le jeu où vous bougez \n" )+ 
        std::wstring(L"les tuiles pour reconstituer un dessin. Nan ? \n" )+ 

        std::wstring(L"Ça vous dit rien ? \n\n" )+
        std::wstring(L"Et bah vous comprendrez en jouant ... enfin j’espère\n") +
        std::wstring(L"pour vous !");

    }
    else {
        res = std::wstring(L"\n\n\n\nPas vraiment de surprise, vous avez explosé en vol.\n")+
        std::wstring(L"Oh allez j’essaye de vous faire rire une \n" )+
        std::wstring(L"dernière fois avant le grand voyage. Bon \n" )+
        std::wstring(L"bah j’aurais essayé ...\n\n" )+
        std::wstring(L"Eddy, explose lui la cervelle ! *Gunshot* ");
    }

    return res;
}

void Demineur:: init_transition(sf::RenderWindow &window)const{

    sf::Font font;
    font.loadFromFile("img_pendu/Type.ttf");

    create_sprite(window,0,0,TEXTURE_TRANSITION);
    create_text(window,font,20,100,130,setFinalText(win()));
    create_text(window,font,16,510,505,"Press enter \nto continue...");

}


void Demineur::transition(sf::RenderWindow &window){
     sf::Event event;
     bool cpt = 0;

     while(window.isOpen() && !cpt){
        while (window.pollEvent(event))
        {
            // Changer de fond
            if (((event.type == sf::Event::KeyPressed)&&(event.key.code == sf::Keyboard::Enter))){
               cpt = true ;
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

