
#include <string>
#include <vector>
#include <iostream>
#include <time.h>
using namespace std;

#include "Demineur.hh"

/*  _plateau :0 = case vide 
            -1 = bombe 
            >0 = nombres de bombes environantes */

/* nb_try, nb_bomb, taille de la grille */
 Demineur::Demineur(const size_t count, const size_t bomb, const size_t gridsize){ 

    _nb_try = count;
    _nb_bomb = bomb;

        // Declaration de la grille initialisée à 0
    vector<vector<int>>tmp(gridsize,vector<int>(gridsize,0));

    /* Choix aléatoire de la position des bombes dans la grille */
    srand(time(0));
    for (size_t i = 0; i < bomb+1; i++){
        _bomb_x.push_back(1+rand()%(gridsize - 1));
        _bomb_y.push_back(1+rand()%(gridsize - 1));
    }

    /* Initialise le tableau contenant les bombes + check le nombre de bombes */
    initBomb(tmp,gridsize);

    _plateau = tmp;

}


Demineur::~Demineur(){ 
    //std::cout<<"Missingnumber destroyed"<<std::endl;

} 

void Demineur::play(){

    /* Grille représentant les cases ouvertes par le joueur
        -- initialisé à false. True si la case est ouverte */ 
    vector<vector<bool>>tmp(get_plateau().size(),vector<bool>(get_plateau().size(),false));

    bool flag = false;
    string x,y;
    size_t tmp_x,tmp_y;
    while (!win(flag) && get_nb_try()){
        affichage(tmp);
        cout<<"Entrez les coordonnées votre choix"<<endl;
        cout<<"Entrez le numéro ligne : "<<endl;
        getline(cin,x);
        cout<<"Entrez le numéro colonne: "<<endl;
        getline(cin,y);

        /* Test des variables d'entrées */
        if (y.find_first_not_of( "0123456789" ) != string::npos 
            || x.find_first_not_of( "0123456789" ) != string::npos 
            || (size_t)stoi(x)-1>get_plateau().size() -1
            || (size_t)stoi(y)-1>get_plateau().size()-1 ){
            cout<<"ERROR. Rentrez des coordonnées valide."<<endl;
            set_nb_try(get_nb_try()+1);
        } 
        /* Si entrées valides */
        else {
            tmp_x = (size_t)stoi(x)-1;
            tmp_y = (size_t)stoi(y)-1;

            if (!tmp[tmp_x][tmp_y]){
                reveal(tmp,get_plateau(),tmp_x,tmp_y);
                tmp[tmp_x][tmp_y] = true;
                if( get_plateau()[tmp_x][tmp_y] == -1 ){
                    set_nb_try(get_nb_try()-1);
                    cout<<"Aie, vous etes tombé sur une bombe... Il vous reste : "<<get_nb_try()<<endl;
                }
                flag=checkBool(tmp);
            }
            else {
                cout<<"Vous avez deja ouvert cette case."<<endl;
            }
            
        }

    }
   
}


/* Initialise le plateau avec les bombes et le nombres de bombes environante */
void Demineur::initBomb(vector<vector<int>>&tab,const size_t gridsize){
    for (size_t i = 0; i < gridsize; i++){
        for (size_t j = 0; j < gridsize ; j++){
            for (size_t k = 0; k < get_nb_bomb() ; k++){
                if ( get_bomb_x()[k] == i && get_bomb_y()[k] == j){
                    tab[i][j] = -1;
                }
            }
        }
    }
    checkBomb(tab,gridsize);
}

/* Permet d'initialiser les cases avec le nombre de bombes adjacentes */
void Demineur::checkBomb(vector<vector<int>>&tab, const size_t gridsize){
    for (size_t i=0 ; i < gridsize; i++){
        for (size_t j=0 ; j < gridsize; j++){
            if(tab[i][j] != -1){
                if( (i<gridsize-1) && (j<gridsize-1) && (tab[i+1][j+1] == -1)) tab[i][j]++;
                if( (i<gridsize-1) && (tab[i+1][j] == -1)) tab[i][j]++;
                if( (i<gridsize-1) && (j>0) && (tab[i+1][j-1] == -1)) tab[i][j]++;
                if( (j<gridsize-1) && (tab[i][j+1] == -1)) tab[i][j]++;
                if( (j>0) && (tab[i][j-1] == -1)) tab[i][j]++;
                if( (i>0) && (j<gridsize-1) && (tab[i-1][j+1] == -1)) tab[i][j]++;
                if( (i>0) && (tab[i-1][j] == -1)) tab[i][j]++;
                if( (i>0) && (j>0) && (tab[i-1][j-1] == -1)) tab[i][j]++;
            }
        }
    }
}

/* Si la case choisie contient un 0 = vide alors on affiche toutes les cases à 0 environantes */
void Demineur::reveal(vector<vector<bool>>&tmp, const vector<vector<int>>tab, const size_t i, const size_t j){
    if(!tmp[i][j] && !tab[i][j])
    {       
        tmp[i][j]=true;
        if(i>0) {reveal(tmp, tab, i-1, j); }
        if(i>0 && j>0) {reveal(tmp, tab, i-1, j-1);}
        if(j>0) {reveal(tmp, tab, i, j-1);}
        if(j>0 && i<tmp.size()-1) {reveal(tmp, tab, i+1, j-1);}
        if(i<tmp.size()-1) {reveal(tmp, tab, i+1, j);}
        if(i>tmp.size()-1 && j<tmp.size()-1) {reveal(tmp, tab, i+1, j+1);}
        if(j<tmp.size()-1) {reveal(tmp, tab, i, j+1);}
        if(i>0 && j<tmp.size()-1) {reveal(tmp, tab, i-1, j+1);}
    }
}

/* Check si toutes les cases ont été ouvertes */
bool Demineur::checkBool(const vector<vector<bool>>tab){

    for (size_t i = 0; i < tab.size(); i++){
        for (size_t j = 0; j < tab.size(); j++){
            if ( !tab[i][j] && get_plateau()[i][j] != -1) return false;
        }
    }

    return true;
}


/* Affichage du jeu */ 
void Demineur::affichage(const vector<vector<bool>>matrice){
 //   cout<<get_plateau().size();
    for(size_t x=0; x < get_plateau().size(); x++){
        for(size_t y=0; y < get_plateau().size(); y++){
            if (matrice[x][y]){
                if(get_plateau()[x][y]>0){ cout<<"["<<get_plateau()[x][y]<<"] "; }
                else if (get_plateau()[x][y]<0){ cout<<"[*] "; }
                else{ cout<<"[0] ";}
            }
            else {
                cout<<"[ ] ";
            } 
        }
        cout <<endl;  
    }
    cout << endl;
}


/* Test si on a gagner ou non */
bool Demineur::win(const bool flag){
    if (flag){ 
        cout<< "You win!"<<endl;
        return true; 
    }
    if(get_nb_try() <= 0){
        cout<< "You loose :(!"<<endl;
    }
    return false;
}