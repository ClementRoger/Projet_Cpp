
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

    _nb_bomb = bomb;

    // Declaration de la grille initialisée à 0
    std::vector<std::vector<int>>tmp(gridsize,std::vector<int>(gridsize,0));
    init_bomb_pos(gridsize);
    initBomb(tmp,gridsize);
    std::cout<<tmp;
    _plateau = tmp;

    std::vector<std::vector<bool>>open_tiles(get_plateau().size(),std::vector<bool>(get_plateau().size(),false));
    _open_tiles = open_tiles;
    
    pos_x=0;
    pos_y=0;
}


Demineur::~Demineur(){ 
    //std::cout<<"Demineur destroyed"<<std::endl;

} 

/* Choix aléatoire de la position des bombes dans la grille */
void Demineur::init_bomb_pos(const std::size_t gridsize){
    srand(time(0));
    for (std::size_t i = 0; i < get_nb_bomb()+1; i++){
        std::size_t tmp_x = 1+rand()%(gridsize - 1);
        std::size_t tmp_y = 1+rand()%(gridsize - 1);
        check_bomb_pos(i,gridsize,tmp_x,tmp_y);
        _bomb_x.push_back(tmp_x);
        _bomb_y.push_back(tmp_y); 
    }
}

/* Check que la position choisie aléatoirement de la bombe nexiste pas déja */
void Demineur::check_bomb_pos(const std::size_t i,const std::size_t gridsize,std::size_t &tmp_x,std::size_t &tmp_y)const{
    for (std::size_t j = i; j > 0; j--){
        if(tmp_x == _bomb_x[j] && tmp_y == _bomb_y[j]){
            tmp_x = 1+rand()%(gridsize - 1);
            tmp_y = 1+rand()%(gridsize - 1);
        }
    }
}

/* Initialise le plateau avec les bombes et le nombres de bombes environante */
void Demineur::initBomb(std::vector<std::vector<int>>&tab,const std::size_t gridsize)const{
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
void Demineur::checkBomb(std::vector<std::vector<int>>&tab, const std::size_t gridsize)const{
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

