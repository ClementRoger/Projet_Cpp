#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>

#include "pendu.hh"

 
void Pendu::display(sf::RenderWindow& window){

    /* Init la fenetre */
    TextEntry player(window,APP_SIZE_X1,APP_SIZE_Y1+170);
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

/* Permet de crée un sprite et de le dessiner sur la fenetre */
void Pendu::create_sprite(sf::RenderWindow &window, const std::size_t x, const std::size_t y, const std::string file){
    sf::Texture texture;
    sf::Sprite sprite;
    texture.loadFromFile(file);
    sprite.setTexture(texture);
    sprite.setPosition(sf::Vector2f(x,y));
    window.draw(sprite);
}

/* Permet de crée un texte et de le dessiner sur la fenetre */
void Pendu::create_text(sf::RenderWindow &window, const sf::Font font, const std::size_t fontSize, const std::size_t x, const std::size_t y, const std::string input){
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
void Pendu::create_text(sf::RenderWindow &window, const sf::Font font, const std::size_t fontSize, const std::size_t x, const std::size_t y, const std::wstring input){
    sf::Text text;
    text.setFont(font);
    text.setString(input);
    text.setCharacterSize(fontSize);
    text.setFillColor(sf::Color::White);
    text.setStyle(sf::Text::Bold);
    text.setPosition(sf::Vector2f(x,y));
    window.draw(text);
}

void Pendu:: init_background(sf::RenderWindow &window){
    
    sf::Font font;
    font.loadFromFile("img_pendu/arial.ttf");

    create_sprite(window,0,0,TEXTURE_BACKGROUND1);
    create_sprite(window,10,0,TEXTURE_BACKNAME1);
    create_text(window,font,20,43,78,L"Test \n 2/6");
    create_sprite(window,APP_SIZE_X1/2-74,20,TEXTURE_NAME1);
    create_sprite(window,APP_SIZE_X1/4+10,160,TEXTURE_BACKGAME1);
    create_sprite(window,100,300,TEXTURE_LETTERS1);
    create_text(window,font,17,300,330,L"Press enter to submit :");
    create_text(window,font,17,300,430,L"Lettres deja utilisees :");
    create_text(window,font,24,APP_SIZE_X1/3+30,500,L"Vies restantes : " + std::to_wstring(get_nb_try()));

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
            res = res + " " + get_solution()[i];
        }
        else {
            res = res + " _";
        }
    }

    sf::Font font;
    font.loadFromFile("arial.ttf");

    create_text(window,font,25,(APP_SIZE_X1-(get_solution().size()*25))/2,190,res);
   
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
    font.loadFromFile("img_pendu/arial.ttf");

    create_text(window,font,16,(APP_SIZE_X1-(get_used_letters().size()*16))/2,470,res);
   
}

void Pendu::print_end(bool winner,sf::RenderWindow &window){

    sf::Time delayTime = sf::milliseconds(2500);

    if (winner) create_sprite(window,530/2,411/2,TEXTURE_WIN1);
    else create_sprite(window,450/2,411/2,TEXTURE_LOSE1);

    window.display();
    sf::sleep(delayTime);
    transition(window);
}

std::wstring Pendu::setFinalText(bool win){
    std::wstring res;

    if (win){
        res = std::wstring(L"\n\nFélicitations, un tiers du chemin parcouru.\n") + 
        std::wstring(L"Pour la troisième épreuve, vous allez affronter Eddy\n") + 
        std::wstring(L"dans le jeu des bâtonnets. Devant vous se trouvent\n") + 
        std::wstring(L"vingts bâtonnets. Chacun votre tour vous aurez le droit\n") +
        std::wstring(L"de prendre un, deux ou trois bâtonnets, celui qui\n" )+ 
        std::wstring(L"s'empare du dernier bâtonnet perd la partie. Le plus\n" )+ 
        std::wstring(L"jeune commence, c'est-à-dire vous.\n\n") +

        std::wstring(L"Étant donné qu'Eddy est très mauvais perdant je ne\n") + 
        std::wstring(L"vous garantie pas la survie si vous le battez, mais\n") + 
        std::wstring(L"j\'essaierai de vous proteger le moment venu.\n" );
    }

    else {
        res = std::wstring(L"\n\n\n J\'en étais sur.\n\n") +
        std::wstring(L"Encore un gugusse qui réussit les épreuves mathématiques\n" )+
        std::wstring(L"mais qui n'a jamais ouvert un livre de sa vie. Vous\n") +
        std::wstring(L"savez comment on appelle les gens comme vous avec Eddy ?\n\n" )+

        std::wstring(L"Des MAIN, pour Mots Aussi Importants que les Nombres.\n") +
        std::wstring(L"Allez Eddy, liquide moi ce MAIN. *Gunshot* \n" ); 
    }

    return res;
}

void Pendu:: init_transition(sf::RenderWindow &window){

    sf::Font font;
    font.loadFromFile("img_pendu/Type.ttf");

    create_sprite(window,0,0,TEXTURE_TRANSITION1);
    create_text(window,font,20,120,85,setFinalText(win()));
    create_text(window,font,16,510,495,L"Press enter \nto continue...");

}


void Pendu::transition(sf::RenderWindow &window){
     sf::Event event;
     std::size_t cpt = 0;

     while(window.isOpen() && cpt < 1){
        while (window.pollEvent(event))
        {
            // Changer de fond
            if (((event.type == sf::Event::KeyPressed)&&(event.key.code == sf::Keyboard::Enter))){
               cpt ++;
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

