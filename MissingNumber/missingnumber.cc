 
#include<stdlib.h>
#include <string>
#include<fstream>
#include <vector>
#include <iostream>
#include <sstream>
#include <time.h>
#include <algorithm> 
using namespace std;

#include "missingnumber.hh"

 Missingnumber::Missingnumber(fstream& in,const size_t nb){ 

    _nb_try = nb;

    srand(time(0));
    size_t random = 1+rand()%(5);

    size_t count = 1;
    size_t tmp = 1;
    string line;

    vector<vector<string>>tempmatrice;

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
                             cout<<"solution:"<<_solution<<endl;
                             tmp = 0;
                         }
        
                    }
                }
            } 
        }
        else {
        /* Recuperer la matrice choisie aléatoirement*/
            if (tmp < 4){
                vector<string>templine;
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
    //affichage(tempmatrice);

}


Missingnumber::~Missingnumber(){ 
    //std::cout<<"Missingnumber destroyed"<<std::endl;

} 

void Missingnumber::play(){
   bool flag = false;
   string number;

   while (!win(flag) && get_nb_try() ){
        affichage(get_matrice());
        getline(cin,number);

        /* Test si l'entrée est un nombre */
        if (number.find_first_not_of( "0123456789" ) != string::npos){
            cout<<"ERROR. Rentrez un chiffre ou un nombre."<<endl;
            set_nb_try(get_nb_try()+1);
        }
        else {
            /* Si entrée utilisateur & solution sont égaux */
            if (!number.compare(get_solution())){
                flag = true;
            }
            else {
                cout<<"Try again. Il vous reste "<<get_nb_try()-1<<" chances."<<endl;
            }
        }

        set_nb_try(get_nb_try()-1);
 
   }
}


/* Affichage du jeu */ 
void Missingnumber::affichage(vector<vector<string>>matrice){

    cout<<"---------------------------------"<<endl<<endl;

    vector<vector<string> >::iterator row;
    vector<string>::iterator col;

    for(row = matrice.begin() ; row !=matrice.end() ; row++){
        for(col = row->begin() ; col != row->end() ; col++){
            cout << *col <<" ";
        }
        cout <<endl;  
    }

    cout<<"Entrez un nombre :"<<endl;
}


/* Test si on a gagner ou non */
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