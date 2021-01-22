#pragma once
#include <cstdlib>
#include <iostream>
#include <string>
#include <fstream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include"Itransition.hh"

class MiniJeu: public Itransition{

public:

  MiniJeu(std::size_t nb_try, bool victory){
    _victory = victory;
    _nb_try = nb_try;
  }

  virtual ~MiniJeu(){};

  virtual void play() = 0;
  virtual void display(sf::RenderWindow &window) = 0;
  virtual void init_background(sf::RenderWindow& window)const = 0;
  virtual void print_end(const bool winner,sf::RenderWindow &window) = 0;
  
  virtual std::wstring setFinalText(const bool win)const = 0;
  virtual void init_transition(sf::RenderWindow &window)const = 0;
  
/* Réalise la transition */
  void transition(sf::RenderWindow &window)const{
    sf::Event event;
    bool cpt = 0;

    sf::SoundBuffer Buffer;
    Buffer.loadFromFile(sound_path);
    sf::Sound sound;
    sound.setBuffer(Buffer);
    sound.play();

     while(window.isOpen() && !cpt){
        while (window.pollEvent(event))
        {
            // Changer de fond
            if (((event.type == sf::Event::KeyPressed)&&(event.key.code == sf::Keyboard::Enter))){
               cpt = true ;
            }
            if (event.type == sf::Event::Closed){ 
              window.close();
              break;                
            }

        } 
        window.clear();
        init_transition(window);
        window.display();
     }
    
  }

  /* Getters & Setters */
  size_t get_nb_try() const { return _nb_try; }
  void set_nb_try(const size_t nb){ _nb_try = nb;}
  bool win() const {return _victory;}
  void set_win(const bool flag) {_victory = flag; }
  void set_path(const std::string path){ sound_path = path; }

protected:
  std::size_t _nb_try;
  bool _victory;
  std::string sound_path;

};