 
#include<stdlib.h>
#include <string>
#include<fstream>
#include <vector>
#include <iostream>
#include <sstream>
#include <time.h>
#include <algorithm> 


#include "missingnumber.hh"

 Missingnumber::Missingnumber(std::fstream& in,const std::size_t nb):MiniJeu(nb,false){ 

    srand(time(0));
    std::size_t random = 1+rand()%(5);

    std::size_t count = 1;
    std::size_t tmp = 1;
    std::string line;

    std::vector<std::vector<std::string>>tempmatrice;

    while(!in.eof()){
        getline(in,line,'\n');
        std::stringstream stream(line);

        /* Recuperer la solution de la matrice choisie aléatoirement*/
        if(count <= random){
            if( (line[0] =='s')){
                count ++;
                if(count == random +1){
                    for(std::string word; getline(stream,word,' ');){
                         tmp++;
                        if (tmp == 3){
                             _solution = word;
                             std::cout<<"solution:"<<_solution<<std::endl;
                             tmp = 0;
                         }
        
                    }
                }
            } 
        }
        else {
        /* Recuperer la matrice choisie aléatoirement*/
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

    }
    
    _matrice = tempmatrice;
    _user_entry = "";
    //affichage(tempmatrice);
}

Missingnumber::~Missingnumber(){ 
    //std::cout<<"Missingnumber destroyed"<<std::endl;

} 


void Missingnumber::play(){
   std::string number = get_user_entry();

        if (validity_test(number)){

            if (!number.compare(get_solution())){
                set_win(true);
            }
            else {
                std::cout<<"Try again. Il vous reste "<<get_nb_try()-1<<" chances."<<std::endl;
            }

            set_nb_try(get_nb_try()-1);
        }

}

/* Test la validité de l'entrée utilisateur */
bool Missingnumber::validity_test(const std::string tmp){

    if (!tmp.size()){
        return false;
    }
    else {
        if (tmp.find_first_not_of( "0123456789") != std::string::npos){
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



/*
bool Missingnumber::win(bool flag){
    if (flag){ 
        cout<< "You win!"<<endl;
        return true; 
    }
    if(get_nb_try() <= 0){
        cout<< "You loose :(!"<<endl;
        cout<<"The response was : "<<get_solution()<<endl;
    }
   return false;
}

*/


/*
void Missingnumber::play(){
   std::string number;

   while (!win() && get_nb_try() ){
        affichage(get_matrice());
        getline(std::cin,number);

        if (number.find_first_not_of( "0123456789" ) != std::string::npos){
            std::cout<<"ERROR. Rentrez un chiffre ou un nombre."<<std::endl;
            set_nb_try(get_nb_try()+1);
        }
        else {
            if (!number.compare(get_solution())){
                set_win(true);
            }
            else {
                std::cout<<"Try again. Il vous reste "<<get_nb_try()-1<<" chances."<<std::endl;
            }
        }

        set_nb_try(get_nb_try()-1);
   }

   if(get_nb_try() <= 0){
        std::cout<< "You loose :(!"<<std::endl;
        std::cout<<"The response was : "<<get_solution()<<std::endl;
    }

}*/