#pragma once
#include <cstdlib>
#include <iostream>
#include <vector>
#include <time.h>
#include <string>


class Demineur {
 
 public:
 
  Demineur(const size_t count, const size_t bomb, const size_t gridsize); //constructeur par défaut

  ~Demineur();

  void play();

  bool win(const bool flag);

  void affichage(const vector<vector<bool>>matrice);

  void initBomb(vector<vector<int>>&tab,const size_t gridsize);

  void checkBomb(vector<vector<int>>&tab, const size_t gridsize);

  bool checkBool(const vector<vector<bool>>tab);

  void reveal(vector<vector<bool>>&tmp, const vector<vector<int>>tab, const size_t i, const size_t j);

  /* Getters & Setters */
  size_t get_nb_try() const { return _nb_try; }
  void set_nb_try(size_t nb){ _nb_try = nb;}
  size_t get_nb_bomb() const { return _nb_bomb; }
  vector<vector<int>> get_plateau() const{ return _plateau;}
  vector<size_t> get_bomb_x() const{ return _bomb_x;}
  vector<size_t> get_bomb_y() const{ return _bomb_y;}


 private:
  vector<vector<int>>_plateau;
  size_t _nb_try; // nombre d'erreurs possible 
  size_t _nb_bomb;
  vector<size_t> _bomb_x;
  vector<size_t> _bomb_y;

};
