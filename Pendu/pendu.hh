#pragma once
#include <cstdlib>
#include <iostream>
#include <string>
#include <fstream> 
#include <vector>
#include <time.h>
#include <sstream>

#include "../MiniJeu.hh"

class Pendu : public MiniJeu {
 
 public:
 
  Pendu(fstream& in,const size_t count); //constructeur par défaut

  ~Pendu();

  void play();

  //bool win(const bool flag);

  bool validity_test(const string tmp);

  string get_mistery() const { return _mistery; }

  void affichage(vector<size_t>found_letters);

  bool find_letter(string letter,vector<size_t>&found_letters, const size_t taille);

  void transition();

  friend ostream& operator<<(ostream& in, vector<string>&used_letters);

 private:
 	string _mistery;

};

inline ostream& operator<<(ostream& in, vector<string>&used_letters){
  	in<<"Vous avez utiliser les lettres suivantes :"<<endl;
    vector<string>::iterator  iter ;
    for( iter  = used_letters.begin() ;iter  !=  used_letters.end();  ++iter )
    {
        in<<*iter<<" ";
        
    } 
    in<<endl;
    return in;
 }