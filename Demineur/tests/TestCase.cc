// Let Catch provide main():
#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <list>
#include "Demineur.hh"
#include "../../MiniJeu.hh"

using namespace std;


TEST_CASE("1: Demineur create","[Demineur]"){
  Demineur m(3);
  REQUIRE(m.get_nb_try() == 3);
  REQUIRE(m.get_nb_bomb() == 8);
  REQUIRE(m.get_plateau()[4][2] == 3);
  REQUIRE(m.get_plateau()[2][2] == -1);
  for (size_t i = 0; i < m.get_open_tiles().size();i++){
    for (size_t j = 0; j < m.get_open_tiles().size();j++){
      REQUIRE(m.get_open_tiles()[i][j] == false);
    }
  }
}

/*
TEST_CASE("2: Test reveal","[Demineur]"){
  //(APP_SIZE_X-(IMG_SIZE*get_plateau().size()))/2)/IMG_SIZE

  Demineur m(3);
 
}


TEST_CASE("3: Test nombre d'essai restants","[Demineur]" )
{
  Missingnumber m(5);
  m.set_user_entry("0");
  m.play();
  REQUIRE(m.get_nb_try() == 4);

  m.set_user_entry("a");
  m.play();
  REQUIRE(m.get_nb_try() == 4);
  
  m.set_user_entry("32");
  m.play();
  REQUIRE(m.get_nb_try() == 3);
}


TEST_CASE("4: Test victoire","[Demineur]" )
{
  Missingnumber m(5);
  m.set_user_entry("23");
  m.play();
  REQUIRE(m.win() == false);

  m.set_user_entry("5");
  m.play();
  REQUIRE(m.win() == true);
  
}*/
