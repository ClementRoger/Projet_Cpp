#pragma once
#include <cstdlib>
#include <iostream>
#include <string>
#include <fstream> 
#include <vector>
#include <time.h>
#include <sstream>

#include "TextEntry.hh"

#include "../MiniJeu.hh"

#define TEXTURE_BACKGROUND1 "img_pendu/background.png"
#define TEXTURE_BACKNAME1 "img_pendu/hangman.png"
#define TEXTURE_NAME1 "img_pendu/title.png"
#define TEXTURE_BACKGAME1 "img_pendu/nb_try.png"
#define TEXTURE_LETTERS1 "img_pendu/tab.png"
#define TEXTURE_WIN1 "img_pendu/you_win.png"
#define TEXTURE_LOSE1 "img_pendu/game_over.png"

#define APP_SIZE_X1 800
#define APP_SIZE_Y1 600


class Pendu : public MiniJeu {
 
 public:
 
  Pendu(std::fstream& in,const std::size_t count); //constructeur par défaut

  ~Pendu();

  void play();
  bool validity_test(const std::string tmp);
  void affichage(std::vector<std::size_t>found_letters);
  bool find_letter(std::string letter,std::vector<std::size_t>&found_letters, const std::size_t taille);
  void add_letter(std::vector<std::string>&used_letters,std::string letter);

  /* SFML */
  void display(sf::RenderWindow& window);
  void init_background(sf::RenderWindow &window);
  void print_end(bool winner,sf::RenderWindow &window);
  void print_word(sf::RenderWindow &window);
  void print_used_letters(sf::RenderWindow &window);
  void print_game( sf::RenderWindow &window );

  void transition();

  /* Getters & Setters */

  std::string get_mistery() const { return _mistery; }
  std::string get_user_entry() const { return _user_entry; }
  std::vector<std::string>  get_used_letters() const { return _used_letters; }
  std::vector<std::size_t>  get_found_letters() const { return _found_letters; }

  void  set_user_entry(const std::string tmp) { _user_entry = tmp; }
  void  set_used_letters(const std::vector<std::string>tmp) { _used_letters=tmp; }
  void  set_found_letters(const std::vector<std::size_t>tmp) { _found_letters=tmp; }

  friend std::ostream& operator<<(std::ostream& in, std::vector<std::string>&used_letters);

 private:
 	std::string _mistery;
  std::string _user_entry;
  std::vector<std::string> _used_letters;
  std::vector<std::size_t> _found_letters;

};

inline std::ostream& operator<<(std::ostream& in, std::vector<std::string>&used_letters){
  	in<<"Vous avez utiliser les lettres suivantes :"<<std::endl;
    std::vector<std::string>::iterator  iter ;
    for( iter  = used_letters.begin() ;iter  !=  used_letters.end();  ++iter )
    {
        in<<*iter<<" ";
        
    } 
    in<<std::endl;
    return in;
 }