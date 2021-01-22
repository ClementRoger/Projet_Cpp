#pragma once
#include <cstdlib>
#include <iostream>
#include <string>
#include <fstream> 
#include <vector>
#include <time.h>
#include <sstream>

#include "TextEntry.hh"

#include "MiniJeu.hh"
#include "MiniJeuAvecSolution.hh"

#define TEXTURE_BACKGROUND1 "img_pendu/background.png"
#define TEXTURE_BACKNAME1 "img_pendu/hangman.png"
#define TEXTURE_NAME1 "img_pendu/title.png"
#define TEXTURE_BACKGAME1 "img_pendu/nb_try.png"
#define TEXTURE_LETTERS1 "img_pendu/paint_bg.png"
#define TEXTURE_WIN1 "img_pendu/you_win.png"
#define TEXTURE_LOSE1 "img_pendu/game_over.png"
#define TEXTURE_TRANSITION1 "img_pendu/wall.jpeg"

#define APP_SIZE_X1 800
#define APP_SIZE_Y1 600


class Pendu : public MiniJeuAvecSolution {
 
 public:
 
  Pendu(std::fstream& in,const std::size_t count); //constructeur par défaut
  Pendu(std::string tmp, const size_t count); //for testcase

  ~Pendu();

  std::size_t find_random(std::fstream& in,std::vector<std::string>& all_lines);
  void play();
  bool check_entry(const std::string entry) const;
  void compare_to_solution(const std::string letter);
  void affichage(std::vector<bool>found_letters);
  bool find_letter(std::string letter,std::vector<bool>&found_letters, const std::size_t taille)const;
  void add_letter(std::vector<std::string>&used_letters,std::string letter)const;

  /* SFML */
  void display(sf::RenderWindow& window);
  void init_background(sf::RenderWindow &window)const;
  void create_text(sf::RenderWindow &window, const sf::Font font, const std::size_t fontSize, const std::size_t x, const std::size_t y, const std::string input)const;
  void create_text(sf::RenderWindow &window, const sf::Font font, const std::size_t fontSize, const std::size_t x, const std::size_t y, const std::wstring input)const;
  void create_sprite(sf::RenderWindow &window, const std::size_t x, const std::size_t y, const std::string file)const;
  void print_end(const bool winner,sf::RenderWindow &window);
  void print_word(sf::RenderWindow &window)const;
  void print_used_letters(sf::RenderWindow &window)const;
  void print_game( sf::RenderWindow &window)const;

  std::wstring setFinalText(const bool win)const;
  void init_transition(sf::RenderWindow &window)const;

  /* Getters & Setters */

  std::vector<std::string>  get_used_letters() const { return _used_letters; }
  std::vector<bool>  get_found_letters() const { return _found_letters; }

  void  set_used_letters(const std::vector<std::string>tmp) { _used_letters=tmp; }
  void  set_found_letters(const std::vector<bool>tmp) { _found_letters=tmp; }

  /* Overload operator */
  friend std::ostream& operator<<(std::ostream& in, std::vector<std::string>&used_letters);

 private:

  std::vector<std::string> _used_letters;
  std::vector<bool> _found_letters;

};

inline std::ostream& operator<<(std::ostream& in, std::vector<std::string>&used_letters){

  	in<<"Vous avez utilisé les lettres suivantes :"<<std::endl;
    std::vector<std::string>::iterator  iter ;
    for( iter  = used_letters.begin() ;iter  !=  used_letters.end();  ++iter )
    {
        in<<*iter<<" ";
        
    } 
    in<<std::endl;
    return in;
 }