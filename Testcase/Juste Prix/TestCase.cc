#define CATCH_CONFIG_MAIN

#include <iostream>
#include <fstream>

#include "Juste_Prix.hh"
#include "catch.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

#define NB_TENTATIVES 7
#define Nmin 1
#define Nmax 100
#define APP_SIZE_X 800
#define APP_SIZE_Y 600

using namespace std;

Juste_Prix J1(NB_TENTATIVES, 42);

TEST_CASE("1 : Test du check_entry") {

	REQUIRE(J1.check_entry("40") == true);
	REQUIRE(J1.check_entry("aze") == false);
	REQUIRE(J1.check_entry("-1") == false);
	REQUIRE(J1.check_entry("101") == false);
	REQUIRE(J1.check_entry("0") == false);
	REQUIRE(J1.check_entry("$") == false);
}

TEST_CASE("2 : Test du +") {

	J1.set_number(30); 
	J1.play();
	REQUIRE(J1.get_result() == "C'est plus");
	REQUIRE(J1.get_nb_try() == NB_TENTATIVES - 1);
	REQUIRE(J1.win() == false);
}	

TEST_CASE("3 : Test du -") {

	J1.set_number(60); 
	J1.play();
	REQUIRE(J1.get_result() == "C'est moins");
	REQUIRE(J1.get_nb_try() == NB_TENTATIVES - 2);
	REQUIRE(J1.win() == false);
}

TEST_CASE("4 : Test de la victoire") {

	J1.set_number(42); 
	J1.play();
	REQUIRE(J1.get_result() == L"C'est gagné");
	REQUIRE(J1.win() == true);
	REQUIRE(J1.get_nb_try() == NB_TENTATIVES - 3);
}
