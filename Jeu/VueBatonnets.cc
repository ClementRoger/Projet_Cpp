#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include <vector>
#include <stdexcept>  // std::invalid_argument

#include "Batonnets.hh"
#include "TextEntry.hh"

#define APP_SIZE_X 800
#define APP_SIZE_Y 600

using namespace std;
 
void Batonnets :: display(sf::RenderWindow& window){

	window.clear();
	init_background(window);
	affiche_batonnets(window);
	TextEntry textbar(window,APP_SIZE_X3,APP_SIZE_Y3 + 220);
	window.display();

	while (window.isOpen() && !win() && nb_batonnets > 0) {

		sf::Event event;

        while (window.pollEvent(event)) {

            textbar.check_events(window,event);

            if (event.type == sf::Event::Closed){ 
                window.close();
                break;                
            }

        }

        user_entry = textbar.get_finalInput();

		if(tour) {
			if(check_entry(user_entry)){

				play();
			}
		}

		else {

			play();
			sf::Time delay = sf::milliseconds(1600);
			sf::sleep(delay);
		}	
			
		window.clear();
        init_background(window);
        affiche_batonnets(window);
        textbar.display(window);
        window.display();
	}
    if(win()){
        set_path("sons/missing_number.wav");
    }
    else{
        set_path("sons/batonnets_defaite.wav");
    }
    print_end(win(),window);
}

bool Batonnets :: check_entry(const string entry)const {

	int number;

	try {

		number = stoi(entry, nullptr, 10); //Convertir le string entry en entier (base 10). Si la conversion échoue, soulève une exception invalid argument
	}

	catch (const std::invalid_argument& ia) {

		return false;
	}	


	if(number >= 1 && number <= 3) { //On ne peut prendre que 1, 2 ou 3 bâtonnets

		return true;
	}

	return false;
}

void Batonnets :: init_background(sf::RenderWindow& window)const{

    sf::Texture texture;
    sf::Sprite sprite;
    texture.loadFromFile("images_batonnets/background.jpg");
    sprite.setTexture(texture);
    window.draw(sprite);

    texture.loadFromFile("images_batonnets/tiger.png"); 
    sprite.setTexture(texture);
    sprite.setPosition(sf::Vector2f(10,20));
    sprite.setScale(0.35,0.35);
    window.draw(sprite);
 
    sf::Font font;
    font.loadFromFile("images_batonnets/arial.ttf");
    sf::Text text;
    text.setFont(font);
    text.setString("Test \n 3/6");
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::White);
    text.setStyle(sf::Text::Bold);
    text.setPosition(sf::Vector2f(32,43));
    window.draw(text);

    font.loadFromFile("images_batonnets/lakeshore.ttf");
    text.setFont(font);
    text.setString("Epreuve des Batonnets");
    text.setCharacterSize(65);
    text.setFillColor(sf::Color::Black);
    text.setStyle(sf::Text::Bold);
    text.setPosition(sf::Vector2f(APP_SIZE_X3/4,25));
    window.draw(text);

    string str;

    if(tour) {

    	str = "A vous de jouer";
    }

    else {

    	str = "Au tour d'Eddy de jouer";	
    }

    font.loadFromFile("images_batonnets/Trouble.otf");

	text.setFont(font);
    text.setString(str);
    text.setCharacterSize(37);
    text.setFillColor(sf::Color(0,0,139));
    text.setStyle(sf::Text::Bold);
    text.setPosition(sf::Vector2f(400 - text.getLocalBounds().width/2,155));
    window.draw(text);    

    text.setFont(font);
    text.setString("Press Enter to submit");
    text.setCharacterSize(25);
    text.setFillColor(sf::Color(0,0,0));
    text.setStyle(sf::Text::Bold);
    text.setPosition(sf::Vector2f(400 - text.getLocalBounds().width/2,430));
    window.draw(text);

    texture.loadFromFile("images_batonnets/paint.png");
    texture.setSmooth(true);
    sprite.setTexture(texture);
    sprite.setScale(1.3,0.9);
    sprite.setPosition(sf::Vector2f(APP_SIZE_X3/4 - 47,480));
    window.draw(sprite);

    font.loadFromFile("images_batonnets/arial.ttf");
    text.setString("Batonnets restants : " + std::to_string(nb_batonnets));
    text.setCharacterSize(30);
    text.setFillColor(sf::Color::White);
    text.setStyle(sf::Text::Bold);
    text.setPosition(sf::Vector2f(APP_SIZE_X3/3-30,510));
    window.draw(text);

}

void Batonnets :: affiche_batonnets(sf::RenderWindow& window) const{

	sf::Texture texture;
    sf::Sprite sprite;
    texture.loadFromFile("images_batonnets/metal.jpeg");
    sprite.setTexture(texture);
    sprite.setPosition(30, 220);
    sprite.setScale(1.04,0.3);
    window.draw(sprite);

	for (std::size_t i = 0; i < nb_batonnets; ++i) {

		sf::Texture texture;
    	sf::Sprite sprite;
		
		if (!texture.loadFromFile("images_batonnets/batonnet.png")){

			cout << "Erreur lors du chargement de l'image" << endl;
		}	

		sprite.setTexture(texture);
		sprite.setPosition(700 * i /19, 233);
		sprite.setScale(0.2,0.2);
		window.draw(sprite);
	}
}

void Batonnets :: print_end(const bool winner,sf::RenderWindow &window){

    sf::Time delayTime = sf::milliseconds(2500);

    sf::Texture texture;
    sf::Sprite sprite;

    if (winner) {

        texture.loadFromFile("images_batonnets/you_win.png");
        sprite.setTexture(texture);
    }    

    else {

        texture.loadFromFile("images_batonnets/game_over.png");
        sprite.setTexture(texture);
    }    

    sprite.setScale(0.9,0.9);
    sprite.setPosition(APP_SIZE_X/2 - sprite.getLocalBounds().width/2,APP_SIZE_Y/2 - sprite.getLocalBounds().height/2);
    window.draw(sprite);

    window.display();
    sf::sleep(delayTime);
    transition(window);
}

wstring Batonnets :: setFinalText(const bool win)const{

    std::wstring res;

    if (win){

        res = std::wstring(L"Bravo. Oh ne prenez pas cet air hautain, battre Eddy\n") + 
        std::wstring(L"n’a rien d'impressionnant, et vous n’êtes qu’à la moitié.\n") + 
        std::wstring(L"Les choses sérieuses commencent maintenant, avant c’était\n") +
        std::wstring(L"l’échauffement.\n\nLa quatrième épreuve est très simple - même pour\n")+
        std::wstring(L"vous -. Huit chiffres seront affichés devant vous, à vous\n") + 
        std::wstring(L"de retrouver la logique et de deviner le nombre manquant.\n\n") +
        std::wstring(L"Cela peut paraître facile sur le papier, mais je suis celui qui\n") +
        std::wstring(L"a créé ce test donc attendez-vous à du challenge. Réfléchissez\n") +
        std::wstring(L"bien, vous n’aurez droit qu’à quelques propositions avant\n") +
        std::wstring(L"qu’Eddy vous transforme en viande hachée.\n\n");

    }

    else {

        res = std::wstring(L"Je n’en reviens pas qu’autant de personnes perdent\n") +
        std::wstring(L"contre Eddy à cette épreuve. Avant de devenir ... “nettoyeur”\n") +
        std::wstring(L"ici, il lisait l’avenir dans un potiron dans une foire ambulante,\n") +
        std::wstring(L"ce gars est bête comme une brique. Ne le prends pas mal Eddy, \n") +
        std::wstring(L"tu fais parfaitement ton boulot maintenant. \n\n") +
        std::wstring(L"Allez, élimine le. *Gunshot*\n"); 
    }

    return res;
}

void Batonnets :: init_transition(sf::RenderWindow &window)const{

    sf::Font font;
    font.loadFromFile("images_batonnets/Type.ttf");
    wstring str = L"Press enter \nto continue...";

    sf::Texture texture;
    sf::Sprite sprite;

    texture.loadFromFile("images_batonnets/wall.jpeg");
    sprite.setTexture(texture);
    window.draw(sprite);

    sf::Text text;
    text.setFont(font);
    text.setString(setFinalText(win()));
    text.setCharacterSize(18);
    text.setFillColor(sf::Color::White);
    text.setStyle(sf::Text::Bold);
    text.setPosition(sf::Vector2f((APP_SIZE_X - text.getLocalBounds().width)/2,(APP_SIZE_Y - text.getLocalBounds().height)/2));
    window.draw(text);

    text.setString(str);
    text.setCharacterSize(16);
    text.setFillColor(sf::Color::White);
    text.setStyle(sf::Text::Bold);
    text.setPosition(sf::Vector2f(510,505));
    window.draw(text);
}

