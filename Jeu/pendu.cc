 
#include<stdlib.h>
#include <string>
#include<fstream>
#include <vector>
#include <iostream>
#include <sstream>
#include <time.h>
#include <algorithm> 
using namespace std;

#include "pendu.hh" 

 Pendu::Pendu(fstream& in, const size_t count):MiniJeuAvecSolution(count,false){ 

    srand(time(0));

    string word;
    vector<string> all_lines;
    int total_lines = 0;
    int random = 0;

    while(getline(in,word)){
        total_lines++;
        all_lines.push_back(word);
    }

    random = rand()%(total_lines);

    set_solution(all_lines[random]);

    vector<size_t>found_letters(get_solution().size(),0);
    found_letters[0] = 1;
    _found_letters=found_letters;
    _user_entry ="";
    cout<<"mistery: "<<get_solution()<<endl;

}


Pendu::~Pendu(){ 
    //std::cout<<"Pendu destroyed"<<std::endl;
} 

void Pendu::play(){

    vector<string>used_letters=get_used_letters();

    vector<size_t>found_letters=get_found_letters();

    string letter = get_user_entry();
    std::cout<<"letters: "<<letter<<std::endl;
    transform(letter.begin(), letter.end(),letter.begin(), ::toupper);

// Si l'entrée est valide
    if (check_entry(letter)){

        
        if (letter.size() == 1 ){
            //used_letters.push_back(letter);
            add_letter(used_letters,letter);
            size_t place = get_solution().find(letter);

            
            if (place != string::npos){
                set_win(find_letter(letter,found_letters,letter.size()));
                set_nb_try(get_nb_try()+1);
            }
        }
        
        else {

            if(!letter.compare(get_solution())){
                set_win(find_letter(letter,found_letters,letter.size()));
            }
           
        }

        set_found_letters(found_letters);
        set_used_letters(used_letters);
    }
    // entrée non valide    
    else {
       // cout<<"ERROR. Rentrez une lettre ou un mot."<<endl;
        set_nb_try(get_nb_try()+1);
    }

    
    affichage(found_letters);
    set_nb_try(get_nb_try()-1);
    cout<<get_nb_try()<<endl;
}

/* Permet d'ajouter la lettre à used_letters que si elle n'apparait pas déja*/
void Pendu::add_letter(vector<string>&used_letters,string letter){
    bool flag = false;

    for (size_t i = 0; i < used_letters.size(); i++){
        if (used_letters[i] == letter) flag = true;
    }
    if (!flag){
        used_letters.push_back(letter);
    }
    
}

bool Pendu::check_entry(const string entry){

    if (!entry.size()){
        return false;
    }
    else {
        if (entry.find_first_not_of("ABCDEFGHIJKLMNOPQRSTUVWXYZ") != std::string::npos){
            return false;
        }
        return true;
    }
}

/* Permet de remplir de tableau des lettre trouvés et de voir si
elles ont toutes été trouvés */
bool Pendu::find_letter(string letter,vector<size_t>&found_letters,const size_t taille){
    bool res = true;
    for (size_t i = 0; i< found_letters.size(); i++){
        if(taille == 1){
            std::ostringstream ss;
            ss << get_solution()[i];
            string tmp = ss.str();
            if(letter == tmp ){
                found_letters[i] = 1;
            }
        }
        else {
            found_letters[i] = 1;
        }

        if(!found_letters[i]){
                res = false;
        }
    }
    return res;
}

/* Affichage du jeu */ 
void Pendu::affichage(vector<size_t>found_letters){
    string res;

    for (size_t i=0; i<found_letters.size();i++){
        if (found_letters[i]){
            res = res + get_solution()[i];
        }
        else {
            res = res + "*";
        }
    }
    cout<<"---------------------------------"<<endl<<endl;
    cout<<res<<endl<<endl;
}


/*
bool Pendu::win(const bool flag){
    if (flag){ 
        cout<< "You win!"<<endl;
        return true; 
    }
    if(get_nb_try() <= 0){
        cout<< "You loose :(!"<<endl;
        cout<<"The response was : "<<get_mistery()<<endl;
    }
   return false;
}
*/


/*
void Pendu::play(){

    vector<string>used_letters;

    vector<size_t>found_letters(get_mistery().size(),0);


    found_letters[0] = 1;
    affichage(found_letters);
 

    while (!win() && get_nb_try() ){

        string letter;
        cout << "Rentrez une lettre ou un mot :"<<endl;
        getline(cin,letter);
        transform(letter.begin(), letter.end(),letter.begin(), ::toupper);
 
    // Si l'entrée est valide
        if (validity_test(letter)){

            
            if (letter.size() == 1 ){
                used_letters.push_back(letter);
                
                size_t place = get_mistery().find(letter);

                
                if (place != string::npos){
                    set_win(find_letter(letter,found_letters,letter.size()));
                    set_nb_try(get_nb_try()+1);
                }
                else{
                    cout<<"Try again. Il vous reste "<<get_nb_try()-1<<" chances."<<endl;
                }

                cout<<used_letters;
            }
            
            else {

              
                if(letter.compare(get_mistery())){
                    cout<<"Try again. Il vous reste "<<get_nb_try()-1<<" chances."<<endl;
                }
               
                else{
                    set_win(find_letter(letter,found_letters,letter.size()));
                }
            }
        }
        // entrée non valide    
        else {
            cout<<"ERROR. Rentrez une lettre ou un mot."<<endl;
            set_nb_try(get_nb_try()+1);
        }

        affichage(found_letters);
        set_nb_try(get_nb_try()-1);
    } 

    if(get_nb_try() <= 0){
        cout<< "You loose :(!"<<endl;
        cout<<"The response was : "<<get_mistery()<<endl;
    }
} */