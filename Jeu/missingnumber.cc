 
#include<stdlib.h>
#include <string>
#include<fstream>
#include <vector>
#include <iostream>
#include <sstream>
#include <time.h>
#include <algorithm> 

#include "missingnumber.hh"


 Missingnumber::Missingnumber(std::fstream& in,const std::size_t nb):MiniJeuAvecSolution(nb,false){ 
    srand(time(0));
    std::vector<std::vector<std::string>>tempmatrice;
    fill_vector(in,tempmatrice);
    _matrice = tempmatrice;
    set_user_entry("");
    //std::cout<<"solution :"<<get_solution()<<std::endl;
}

Missingnumber::Missingnumber(const std::size_t nb):MiniJeuAvecSolution(nb,false){
    std::vector<std::vector<std::string>>temp { {"3","1","4"},
                                                {"1","?","9"},
                                                {"2","6","5"}};
    _matrice = temp;
    set_solution("5");
    set_user_entry("");
}


Missingnumber::~Missingnumber(){ 
    //std::cout<<"Missingnumber destroyed"<<std::endl;

} 

/* Parcours le fichier pour en extraire une matrice et sa solution */
void Missingnumber::fill_vector(std::fstream& in,std::vector<std::vector<std::string>>&tempmatrice){
    std::size_t random = 1+rand()%(5);
    std::size_t count = 1;
    std::size_t tmp = 1;
    std::string line;
     while(!in.eof()){
        getline(in,line,'\n');
        std::stringstream stream(line);

        if(count <= random){
            if( (line[0] =='s')){
                count ++;
                if(count == random +1){
                    find_solution(stream,tmp);
                }
            } 
        }
        else {
            find_matrice(stream,tempmatrice,tmp);
        }

    }
}

/* Recuperer la solution de la matrice choisie aléatoirement*/
void Missingnumber::find_solution(std::stringstream& stream,std::size_t& tmp){
    for(std::string word; getline(stream,word,' ');){
         tmp++;
        if (tmp == 3){
             set_solution(word);
             tmp = 0;
         }
    }
}

/* Recuperer la matrice choisie aléatoirement*/
void Missingnumber::find_matrice(std::stringstream& stream,std::vector<std::vector<std::string>>&tempmatrice,std::size_t& tmp) const {
    if (tmp < 3){
        std::vector<std::string>templine;
        for(std::string tempword; getline(stream,tempword,' ');){
            templine.push_back(tempword); 
        }
        tempmatrice.push_back(templine);
        templine.clear();
        tmp++;
    }
}

/* Permet de jouer aprés une entrée utilisateur. Appellée à chaque nouvelle entrée utilisateur*/
void Missingnumber::play(){
   std::string number = get_user_entry();

        if (check_entry(number)){

            if (!number.compare(get_solution())){
                set_win(true);
            }
            else {
                //std::cout<<"Try again. Il vous reste "<<get_nb_try()-1<<" chances."<<std::endl;
            }

            set_nb_try(get_nb_try()-1);
        }

}

/* Test la validité de l'entrée utilisateur */
bool Missingnumber::check_entry(const std::string entry) const {

    if (!entry.size()){
        return false;
    }
    else {
        if (entry.find_first_not_of( "0123456789") != std::string::npos){
            return false;
        }
        return true;
    }
}



/* Affichage du jeu */ 
void Missingnumber::affichage(std::vector<std::vector<std::string>>matrice){

    std::cout<<"---------------------------------"<<std::endl<<std::endl;

    std::vector<std::vector<std::string> >::iterator row;
    std::vector<std::string>::iterator col;

    for(row = matrice.begin() ; row !=matrice.end() ; row++){
        for(col = row->begin() ; col != row->end() ; col++){
            std::cout << *col <<" ";
        }
        std::cout << std::endl;  
    }

   std::cout<<"Entrez un nombre :"<< std::endl;
} 

