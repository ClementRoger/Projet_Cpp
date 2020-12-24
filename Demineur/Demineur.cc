
#include <string>
#include <vector>
#include <iostream>
#include <time.h>

#include "Demineur.hh"
 
/*  _plateau :0 = case vide 
            -1 = bombe 
            >0 = nombres de bombes environantes */

/* nb_try, nb_bomb, taille de la grille */
 Demineur::Demineur(const std::size_t count, const std::size_t bomb, const std::size_t gridsize):MiniJeu(count,false){ 

   // _nb_try = count;
    _nb_bomb = bomb;

        // Declaration de la grille initialisée à 0
    std::vector<std::vector<int>>tmp(gridsize,std::vector<int>(gridsize,0));

    /* Choix aléatoire de la position des bombes dans la grille */
    srand(time(0));
    for (std::size_t i = 0; i < bomb+1; i++){
        std::size_t tmp_x = 1+rand()%(gridsize - 1);
        std::size_t tmp_y = 1+rand()%(gridsize - 1);
        for (std::size_t j = i; j > 0; j--){
            if(tmp_x == _bomb_x[j] && tmp_y == _bomb_y[j]){
                tmp_x = 1+rand()%(gridsize - 1);
                tmp_y = 1+rand()%(gridsize - 1);
            }
        }

        _bomb_x.push_back(tmp_x);
        _bomb_y.push_back(tmp_y); 
    }

    /* Initialise le tableau contenant les bombes + check le nombre de bombes */
    initBomb(tmp,gridsize);

    _plateau = tmp;

    std::vector<std::vector<bool>>open_tiles(get_plateau().size(),std::vector<bool>(get_plateau().size(),false));
    _open_tiles = open_tiles;
    
    pos_x=0;
    pos_y=0;
}


Demineur::~Demineur(){ 
    //std::cout<<"Demineur destroyed"<<std::endl;

} 


void Demineur::play(){
    std::size_t tmp_x,tmp_y;
  // Permet de récuperer les indices des cases cliqués 
    tmp_x = (std::size_t)(get_pos_x() - (APP_SIZE_X-(IMG_SIZE*get_plateau().size()))/2)/IMG_SIZE;
    tmp_y = (std::size_t)(get_pos_y() - (APP_SIZE_Y-(IMG_SIZE*get_plateau().size()))/2)/IMG_SIZE;


    if (!get_open_tiles()[tmp_x][tmp_y]){
        reveal(tmp_x,tmp_y);
        set_open_tiles(true,tmp_x,tmp_y);
        
        if( get_plateau()[tmp_x][tmp_y] == -1 ){
            set_nb_try(get_nb_try()-1);
            std::cout<<"Aie, vous etes tombé sur une bombe... Il vous reste : "<<get_nb_try()<<std::endl;
        }
        set_win(checkBool(get_open_tiles()));
    }
    else {
        std::cout<<"Vous avez deja ouvert cette case."<<std::endl;
    }
}


/* Initialise le plateau avec les bombes et le nombres de bombes environante */
void Demineur::initBomb(std::vector<std::vector<int>>&tab,const std::size_t gridsize){
    for (std::size_t i = 0; i < gridsize; i++){
        for (std::size_t j = 0; j < gridsize ; j++){
            for (std::size_t k = 0; k < get_nb_bomb() ; k++){
                if ( get_bomb_x()[k] == i && get_bomb_y()[k] == j){
                    tab[i][j] = -1;
                }
            }
        }
    }
    checkBomb(tab,gridsize);
}

/* Permet d'initialiser les cases avec le nombre de bombes adjacentes */
void Demineur::checkBomb(std::vector<std::vector<int>>&tab, const std::size_t gridsize){
    for (std::size_t i=0 ; i < gridsize; i++){
        for (std::size_t j=0 ; j < gridsize; j++){
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
void Demineur::reveal(const std::size_t i, const std::size_t j){
    if(!get_open_tiles()[i][j] && !get_plateau()[i][j])
    {       
        set_open_tiles(true,i,j);

        if(i>0) {reveal(i-1, j); }
        if(i>0 && j>0) {reveal(i-1, j-1);}
        if(j>0) {reveal( i, j-1);}
        if(j>0 && i<get_open_tiles().size()-1) {reveal(i+1, j-1);}
        if(i<get_open_tiles().size()-1) {reveal( i+1, j);}
        if(i>get_open_tiles().size()-1 && j<get_open_tiles().size()-1) {reveal( i+1, j+1);}
        if(j<get_open_tiles().size()-1) {reveal(i, j+1);}
        if(i>0 && j<get_open_tiles().size()-1) {reveal( i-1, j+1);}
    }
}

/* Check si toutes les cases ont été ouvertes */
bool Demineur::checkBool(const std::vector<std::vector<bool>>tab){

    for (std::size_t i = 0; i < tab.size(); i++){
        for (std::size_t j = 0; j < tab.size(); j++){
            if ( !tab[i][j] && get_plateau()[i][j] != -1) return false;
        }
    }

    return true;
}


/* Affichage du jeu */ 
void Demineur::affichage(const std::vector<std::vector<bool>>matrice){
 //   cout<<get_plateau().size();
    for(std::size_t x=0; x < get_plateau().size(); x++){
        for(std::size_t y=0; y < get_plateau().size(); y++){
            if (matrice[x][y]){
                if(get_plateau()[x][y]>0){ std::cout<<"["<<get_plateau()[x][y]<<"] "; }
                else if (get_plateau()[x][y]<0){ std::cout<<"[*] "; }
                else{ std::cout<<"[0] ";}
            }
            else {
                std::cout<<"[ ] ";
            } 
        }
        std::cout << std::endl;  
    }
    std::cout << std::endl;
}



/*
void Demineur::play(){

    // Grille représentant les cases ouvertes par le joueur
       // -- initialisé à false. True si la case est ouverte 
    std::vector<std::vector<bool>>tmp(get_plateau().size(),std::vector<bool>(get_plateau().size(),false));

    bool flag = false;
    string x,y;
    std::size_t tmp_x,tmp_y;
    while (!win(flag) && get_nb_try()){ 
        affichage(tmp);
        cout<<"Entrez les coordonnées votre choix"<<endl;
        cout<<"Entrez le numéro ligne : "<<endl;
        getline(cin,x);
        cout<<"Entrez le numéro colonne: "<<endl;
        getline(cin,y);

        // Test des variables d'entrées 
        if (y.find_first_not_of( "0123456789" ) != string::npos 
            || x.find_first_not_of( "0123456789" ) != string::npos 
            || (size_t)stoi(x)-1>get_plateau().size() -1
            || (size_t)stoi(y)-1>get_plateau().size()-1 ){
            cout<<"ERROR. Rentrez des coordonnées valide."<<endl;
            set_nb_try(get_nb_try()+1);
        } 
        // Si entrées valides 
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

bool Demineur::win(const bool flag){

    bool tmp = false;
    if (flag){ 
        cout<< "You win!"<<endl;
        return true;
    }

    if(get_nb_try() <= 0){
        cout<< "You loose :(!"<<endl;
    }


    return tmp;
}


*/