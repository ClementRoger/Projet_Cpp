#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>

#include "missingnumber.hh"

/* Boucle principale du jeu */
void Missingnumber::display(sf::RenderWindow &window){

    /* Création de la zone de texte */
    TextEntry player(window,APP_SIZE_X2,APP_SIZE_Y2+200);
    std::string prev= get_user_entry(); 

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
        
        window.clear();
        print_game(window);
        player.display(window);
        window.display();

    }  

    print_end(win(),window); 
    std::cout<<"la solution est: "<<get_solution()<<std::endl;

}

/* Permet de crée un sprite et de le dessiner sur la fenetre */
void Missingnumber::create_sprite(sf::RenderWindow &window, const std::size_t x, const std::size_t y, const std::string file)const{
    sf::Texture texture;
    sf::Sprite sprite;
    texture.loadFromFile(file);
    sprite.setTexture(texture);
    sprite.setPosition(sf::Vector2f(x,y));
    window.draw(sprite);
}

/* Permet de crée un texte et de le dessiner sur la fenetre */
void Missingnumber::create_text(sf::RenderWindow &window, const sf::Font font, const std::size_t fontSize, const std::size_t x, const std::size_t y, const std::string input)const{
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
void Missingnumber::create_text(sf::RenderWindow &window, const sf::Font font, const std::size_t fontSize, const std::size_t x, const std::size_t y, const std::wstring input)const{
    sf::Text text;
    text.setFont(font);
    text.setString(input);
    text.setCharacterSize(fontSize);
    text.setFillColor(sf::Color::White);
    text.setStyle(sf::Text::Bold);
    text.setPosition(sf::Vector2f(x,y));
    window.draw(text);
}

/* Permet d'initialiser le fond du jeu */
void Missingnumber:: init_background(sf::RenderWindow &window)const{
    sf::Font font;
    font.loadFromFile("img_missing/arial.ttf");
    create_sprite(window,0,0,TEXTURE_BACKGROUND2);
    create_sprite(window,(APP_SIZE_X2-580)/2,(APP_SIZE_Y2-307)/2-10,TEXTURE_LETTERS2);
    create_sprite(window,(APP_SIZE_X2-348)/2,185,TEXTURE_GRID2);
    create_text(window,font,24,APP_SIZE_X2/3+30,450,"Vies restantes : " + std::to_string(get_nb_try()));
    create_text(window,font,17,300,350,"Press enter to submit :");
    create_sprite(window,10,10,TEXTURE_BACKNAME2);
    create_text(window,font,17,27,33,"Test \n 4/6");
    create_sprite(window,APP_SIZE_X2/2-260,15,TEXTURE_NAME2);

}


/* Affichage du jeu */ 
void Missingnumber::print_game(sf::RenderWindow &window)const{
    init_background(window);
    sf::Font font;
    font.loadFromFile("img_missing/arial.ttf");

    for (std::size_t i = 0; i < get_matrice().size(); i++){
        for (std::size_t j = 0; j < get_matrice().size(); j++){
            create_text(window,font,25,(APP_SIZE_X2-348)/2-5 + (2*i+1)*58 , 170 + (2*j+1)*25,get_matrice()[j][i]);

        }
    }
} 

/* Affichage d'un game-over ou you win */
void Missingnumber::print_end(const bool winner,sf::RenderWindow &window){

    sf::Time delayTime = sf::milliseconds(2500);

    if (winner) create_sprite(window,530/2,411/2,TEXTURE_WIN2);
    else create_sprite(window,450/2,411/2,TEXTURE_LOSE2);

    window.display();
    sf::sleep(delayTime);
    transition(window);
}

/* Renvoie le message de transition */
std::wstring Missingnumber::setFinalText(const bool win)const{
    std::wstring res;

    if (win){
        res = std::wstring(L"\n\nHum, je vais commencer à croire que vous\n") + 
        std::wstring(L"allez réussir le test. Il vous reste deux épreuves,  \n") + 
        std::wstring(L"et la prochaine c\'est de la bombe puisqu\'il \n") + 
        std::wstring(L"s\'agit d\'un démineur ! \n\n") +
        std::wstring(L"Vous savez, dix heures dans ce bureau tous les jours \n") + 
        std::wstring(L"à voir des idiots dans votre genre c\'est épuisant  \n") + 
        std::wstring(L"donc si vous pouviez au moins rigoler à mes vannes \n") +
        std::wstring(L"ça me faciliterait la tache.\n \n") +
       
        std::wstring(L"Enfin bref, vous devez connaître le principe du \n") + 
        std::wstring(L"démineur : vous avez une grille où sont cachées\n") + 
        std::wstring(L"des bombes. A chaque fois que vous cliquez sur \n" )+
        std::wstring(L"une case, on affiche combien de bombes sont\n") +
        std::wstring(L"adjacentes à celle-ci. Si vous parvenez à découvrir\n") + 
        std::wstring(L"toutes les cases sans toucher les bombes, vous\n") + 
        std::wstring(L"réussissez l'épreuve, mais faites attention, vous\n") +
        std::wstring(L"avez un nombre limité de vies.");
    }
    else {
        res = std::wstring(L"\n\n\n\n\n\nJe suis déçu. Alors que ça devenait enfin \n")+
        std::wstring(L"intéressant,vous échouez lamentablement.\n" )+
        std::wstring(L"Vous voulez la réponse avant de ... enfin vous\n" )+
        std::wstring(L"savez ? Je peux vous la donner, c\'est pas comme si\n") +
        std::wstring(L" vous alliez pouvoir retenter l\'épreuve plus\ntard !\n\n" )+

        std::wstring(L"C\'était ... *Gunshot*. Eddy ! La dernière\n") +
        std::wstring(L"volonté, ça te parle ? Quel idiot.\n") + 
        std::wstring(L"Allez nettoie moi tout ça ...");
    }

    return res;
}

/* Initialise la transition */
void Missingnumber:: init_transition(sf::RenderWindow &window)const{
 
    sf::Font font;
    font.loadFromFile("img_missing/Type.ttf");

    create_sprite(window,0,0,TEXTURE_TRANSITION2);
    create_text(window,font,20,90,20,setFinalText(win()));
    create_text(window,font,16,510,505,"Press enter \nto continue...");
}


