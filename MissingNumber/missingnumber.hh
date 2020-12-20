#pragma once
#include <cstdlib>
#include <iostream>
#include <string>
#include <fstream> 
#include <vector>
#include <time.h>
#include <sstream>


class Missingnumber {
 
 public:
 
  Missingnumber(fstream& in,const size_t count); //constructeur par défaut

  ~Missingnumber();

  void play();

  bool win(bool flag);

  string get_solution() const { return _solution; }

  size_t get_nb_try() const { return _nb_try; }

  vector<vector<string>> get_matrice() const{ return _matrice;}

  void set_nb_try(size_t nb){ _nb_try = nb;}

  void affichage(vector<vector<string>>matrice);

 private:
  vector<vector<string>>_matrice;
 	string _solution;
 	size_t _nb_try;

};
