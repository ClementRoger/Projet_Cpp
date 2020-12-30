#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include<fstream>

#define XWINDOW 800
#define YWINDOW 600

#include "../MiniJeu.hh"

//extern sf::RenderWindow window;

class Jeu {

  public :

    Jeu();
    void run();
    void init_game(sf::RenderWindow& window);
    void create_button(sf::RenderWindow& window,sf::Sprite Bouton, sf::Text text, size_t x, size_t y);

    std::size_t test_button_border(const sf::Vector2i position);
    bool Get_Mouse_Click(sf::RenderWindow &window);
    void check_end(MiniJeu& game,sf::RenderWindow &window,std::size_t& cpt);
    void easy_game(sf::RenderWindow &window,std::size_t& cpt);
    void difficult_game(sf::RenderWindow &window,std::size_t& cpt);

    void transition(sf::RenderWindow &window,sf::Event& event);
  	std::string setFinalText(const std::size_t cpt);
  	void init_transition(sf::RenderWindow &window,const std::size_t cpt);
  	void create_text(sf::RenderWindow &window, const sf::Font font, const std::size_t fontSize, const std::size_t x, const std::size_t y, const std::string input);
  	void create_sprite(sf::RenderWindow &window, const std::size_t x, const std::size_t y, const std::string file);
  

    /* Getters & Setters */
    std::size_t get_difficulty() const { return _difficulty;}
  	void set_difficulty(const std::size_t val){ _difficulty = val; }

	private:
	std::size_t _difficulty;
	std::size_t _passedGames;
};