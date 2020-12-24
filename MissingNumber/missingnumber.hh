#pragma once
#include <cstdlib>
#include <iostream>
#include <string>
#include <fstream> 
#include <vector>
#include <time.h>
#include <sstream>

#include "../MiniJeu.hh"

class Missingnumber : public MiniJeu {
 
 public:
 
  Missingnumber(fstream& in,const size_t count); 

  ~Missingnumber();

  void play();

  string get_solution() const { return _solution; }

  vector<vector<string>> get_matrice() const{ return _matrice;}

  void affichage(vector<vector<string>>matrice);

  void transition();

 private:
  vector<vector<string>>_matrice;
  string _solution;

};
