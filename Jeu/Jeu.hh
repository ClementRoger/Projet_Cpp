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
    void init_game(sf::RenderWindow& window)const;
    void create_button(sf::RenderWindow& window,sf::Sprite Bouton, sf::Text text, const size_t x, const size_t y)const;

    std::size_t test_button_border(const sf::Vector2i position)const;
    bool Get_Mouse_Click(sf::RenderWindow &window);
    void check_end(MiniJeu& game,sf::RenderWindow &window,sf::Event& event);
    void easy_game(sf::RenderWindow &window,sf::Event& event);
    void difficult_game(sf::RenderWindow &window,sf::Event& event);

    void transition(sf::RenderWindow &window,sf::Event& event)const;
  	std::wstring setFinalText(const std::size_t cpt)const;
  	void init_transition(sf::RenderWindow &window,const std::size_t cpt)const;
  	void create_text(sf::RenderWindow &window, const sf::Font font, const std::size_t fontSize, const std::size_t x, const std::size_t y, const std::wstring input)const;
  	void create_sprite(sf::RenderWindow &window, const std::size_t x, const std::size_t y, const std::string file)const;
  

    void init_playagain(sf::RenderWindow &window)const;
    void playagain(sf::RenderWindow &window,sf::Event& event);
    /* Getters & Setters */
    std::size_t get_difficulty() const { return _difficulty;}
  	void set_difficulty(const std::size_t val){ _difficulty = val; }

	private:
	std::size_t _difficulty;
	std::size_t _passedGames;
  std::size_t _playagain;
};
