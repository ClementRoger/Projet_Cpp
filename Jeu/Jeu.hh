#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include<fstream>

#include <codecvt>
#include <locale>
#include <cwchar>

#define XWINDOW 800
#define YWINDOW 600


#include "../MiniJeu.hh"


class Jeu {

  public :

    Jeu();
    void run();
    void init_game(sf::RenderWindow& window);
    void create_button(sf::RenderWindow& window,sf::Sprite Bouton, sf::Text text, const size_t x, const size_t y);

    std::size_t test_button_border(const sf::Vector2i position);
    bool Get_Mouse_Click(sf::RenderWindow &window);
    void check_end(MiniJeu& game,sf::RenderWindow &window,sf::Event& event);
    void easy_game(sf::RenderWindow &window,sf::Event& event);
    void difficult_game(sf::RenderWindow &window,sf::Event& event);

    void transition(sf::RenderWindow &window,sf::Event& event);
  	std::wstring setFinalText(const std::size_t cpt);
  	void init_transition(sf::RenderWindow &window,const std::size_t cpt);
  	void create_text(sf::RenderWindow &window, const sf::Font font, const std::size_t fontSize, const std::size_t x, const std::size_t y, const std::wstring input);
  	void create_sprite(sf::RenderWindow &window, const std::size_t x, const std::size_t y, const std::string file);
  

    void init_playagain(sf::RenderWindow &window);
    void playagain(sf::RenderWindow &window,sf::Event& event);
    /* Getters & Setters */
    std::size_t get_difficulty() const { return _difficulty;}
  	void set_difficulty(const std::size_t val){ _difficulty = val; }

  	//friend std::wchar_t operator+(std::wchar_t* res,std::wchar_t* tmp);

	private:
	std::size_t _difficulty;
	std::size_t _passedGames;
  std::size_t _playagain;
};
/*

 inline std::wchar_t operator+(std::wchar_t* res,std::wchar_t* tmp){
  		return wcscat(res,tmp);
 } */