// Let Catch provide main():
#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <list>
#include "missingnumber.hh"
#include "TextEntry.hh"
#include "MiniJeu.hh"
#include "MiniJeuAvecSolution.hh"
using namespace std;


TEST_CASE("1: Missingnumber create","[missingnumber]"){
  Missingnumber m(3);
  REQUIRE(m.get_nb_try() == 3);
  REQUIRE(m.get_solution() == "5");
  REQUIRE(m.get_user_entry() == "");
  REQUIRE(m.get_matrice()[0][0] == "3");
  REQUIRE(m.get_matrice()[1][1] == "?");
}


TEST_CASE("2: Test validity","[missingnumber]"){
  Missingnumber m(3);
  m.set_user_entry("a");
  REQUIRE(m.check_entry(m.get_user_entry()) == false);
  m.set_user_entry("-");
  REQUIRE(m.check_entry(m.get_user_entry()) == false);
  m.set_user_entry("W");
  REQUIRE(m.check_entry(m.get_user_entry()) == false);
  m.set_user_entry("3");
  REQUIRE(m.check_entry(m.get_user_entry()) == true);
}


TEST_CASE("3: Test nombre d'essai restants","[missingnumber]" )
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


TEST_CASE("4: Test victoire","[missingnumber]" )
{
  Missingnumber m(5);
  m.set_user_entry("23");
  m.play();
  REQUIRE(m.win() == false);

  m.set_user_entry("5");
  m.play();
  REQUIRE(m.win() == true);
  
}
