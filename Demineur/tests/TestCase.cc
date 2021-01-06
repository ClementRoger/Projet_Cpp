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
  REQUIRE(m.get_nb_bomb() == 9);
  REQUIRE(m.get_plateau()[4][2] == 2);
  REQUIRE(m.get_plateau()[2][2] == -1);
  for (size_t i = 0; i < m.get_open_tiles().size();i++){
    for (size_t j = 0; j < m.get_open_tiles().size();j++){
      REQUIRE(m.get_open_tiles()[i][j] == false);
    }
  }
}


TEST_CASE("2: Test reveal","[Demineur]"){
  Demineur m(3);
 
  m.reveal(0,3);

  for (size_t i = 0; i < m.get_open_tiles().size();i++){
    for (size_t j = 0; j < m.get_open_tiles().size();j++){
      if( !i ) REQUIRE(m.get_open_tiles()[i][j] == true);
      else REQUIRE(m.get_open_tiles()[i][j] == false);
    }
  }
 
}

TEST_CASE("3: Test checkBomb","[Demineur]" )
{

  Demineur m(3); 
  std::vector<std::vector<int>>temp {{0, 0, 0, 0, 0, 0, 0, 0 },
                                      {0, 0, 0, 0, 0, 0, 0, 0 },
                                      {0, -1, -1, -1, 0, 0, -1, 0} ,
                                      {0, 0, 0, 0, 0, 0, 0, 0 },
                                      {0, -1, 0, 0, 0, 0, 0, 0 },
                                      {0, 0, -1, 0, -1, 0, 0, 0 },
                                      {0, -1, 0, 0, 0, -1, -1, 0 },
                                      {0, 0, 0, 0, 0, 0, 0, 0},
                                      };

  m.checkBomb(temp, temp.size());

  for (size_t i = 0; i < m.get_open_tiles().size();i++){
      for (size_t j = 0; j < m.get_open_tiles().size();j++){
        REQUIRE( m.get_plateau()[i][j] == temp[i][j]);
      }
  }

}


TEST_CASE("4: Test play and checkbool","[Demineur]" )
{
  Demineur m(3);
  REQUIRE(m.checkBool(m.get_open_tiles()) == false);

  m.set_position((0*IMG_SIZE + (APP_SIZE_X-(IMG_SIZE*m.get_plateau().size()))/2),(0*IMG_SIZE + (APP_SIZE_Y-(IMG_SIZE*m.get_plateau().size()))/2));
  m.play();

  REQUIRE(m.checkBool(m.get_open_tiles()) == false);

  m.set_position((3*IMG_SIZE + (APP_SIZE_X-(IMG_SIZE*m.get_plateau().size()))/2),(4*IMG_SIZE + (APP_SIZE_Y-(IMG_SIZE*m.get_plateau().size()))/2));
  m.play();
  REQUIRE(m.checkBool(m.get_open_tiles()) == false);
 
  for (size_t i = 0; i < m.get_open_tiles().size();i++){
    for (size_t j = 0; j < m.get_open_tiles().size();j++){
      m.set_position((i*IMG_SIZE + (APP_SIZE_X-(IMG_SIZE*m.get_plateau().size()))/2),(j*IMG_SIZE + (APP_SIZE_Y-(IMG_SIZE*m.get_plateau().size()))/2));
      m.play();
    }
  } 

  REQUIRE(m.checkBool(m.get_open_tiles()) == true);
}
