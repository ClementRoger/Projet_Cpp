#include <iostream>
#include "TextEntry.hh"
using namespace std; 

#define SIZE 200

TextEntry :: TextEntry (sf::RenderWindow& window,const size_t x, const size_t y) {

	if (!_font.loadFromFile("images_TextEntry/arial.ttf")) {
        cout<<"Font ERROR. Don't find arial.ttf"<<endl;
    }
  
    _playerInput = "";
    _entrysize = 0;
    _xsize = (size_t)(x-SIZE)/2;
    _ysize = (size_t)(y-30)/2;
    _final = "";
}

TextEntry :: ~TextEntry(){ 
    //std::cout<<"TextEntry destroyed"<<std::endl;

} 

void TextEntry :: init_rectangle(sf::RenderWindow& window,const size_t width, const size_t height, const size_t x, const size_t y)const{

	sf::RectangleShape rectangle(sf::Vector2f(width, height));
    rectangle.setPosition(x,y);

    rectangle.setFillColor(sf::Color(255,255,255)); //Fill with white
    rectangle.setOutlineThickness(2); //Border of two pixels ...
    rectangle.setOutlineColor(sf::Color(0, 0, 0)); // ... in black
    window.draw(rectangle);

}  

void TextEntry :: display_playertext(sf::RenderWindow& window,const string tmp,const size_t pos_x,const size_t pos_y){
	sf::Text playerText(tmp,_font,SIZE);
    playerText.setCharacterSize(24);
    playerText.setPosition(pos_x,pos_y);
    playerText.setFillColor(sf::Color(0, 0, 0));
    playerText.setString(tmp);
    set_entrysize(playerText.getLocalBounds().width);
    window.draw(playerText);

}

void TextEntry :: check_events(sf::RenderWindow& window,sf::Event& event){
	string tmp = get_playerInput();
	std::size_t cpt = 0;

	if ((event.key.code == sf::Keyboard::Enter)){
    	if(!cpt){
    		set_finalInput(tmp);
	    	tmp.clear();
	    	tmp="";
	    	cpt++;
    	}
    }
	else if (event.type == sf::Event::TextEntered) {

		//Si efface un charactère
        if(event.text.unicode == '\b'){
 
            if(tmp != ""){

                tmp.erase(tmp.size() -1, 1);
            }
        }
        else if (get_entrysize() < SIZE-20){
        	
        	tmp += event.text.unicode;
            
        }
    }

    set_playerInput(tmp);
    cpt = 0;

}

 void TextEntry :: display (sf::RenderWindow& window){

    init_rectangle(window,SIZE,30,get_xsize(),get_ysize());
    display_playertext(window,get_playerInput(),get_xsize()+ SIZE/2 - get_entrysize()/2, get_ysize());

 }
