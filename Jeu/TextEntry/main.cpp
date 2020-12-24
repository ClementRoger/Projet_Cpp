
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

int main() {

    sf::RenderWindow window(sf::VideoMode(1200, 600), "Projet C++");

    sf::Font font;

    sf::Event event;
    std::string playerInput;
    
    sf::RectangleShape rectangle(sf::Vector2f(140, 30));
    rectangle.setPosition(600,300);
    rectangle.setFillColor(sf::Color(255,255,255));
    rectangle.setOutlineThickness(2);
    rectangle.setOutlineColor(sf::Color(0, 0, 0));

    if (!font.loadFromFile("arial.ttf")) {
        return -1;
    }

    sf::Text playerText("",font,50);
    playerText.setCharacterSize(24);
    playerText.setPosition(600,300);
    playerText.setFillColor(sf::Color(0, 0, 0));

    window.draw(rectangle);
    window.draw(playerText);

    while (window.isOpen()) {

        while(window.pollEvent(event)) {

            if (event.type == sf::Event::TextEntered) {

                if(event.text.unicode == '\b'){

                    if(playerInput != ""){

                        playerInput.erase(playerInput.size() -1, 1);
                    }
                }

                else if (playerText.getLocalBounds().width < 120){

                    playerInput += event.text.unicode;
                }
                               
                playerText.setString(playerInput);
                playerText.setPosition(600 + 140/2 - playerText.getLocalBounds().width/2, 300);
            }

            else if (event.type == sf::Event::Closed) {
                window.close();
            }

            else if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Enter)){
                continue;
            }
        }  

    window.clear(sf::Color::White);
    window.draw(rectangle);
    window.draw(playerText);
    window.display();    

    }
    
    return 0;
}    