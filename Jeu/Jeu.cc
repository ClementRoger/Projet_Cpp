#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <iostream>

 
#include "Jeu.hh"
#include "Demineur.hh"
#include "pendu.hh"
#include "missingnumber.hh"
#include "Batonnets.hh"
#include "Juste_Prix.hh"

using namespace std;

Jeu :: Jeu() {
	// 1 = facile ~ 2 = difficile ~ 0 = indéfini
	_difficulty = 0;
	_passedGames = 0;
}

void Jeu :: run(){
	sf::RenderWindow window(sf::VideoMode(XWINDOW, YWINDOW), "Livin' Tomorrow");
	bool Intropassed = false;
	while(window.isOpen()) {

		sf::Event event;
	    while (window.pollEvent(event)) {

	        if (event.type == event.Closed) {
	        	window.close();
	        	break;
	        }
		    if (!_passedGames){
		        if (event.type == sf::Event::MouseButtonPressed){
		        	Intropassed = Get_Mouse_Click(window);
		        	break;
		        }
		    }
	    }
	     // Si un niveau : facile ou difficile sélectionné on incrémente cpt pour passer aux minijeux
	    if(Intropassed && !_passedGames){
	    	transition(window,event);
	    	_passedGames ++;
	    }
	    // Si niveau facile
	    if (get_difficulty() == 1){
	    	easy_game(window);
	    }
	    else if (get_difficulty() == 2){
	    	difficult_game(window);
	    }
	    
	    
	    if (!_passedGames){
	    	window.clear();
	    	init_game(window);
			window.display();
	    }
	    
	}
}

void Jeu::easy_game(sf::RenderWindow &window){
	switch (_passedGames){
		case 1: {
			Juste_Prix J1(8, 1, 100);
			J1.display(window);
			check_end(J1,window);
		}
		case 2 : {
			std::fstream inFile("img_pendu/mots_faciles.txt", std::fstream::in);
			Pendu game(inFile,8); 
    		game.display(window);
	    	check_end(game,window);
			break;
		}
		case 3 : {
			Batonnets B1(20,1); //1 easy, 2 difficult
			B1.display(window);
    		check_end(B1,window);
			break;
		}
		case 4 : {
			std::fstream inFile("img_missing/matrices.txt", std::fstream::in);
			Missingnumber game(inFile,3); 
			game.display(window);
			check_end(game,window);
			break;
		}
		
		case 5 : {
			Demineur game(2,8,8); 
    		game.display(window);
    		check_end(game,window);
			break;
		}
		
		default :
			//ajouter la possibilité de rejouer?
			window.close();
			std::cout<<"end"<<std::endl;
			break;
	}
}

void Jeu::difficult_game(sf::RenderWindow &window){
    switch (_passedGames){
    	case 1: {
			Juste_Prix J1(6, 1, 100);
			J1.display(window);
			check_end(J1,window);
		}
		case 2 : {
			std::fstream inFile("img_pendu/mots_difficiles.txt", std::fstream::in);
			Pendu game(inFile,8); 
    		game.display(window);
	    	check_end(game,window);
			break;
		}
		case 3 : {
			Batonnets B1(20,2); //1 easy, 2 difficult
			B1.display(window);
    		check_end(B1,window);
			break;
		}
		case 4 : {
			std::fstream inFile("img_missing/matrices.txt", std::fstream::in);
			Missingnumber game(inFile,1); 
			game.display(window);
			check_end(game,window);
			break;
		}
		case 5 : {
			Demineur game(1,10,8); 
    		game.display(window);
    		check_end(game,window);
			break;
		}
		
		default :
		//ajouter la possibilité  de rejouer?
			window.close();
			std::cout<<"end"<<std::endl;
			break;
	}
}

void Jeu::check_end(MiniJeu& game,sf::RenderWindow &window){
	if(game.win()){
		_passedGames++;
	}
	else {
		window.close();
	}
}

/* Permet de determiner la position de la souris lors du click + de savoir si ce click est dans la grille de jeu */
bool Jeu::Get_Mouse_Click(sf::RenderWindow &window){
	sf::Vector2i position;
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
    std::size_t tmp = test_button_border(position);
    if (tmp > 0){
    	set_difficulty(tmp);
    	return true;
    }
    return false;
}

/* Permet de tester si le click se trouve sur difficile ou facile*/
std::size_t Jeu::test_button_border(const sf::Vector2i position){

    if ( (position.x >= 100)
        && (position.x <= 100 + 960*0.25f)
        && (position.y >= 430)
        && (position.y <= 430 + 480*0.25f )) {
        return 1;
    }

    if ( (position.x >= 450)
        && (position.x <= 450 + 960*0.25f)
        && (position.y >= 430)
        && (position.y <= 430 + 480*0.25f )){

    	return 2;
    }
    
    
    return 0;
}

void Jeu :: init_game(sf::RenderWindow& window) {

	sf::Font font;

	if (!font.loadFromFile("zorque.ttf")) {
        cout << "Erreur de chargement de la police" << endl;
    }

    sf::Sprite Bouton_Facile, Bouton_Difficile;
	sf::Text Texte_Facile("Facile",font,50);
	sf::Text Texte_Difficile("Difficile",font,50);

	sf::Texture bg_texture;
	sf::Sprite bg;
	
	if (!bg_texture.loadFromFile("bg.jpeg")){

    	cout << "Erreur de chargement de l'image de fond" << endl;
	}

	bg.setTexture(bg_texture);
	bg.setScale(1.18,1.48); //Valeur trouvées un peu au pif mdr
	window.draw(bg);

	create_button(window,Bouton_Facile, Texte_Facile, 100, 430);
	create_button(window,Bouton_Difficile, Texte_Difficile, 450, 430);

	sf::Text Texte_Titre("Livin' Tomorrow",font,50);
	Texte_Titre.setCharacterSize(55);
    Texte_Titre.setFillColor(sf::Color(0, 0, 139)); // Du bleu foncé stylé
    Texte_Titre.setStyle(sf::Text::Bold);
    Texte_Titre.setPosition(160, 30);

    window.draw(Texte_Titre);

}

void Jeu :: create_button(sf::RenderWindow& window,sf::Sprite Bouton, sf::Text text, size_t x, size_t y) {

	sf::Texture texture;
	
	if (!texture.loadFromFile("button.png")){ //NOTE A MOI MEME : PNG >>>>>>>>>>> JPEG. JPEG EST LE DIABLE ET CAUSE DES BUGS DE MEEEEEEEEEEEEEEEEEERDE (jsuis grv d'accord jpg ça pu sa daronne)

    	cout << "Erreur de chargement de l'image du bouton" << endl;
	}

	texture.setSmooth(true);
	Bouton.setTexture(texture);
	Bouton.setScale(0.25,0.25);

    text.setCharacterSize(30);
    text.setFillColor(sf::Color(55, 0, 139)); // Du bleu foncé stylé
    text.setStyle(sf::Text::Bold);

    Bouton.setPosition(x,y);
    text.setPosition(x + texture.getSize().x/8 - text.getLocalBounds().width/2, y + texture.getSize().y/8 - text.getLocalBounds().height); //Un peu au pif pour le y (jsp pourquoi y a pas le /2 pour height), le x est logique : le /8 vient de /2 et il faut multiplier par le cofficient de getScale (0.25) donc 1/2 * 1/4 = 1/8

    window.draw(Bouton);
    window.draw(text);
}

/* char (0x82); - é
char (0x85) - à
char (0X8A) - è
*/
std::wstring Jeu::setFinalText(const std::size_t cpt){
    std::wstring res;
    //char a = char(0x85);
    //const char e_1 = char(0x82);
    //const char e_2 = char(0x8A);
    switch (cpt){
    	case 0:
    		res = std::wstring(L"2107. \n\n") +
	        std::wstring(L"Quatorze milliards d\'individus peuplent la Terre\n") + 
	        std::wstring(L"et les ressources commencent à cruellement manquer.\n\n") + 

	        std::wstring(L"Après la publication d\'un article scientifique de \n") + 
	        std::wstring(L"Svetlana Deac et de Clément Roger Jr - qui leur \n") +
	        std::wstring(L"vaudra le prix Nobel de la Paix - démontrant que \n") + 
	        std::wstring(L"l\'humanité courait à sa perte, l\'ONU convoqua en\n") + 
	        std::wstring(L"urgence un conseil de sécurité.  \n\n" ) +

	        std::wstring(L"La décision était prise : il fallait éliminer  \n" ) +
	        std::wstring(L"une grande partie de la population mondiale et, \n") +
	        std::wstring(L"de préférence, les moins utiles au développement \n") + 
	        std::wstring(L"scientifique des Nations.  \n");
    		break;

    	case 1:
    		res = std::wstring(L"\n\nChaque pays a donc eu la responsabilité de créer\n") +
	        std::wstring(L"un test comportant six épreuves que seuls les 5 % \n") +
	        std::wstring(L"les plus intelligents seraient en mesure de réussir. \n" )+
	        std::wstring(L"Ils doivent désormais convoquer chaque citoyen de \n" )+
	        std::wstring(L"plus de 16 ans et leur faire passer ce test.\n\n") +

	        std::wstring(L"En cas d\'échec à l\'une des six épreuves, l\'individu \n") +
	        std::wstring(L"sera exécuté sur le champ ...\n\n") +

	        std::wstring(L"Demain vous fêterez votre seizième anniversaire. \n" )+
	        std::wstring(L"La lettre est arrivée aujourd’hui, vous êtes \n") + 
	        std::wstring(L"attendu demain au Centre de Recherche afin de\n")+
	        std::wstring(L"passer Le Test...");
	        

    		break;

    	case 2:

    		res = std::wstring(L"\n\n\n\n\"Asseyez-vous\" dit le scientifique d\'un ton froid.\n\n") +

	        std::wstring(L"Je pense que vous connaissez les règles : vous \n") +
	        std::wstring(L"allez passer six épreuves par ordre croissant de \n") +
	        std::wstring(L"difficulté, si vous échouez à l\'une d’elle, mon ami \n") +
	        std::wstring(L"Eddy ici présent se chargera de vous éliminer d\'une \n") +

	        std::wstring(L"balle dans la tête. Vous avez de la chance, vous\n") +

	        std::wstring(L"êtes le premier à passer aujourd\'hui, vous ne vous\n") +
	        std::wstring(L"êtes pas assis sur des morceaux de cervelle,\n") +
	        std::wstring(L"dit-il en ricanant.");

    	
	        break;

	    case 3:
    		 res = std::wstring(L"\n\nBien. Commençons.\n\n") +
	         std::wstring(L"Pour la première épreuve je vais penser à un nombre\n") +
	         std::wstring(L"entre 1 et 100 inclus, votre objectif est de retrouver\n") +
	         std::wstring(L"ce nombre en un nombre limité de tentatives.\n") +
	         std::wstring(L"A chacune de vos propositions je ne répondrai que \n") +

	         std::wstring(L"\"C\'est plus\",\"C\'est moins\" ou \"C\'est correct\",") +
	         std::wstring(L"rien d’autre.\n\n") +

	         std::wstring(L"Si à la fin des tentatives autorisés,vous n’avez \n") + 
	         std::wstring(L"pas trouvé le nombre, pan.\n\n") +
	         std::wstring(L"Compris ?"); 

    		break;

    	default :
    		break;
    }


    //std::basic_string<sf::Uint8> tmpbuff1 = res.toUtf8();
    //std::string tmp (tmpbuff1.begin(),tmpbuff1.end());
    //sf::String tmp(res);
    //tmp.toUtf8();
    return res;
}


/* Permet de crée un sprite et de le dessiner sur la fenetre */
void Jeu::create_sprite(sf::RenderWindow &window, const std::size_t x, const std::size_t y, const std::string file){
    sf::Texture texture;
    sf::Sprite sprite;
    texture.loadFromFile(file);
    sprite.setTexture(texture);
    sprite.setPosition(sf::Vector2f(x,y));
    window.draw(sprite);
}

/* Permet de crée un texte et de le dessiner sur la fenetre */
void Jeu::create_text(sf::RenderWindow &window, const sf::Font font, const std::size_t fontSize, const std::size_t x, const std::size_t y, const std::wstring input){
    sf::Text text;
    text.setFont(font);
    text.setString(input);
    text.setCharacterSize(fontSize);
    text.setFillColor(sf::Color::White);
    text.setStyle(sf::Text::Bold);
    text.setPosition(sf::Vector2f(x,y));
    window.draw(text);
}

void Jeu:: init_transition(sf::RenderWindow &window,const std::size_t cpt){

    sf::Font font;
    font.loadFromFile("img_pendu/Type.ttf");

    create_sprite(window,0,0,TEXTURE_TRANSITION1);
    create_text(window,font,20,75,90,setFinalText(cpt));
    create_text(window,font,16,510,505,L"Press enter \nto continue...");

}


void Jeu::transition(sf::RenderWindow &window,sf::Event& event){
     std::size_t cpt = 0;

     while(window.isOpen() && cpt < 4){
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
        init_transition(window,cpt);
        window.display();
     }
    
}