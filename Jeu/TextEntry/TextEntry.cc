#include <iostream>

using namespace std;

TextEntry :: TextEntry (size_t x, size_t y) {

	init_rectangle(140,30,x/2,y);
	


}

TextEntry :: init_rectangle(size_t width, size_t height, size_t x, size_t y) {

	sf::RectangleShape rectangle(sf::Vector2f(width, height));
    rectangle.setPosition(x,y);

    rectangle.setFillColor(sf::Color(255,255,255)); //Fill with white
    rectangle.setOutlineThickness(2); //Border of two pixels ...
    rectangle.setOutlineColor(sf::Color(0, 0, 0)); // ... in black

}    