#define CATCH_CONFIG_MAIN

#include <iostream>
#include <fstream>

#include "Batonnets.hh"
#include "catch.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

using namespace std;

#define NB_BATONNETS 20


Batonnets B1(NB_BATONNETS,2); //1 easy, 2 difficult
	
TEST_CASE("1 : Test du check_entry") {

	REQUIRE(B1.check_entry("4") == false);
	REQUIRE(B1.check_entry("aze") == false);
	REQUIRE(B1.check_entry("-1") == false);
	REQUIRE(B1.check_entry("101") == false);
	REQUIRE(B1.check_entry("0") == false);
	REQUIRE(B1.check_entry("$") == false);
	REQUIRE(B1.check_entry("1") == true);
	REQUIRE(B1.check_entry("2") == true);
	REQUIRE(B1.check_entry("3") == true);
}

TEST_CASE("2 : Test du tour de l'utilisateur") {

	REQUIRE(B1.get_nb_batonnets() == NB_BATONNETS);

	REQUIRE(B1.get_tour() == true);
	B1.set_user_entry("3");
	B1.play();

	REQUIRE(B1.get_nb_batonnets() == NB_BATONNETS - B1.get_last_move());
}	

TEST_CASE("3 : Test du tour de l'IA") {	

	REQUIRE(B1.get_tour() == false);
	B1.play();

	REQUIRE(B1.get_nb_batonnets() == NB_BATONNETS - B1.get_last_move());
	REQUIRE(B1.get_tour() == true);
}
