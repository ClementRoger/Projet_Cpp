#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

extern sf::RenderWindow window;

class Jeu {

  public :

    Jeu();
    void init_game();
    void create_button(sf::Sprite Bouton, sf::Text text, size_t x, size_t y);
};