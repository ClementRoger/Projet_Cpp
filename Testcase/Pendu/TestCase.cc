// Let Catch provide main():
#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <list>
#include "pendu.hh"
#include "TextEntry.hh"
#include "MiniJeu.hh"
#include "MiniJeuAvecSolution.hh"
using namespace std;


TEST_CASE("1: Pendu create","[pendu]"){
  Pendu m("youtube",8);
  REQUIRE(m.get_nb_try() == 8);
  REQUIRE(m.get_solution() == "youtube");
  REQUIRE(m.get_user_entry() == "");
  REQUIRE(m.get_found_letters()[0] == 1);
  REQUIRE(m.get_found_letters()[1] == 0);
}


TEST_CASE("2: Test validity","[pendu]"){
  Pendu m("youtube",8);
  m.set_user_entry("5");
  REQUIRE(m.check_entry(m.get_user_entry()) == false);
  m.set_user_entry("-");
  REQUIRE(m.check_entry(m.get_user_entry()) == false);
  m.set_user_entry("A");
  REQUIRE(m.check_entry(m.get_user_entry()) == true);
  m.set_user_entry("T");
  REQUIRE(m.check_entry(m.get_user_entry()) == true);
}


TEST_CASE("3: Test lettre trouvée","[pendu]" )
{
  Pendu m("YOUTUBE",8);
  m.set_user_entry("O");
  m.play();
  REQUIRE(m.get_found_letters()[1] == 1);
  m.set_user_entry("U");
  m.play();
  REQUIRE(m.get_found_letters()[2] == 1);
  REQUIRE(m.get_found_letters()[3] == 0);
  REQUIRE(m.get_found_letters()[4] == 1);
}


TEST_CASE("4: Test nombre d'essai restants","[pendu]" )
{
  Pendu m("YOUTUBE",8);
  m.set_user_entry("O");
  m.play();
  REQUIRE(m.get_nb_try() == 8);

  m.set_user_entry("z");
  m.play();
  REQUIRE(m.get_nb_try() == 7);
  
  m.set_user_entry("5");
  m.play();
  REQUIRE(m.get_nb_try() == 7);
}

TEST_CASE("5: Test victoire","[pendu]" )
{
  Pendu m("YOUTUBE",8);
  m.set_user_entry("O");
  m.play();
  REQUIRE(m.win() == false);

  m.set_user_entry("YOUTUBE");
  m.play();
  REQUIRE(m.win() == true);
  
}
