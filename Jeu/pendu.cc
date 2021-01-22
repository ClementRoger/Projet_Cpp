 
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
    vector<string> all_lines;

    set_solution(all_lines[find_random(in,all_lines)]);

    vector<bool>found_letters(get_solution().size(),false);
    found_letters[0] = 1;
    _found_letters=found_letters;
    set_user_entry("");
    //cout<<"mistery: "<<get_solution()<<endl;
}

// Contructeur fait seulement pour le testcase
Pendu::Pendu(string tmp, const size_t count):MiniJeuAvecSolution(count,false){ 

    set_solution(tmp);
    vector<bool>found_letters(get_solution().size(),false);
    found_letters[0] = 1;
    _found_letters=found_letters;
    set_user_entry("");
}

Pendu::~Pendu(){ 
    //std::cout<<"Pendu destroyed"<<std::endl;
} 

/* Permet de retourner un nombre random */
size_t Pendu::find_random(fstream& in,vector<string>& all_lines){
    string word;
    int total_lines = 0;

    while(getline(in,word)){
        total_lines++;
        all_lines.push_back(word);
    }

    return rand()%(total_lines);
}

/* Permet de jouer aprés une entrée utilisateur. Appellée à chaque nouvelle entrée utilisateur*/
void Pendu::play(){
    string letter = get_user_entry();
    transform(letter.begin(), letter.end(),letter.begin(), ::toupper);

    // Si l'entrée est valide
    if (check_entry(letter)){
        compare_to_solution(letter);
    }
    // entrée non valide    
    else {
        set_nb_try(get_nb_try()+1);
    }
    set_nb_try(get_nb_try()-1);
}

/* Permet de comparer l'entrée de l'utilisateur à la solution */
void Pendu::compare_to_solution(const string letter){
    vector<string>used_letters=get_used_letters();
    vector<bool>found_letters=get_found_letters();
    if (letter.size() == 1 ){
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

/* Permet d'ajouter la lettre à used_letters que si elle n'apparait pas déja*/
void Pendu::add_letter(vector<string>&used_letters,string letter)const{
    bool flag = false;

    for (size_t i = 0; i < used_letters.size(); i++){
        if (used_letters[i] == letter) flag = true;
    }
    if (!flag){
        used_letters.push_back(letter);
    }
    
}

/* Permet de checker si l'entrée utilisateur est correcte */
bool Pendu::check_entry(const string entry)const {

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
bool Pendu::find_letter(string letter,vector<bool>&found_letters,const size_t taille)const{
    bool res = true;
    for (size_t i = 0; i< found_letters.size(); i++){
        if(taille == 1){
            std::ostringstream ss;
            ss << get_solution()[i];
            string tmp = ss.str();
            if(letter == tmp ){
                found_letters[i] = true;
            }
        }
        else {
            found_letters[i] = true;
        }

        if(!found_letters[i]){
                res = false;
        }
    }
    return res;
}

/* Affichage du jeu */ 
void Pendu::affichage(vector<bool>found_letters){
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

