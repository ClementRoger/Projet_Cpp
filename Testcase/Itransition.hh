#pragma once
#include <cstdlib>
#include <iostream>
#include <SFML/Graphics.hpp>

// Interface

class Itransition{

public:

  virtual void transition(sf::RenderWindow &window)const = 0;


};
