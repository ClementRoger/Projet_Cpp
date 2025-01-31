#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <iostream>

 
#include "Jeu.hh"
#include "Demineur.hh"
#include "pendu.hh"
#include "missingnumber.hh"
#include "Batonnets.hh"
#include "Juste_Prix.hh"
#include "Taquin.hh"

#define NB_TRY_JP_EASY 8
#define NB_TRY_JP_DIFFICULT 6
#define NMIN 1
#define NMAX 100
#define NB_TRY_PENDU_EASY 6
#define NB_TRY_PENDU_DIFFICULT 8
#define NB_BATONNETS 20
#define EASY 1
#define DIFFICULT 2
#define NB_TRY_MISSING_NUMBER_EASY 3
#define NB_TRY_MISSING_NUMBER_DIFFICULT 1
#define NB_TRY_DEMINEUR_EASY 3
#define NB_TRY_DEMINEUR_DIFFICULT 1
#define NB_BOMBS_EASY 8
#define NB_BOMBS_DIFFICULT 10
#define DEMINEUR_GRID_SIZE 8
#define NB_TRY_TAQUIN_EASY 150
#define NB_TRY_TAQUIN_DIFFICULT 100 

using namespace std;

Jeu :: Jeu() {
	// 1 = facile ~ 2 = difficile ~ 0 = indéfini
	_difficulty = 0;
	_passedGames = 0;
	_playagain = 0;
}

/* Boucle de jeu */
void Jeu :: run(){

	sf::RenderWindow window(sf::VideoMode(XWINDOW, YWINDOW), "Livin' Tomorrow");
	bool Intropassed = false;
	sf::SoundBuffer Buffer1, Buffer2;
	if (!Buffer1.loadFromFile("sons/menu_sound.wav")){
    	cout << "Erreur de chargement du son (menu_sound.wav)" << endl;
	}
	if(!Buffer2.loadFromFile("sons/background_soundtrack.wav")){
		cout << "Erreur de chargement du son (background_soundtrack.wav)" << endl;
	}
	sf::Sound menu_sound, background_sound;
	menu_sound.setBuffer(Buffer1);
	background_sound.setBuffer(Buffer2);
	menu_sound.setLoop(true); //Quand se termine, recommence au début
	background_sound.setLoop(true);
	background_sound.setVolume(20);
	menu_sound.play();

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
		        	_playagain = 0;
		        	menu_sound.stop();
		        	background_sound.play();
		        	break;
		        }
		    }
	    }
	     // Si un niveau : facile ou difficile sélectionné on incrémente cpt pour passer aux minijeux
	    if(Intropassed && !_passedGames){
	    	transition(window);
	    	_passedGames ++;
	    	Intropassed = false;
	    }
	    // Si niveau facile
	    if (get_difficulty() == 1){
	    	easy_game(window);
	    }
	    // Si niveau difficile 
	    else if (get_difficulty() == 2){
	    	difficult_game(window);
	    }
	    // On affiche seulement si on est à l'intro
	    if (!_passedGames){
	    	window.clear();
	    	init_game(window);
			window.display();
	    }

	    if(_playagain) {
	    	background_sound.stop();
	    	menu_sound.play();
	    	_playagain = 0;
	    }
	}
}

/* Jeux en niveau facile */
void Jeu::easy_game(sf::RenderWindow &window){

	switch (_passedGames){

		case 1: {
			Juste_Prix J1(NB_TRY_JP_EASY, NMIN, NMAX);
			J1.display(window);
			check_end(J1,window);
			break;
		}
		case 2 : {
			std::fstream inFile("img_pendu/mots_faciles.txt", std::fstream::in);
			Pendu games(inFile,NB_TRY_PENDU_EASY); 
    		games.display(window);
	    	check_end(games,window);
			break;
		}
		case 3 : {
			Batonnets B1(NB_BATONNETS,EASY);
			B1.display(window);
    		check_end(B1,window);
			break;
		}
		case 4 : {
			std::fstream inFile("img_missing/matrices.txt", std::fstream::in);
			Missingnumber game(inFile,NB_TRY_MISSING_NUMBER_EASY); 
			game.display(window);
			check_end(game,window);
			break;
		}
		case 5 : {
			Demineur game(NB_TRY_DEMINEUR_EASY,NB_BOMBS_EASY,DEMINEUR_GRID_SIZE); 
    		game.display(window);
    		check_end(game,window);
			break;
		}
		case 6 : {
			Taquin T1(NB_TRY_TAQUIN_EASY);
			T1.display(window);
			check_end(T1,window);
			break;
		}
		
		default :
			playagain(window);
			break;
	}
}

/* Jeux en niveau difficile */
void Jeu::difficult_game(sf::RenderWindow &window){
    switch (_passedGames){
    	case 1: {
			Juste_Prix J1(NB_TRY_JP_DIFFICULT, NMIN, NMAX);
			J1.display(window);
			check_end(J1,window);
			break;
		}
		case 2 : {
			std::fstream inFile("img_pendu/mots_difficiles.txt", std::fstream::in);
			Pendu games(inFile,NB_TRY_PENDU_DIFFICULT); 
    		games.display(window);
	    	check_end(games,window);
			break;
		}
		case 3 : {
			Batonnets B1(NB_BATONNETS,DIFFICULT);
			B1.display(window);
    		check_end(B1,window);
			break;
		}
		case 4 : {
			std::fstream inFile("img_missing/matrices.txt", std::fstream::in);
			Missingnumber game(inFile,NB_TRY_MISSING_NUMBER_DIFFICULT); 
			game.display(window);
			check_end(game,window);
			break;
		}
		case 5 : {
			Demineur game(NB_TRY_DEMINEUR_DIFFICULT,NB_BOMBS_DIFFICULT,DEMINEUR_GRID_SIZE); 
    		game.display(window);
    		check_end(game,window);
			break;
		}
		case 6 : {
			Taquin T1(NB_TRY_TAQUIN_DIFFICULT);
			T1.display(window);
			check_end(T1,window);
			break;
		}
		default :
			playagain(window);
			break;
	}
}

/* Permet d'initialiser la fenetre pour proposer au joueur de rejouer' */
void Jeu::init_playagain(sf::RenderWindow &window)const{
	create_sprite(window,0,0,TEXTURE_TRANSITION1);
	sf::Font font;

	if (!font.loadFromFile("images_Jeu/zorque.ttf")) {
        cout << "Erreur de chargement de la police" << endl;
    }
    sf::Sprite Bouton_Facile, Bouton_Difficile;
	sf::Text Texte_Facile("Rejouer",font,50);
	sf::Text Texte_Difficile("Terminer",font,50);
	create_button(window,Bouton_Facile, Texte_Facile, 100, 430);
	create_button(window,Bouton_Difficile, Texte_Difficile, 450, 430);
    create_text(window,font,50,200,250,L"Play Again?");
}

/* Permet de proposer au joeur de rejouer. On teste sur quel bouton il a cliqué et on réalise l'action correspondantes */
void Jeu::playagain (sf::RenderWindow &window){
	sf::Event event;
	bool passed = false;
	while (window.isOpen() && !_playagain){
		
		while (window.pollEvent(event)) {
				if (event.type == sf::Event::MouseButtonPressed){
	        	passed = Get_Mouse_Click(window);
	        	break;
			}
			
	        if (event.type == event.Closed) {
	        	window.close();
	        	break;
	        } 
	    }
		if (passed && _playagain == 1){
			_passedGames = 0;
			_difficulty = 0;
		}
		if(passed && _playagain == 2){
			window.close();
		}
		window.clear();
		init_playagain(window);
		window.display();
	}
	
}

/* Permet de check la fin du jeu. Si game over, le jeu demande au joueur si il veut rejouer*/
void Jeu::check_end(MiniJeu& game,sf::RenderWindow &window){
	if(game.win()){
		_passedGames++;
	}
	else {
		playagain(window);
	}
}

/* Permet de determiner la position de la souris lors du click + de savoir si ce click est dans la grille de jeu */
bool Jeu::Get_Mouse_Click(sf::RenderWindow &window){
	sf::Vector2i position;
    static bool pressed=false;
    if (pressed) pressed = false;

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
    
    std::size_t tmp = test_button_border(position);
    if (tmp > 0){
    	if(!_passedGames) set_difficulty(tmp); 
    	else _playagain = tmp; 
    	return true;
    }
    return false;
}

/* Permet de tester si le click se trouve sur difficile ou facile*/
std::size_t Jeu::test_button_border(const sf::Vector2i position)const{

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


/* Permet d'initialiser la fenetre de début du jeu' */
void Jeu :: init_game(sf::RenderWindow& window)const {

	sf::Font font;

	if (!font.loadFromFile("images_Jeu/zorque.ttf")) {
        cout << "Erreur de chargement de la police" << endl;
    }

    sf::Sprite Bouton_Facile, Bouton_Difficile;
	sf::Text Texte_Facile("Facile",font,50);
	sf::Text Texte_Difficile("Difficile",font,50);

	sf::Texture bg_texture;
	sf::Sprite bg;
	
	if (!bg_texture.loadFromFile("images_Jeu/bg.jpeg")){

    	cout << "Erreur de chargement de l'image de fond" << endl;
	}

	bg.setTexture(bg_texture);
	bg.setScale(1.18,1.48); 
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

/* Permet de créer un bouton et de le dessiner sur la fenetre */
void Jeu :: create_button(sf::RenderWindow& window,sf::Sprite Bouton, sf::Text text, const size_t x, const size_t y)const {
	sf::Texture texture;
	if (!texture.loadFromFile("images_Jeu/button.png")){ 

    	cout << "Erreur de chargement de l'image du bouton" << endl;
	}
	texture.setSmooth(true);
	Bouton.setTexture(texture);
	Bouton.setScale(0.25,0.25);
    text.setCharacterSize(30);
    text.setFillColor(sf::Color(55, 0, 139)); // Du bleu foncé stylé
    text.setStyle(sf::Text::Bold);
    Bouton.setPosition(x,y);
    text.setPosition(Bouton.getPosition().x + texture.getSize().x/8 - text.getLocalBounds().width/2, Bouton.getPosition().y + texture.getSize().y/8 - text.getLocalBounds().height); //le /8 vient de /2 et il faut multiplier par le cofficient de getScale (0.25) donc 1/2 * 1/4 = 1/8
    window.draw(Bouton);
    window.draw(text);
}


/* Permet de créer un sprite et de le dessiner sur la fenetre */
void Jeu::create_sprite(sf::RenderWindow &window, const std::size_t x, const std::size_t y, const std::string file)const{
    sf::Texture texture;
    sf::Sprite sprite;
    texture.loadFromFile(file);
    sprite.setTexture(texture);
    sprite.setPosition(sf::Vector2f(x,y));
    window.draw(sprite);
}

/* Permet de créer un texte et de le dessiner sur la fenetre */
void Jeu::create_text(sf::RenderWindow &window, const sf::Font font, const std::size_t fontSize, const std::size_t x, const std::size_t y, const std::wstring input)const{
    sf::Text text;
    text.setFont(font);
    text.setString(input);
    text.setCharacterSize(fontSize);
    text.setFillColor(sf::Color::White);
    text.setStyle(sf::Text::Bold);
    text.setPosition(sf::Vector2f(x,y));
    window.draw(text);
}

/* Renvoie le message de transition */
std::wstring Jeu::setFinalText(const std::size_t cpt)const{
    std::wstring res;

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

    return res;
}

/* Affiche la transition */
void Jeu:: init_transition(sf::RenderWindow &window,const std::size_t cpt)const{
    sf::Font font;
    font.loadFromFile("img_pendu/Type.ttf");
    create_sprite(window,0,0,TEXTURE_TRANSITION1);
    create_text(window,font,20,75,90,setFinalText(cpt));
    create_text(window,font,16,510,505,L"Press enter \nto continue...");
}

/* Réalise la transition */
void Jeu::transition(sf::RenderWindow &window)const{
	sf::Event event;
    std::size_t cpt = 0;
    sf::SoundBuffer Buffer;
	sf::Sound sound;

    int flag = 0;

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
            if(cpt == 0 && flag == 0){
				Buffer.loadFromFile("sons/intro1.wav");
				sound.setBuffer(Buffer);
				sound.play();
				flag++;
            }
            if(cpt == 1 && flag == 1){
            	Buffer.loadFromFile("sons/intro2.wav");
				sound.setBuffer(Buffer);
				sound.play();
				flag++;
            }
            if(cpt == 2 && flag == 2){
            	Buffer.loadFromFile("sons/intro3.wav");
				sound.setBuffer(Buffer);
				sound.play();
				flag++;
            }
            if(cpt == 3 && flag == 3){
            	Buffer.loadFromFile("sons/juste_prix.wav");
				sound.setBuffer(Buffer);
				sound.play();
				flag++;
            }
        } 
        window.clear();
        init_transition(window,cpt);
        window.display();
    }
    
}