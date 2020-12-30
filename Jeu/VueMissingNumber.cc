#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>

#include "missingnumber.hh"

 
void Missingnumber::display(sf::RenderWindow &window){

    /* Init la fenetre */
    TextEntry player(window,APP_SIZE_X2,APP_SIZE_Y2+200);
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
void Missingnumber::create_sprite(sf::RenderWindow &window, const std::size_t x, const std::size_t y, const std::string file){
    sf::Texture texture;
    sf::Sprite sprite;
    texture.loadFromFile(file);
    sprite.setTexture(texture);
    sprite.setPosition(sf::Vector2f(x,y));
    window.draw(sprite);
}

/* Permet de crée un texte et de le dessiner sur la fenetre */
void Missingnumber::create_text(sf::RenderWindow &window, const sf::Font font, const std::size_t fontSize, const std::size_t x, const std::size_t y, const std::string input){
    sf::Text text;
    text.setFont(font);
    text.setString(input);
    text.setCharacterSize(fontSize);
    text.setFillColor(sf::Color::White);
    text.setStyle(sf::Text::Bold);
    text.setPosition(sf::Vector2f(x,y));
    window.draw(text);
}

void Missingnumber:: init_background(sf::RenderWindow &window){
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
void Missingnumber::print_game(sf::RenderWindow &window){

 sf::Font font;
font.loadFromFile("arial.ttf");

  for (std::size_t i = 0; i < get_matrice().size(); i++){
    for (std::size_t j = 0; j < get_matrice().size(); j++){
        create_text(window,font,25,(APP_SIZE_X2-348)/2-5 + (2*i+1)*58 , 170 + (2*j+1)*25,get_matrice()[i][j]);

    }
  }
} 


void Missingnumber::print_end(bool winner,sf::RenderWindow &window){

    sf::Time delayTime = sf::milliseconds(2500);

    if (winner) create_sprite(window,530/2,411/2,TEXTURE_WIN2);
    else create_sprite(window,450/2,411/2,TEXTURE_LOSE2);

    window.display();
    sf::sleep(delayTime);
    transition(window);
}


std::string Missingnumber::setFinalText(bool win){
    std::string res = "";

    if (win){
        res = std::string("Cinquième épreuve :") + "\n \n" +

        "Hum, je vais commencer à croire que vous" + "\n" + 
        "allez réussir le test. Il vous reste deux" + "\n" + 
        "épreuves, et la prochaine c\'est de la bombe" + "\n" + 
        "puisqu\'il s\'agit d\'un démineur ! " +"\n" +
        "Vous savez, dix heures dans ce bureau tous" + "\n" + 
        "les jours à voir des idiots dans votre genre " + "\n" + 
        "c\'est épuisant donc si vous pouviez au moins" + "\n" +
        "rigoler à mes vannes ça me faciliterait la" + "\n" +
        "tache" + "\n \n" +

        "Enfin bref, vous devez connaître le principe " + "\n" + 
        "du démineur : vous avez une grille où sont" + "\n" + 
        "cachées des bombes. A chaque fois que vous" + "\n" +
        "cliquez sur une case, on affiche combien de" +"\n" +

        "bombes sont adjacentes à celle-ci. Si vous " + "\n" + 
        "parvenez à découvrir toutes les cases sans  " + "\n" + 
        "toucher les bombes, vous réussissez " + "\n" +
        "l\'épreuve, mais faites attention, vous " + "\n" +
        "avez un nombre limité de vies.";

    }
    else {
        res = std::string("Je suis déçu. Alors que ça devenait") + "\n"+
        "enfin intéressant, vous échouez " + "\n" +
        "lamentablement. Vous voulez la réponse" + "\n" +
        "avant de ... enfin vous savez ? Je peux " + "\n" +
        "vous la donner, c\'est pas comme si vous  ? " + "\n" +
        "alliez pouvoir retenter l\'épreuve plus" + "\n" +
        "tard !" + "\n\n" +

        "C\'était ... *Gunshot*. Eddy ! La dernière" + "\n" +
        "volonté, ça te parle ? Quel idiot." + "\n" + 
        "Allez nettoie moi tout ça ...";
    }

    //sf::String tmp(res);
    //tmp.toUtf8();
    return res;
}

void Missingnumber:: init_transition(sf::RenderWindow &window){
 
    sf::Font font;
    font.loadFromFile("img_pendu/arial.ttf");

    create_sprite(window,0,0,TEXTURE_BACKGROUND2);
    create_sprite(window,(APP_SIZE_X2-640)/2,0,TEXTURE_TRANSITION2);
    create_text(window,font,18,(APP_SIZE_X2-640)/2+90,70,setFinalText(win()));
    create_text(window,font,16,510,505,"Press enter \nto continue...");

}


void Missingnumber::transition(sf::RenderWindow &window){
     sf::Event event;
     std::size_t cpt = 0;

     while(window.isOpen() && cpt < 1){
        while (window.pollEvent(event))
        {
            // Changer de fond
            if (((event.type == sf::Event::KeyPressed)&&(event.key.code == sf::Keyboard::Enter))){
               cpt ++;
               break;
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



