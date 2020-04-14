#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "player.h"
#include "strategy.h"
#include "../server/option.h"


struct player {
    char player_name[100];
    enum color_t player_color;
};


//! this function creates a matrix that represent the table of game 
//! its used to have a better vision of the game

// m doit correspondre au nombre de vertices
struct couple mov_to_pos(struct move_t mov , int m , gsl_spmatrix * mat)
{
    struct couple p = {0,0};
    for(int i = 0 ; i <= m ; i++){
        for(int j = 0 ; j <= m ; j++){
            if((size_t)gsl_spmatrix_get(mat,i,j) == mov.m){
                p.x = i;
                p.y = j;
            }
        }
    }
    return p;
}

struct move_t position_to_move(gsl_spmatrix * mat , struct couple c , struct player p)
{
    struct move_t m;
    m.m = (size_t)(gsl_spmatrix_get(mat,(size_t)c.x,(size_t)c.y));
    m.c = p.player_color;
    return m;
}

gsl_spmatrix * graph_to_matrix(int m , struct player p , struct graph_t * g)
{
    gsl_spmatrix * mat = gsl_spmatrix_alloc(m+1,m+1);
    int k = 0;
    for (int i = 0 ; i <= m ; i++){
        for (int j = 0 ; j <= m ; j++){
            gsl_spmatrix_set(mat,i,j,k);
            k++;
        }
    }/*
    for(int i = 0 ; i < m ; i++){
        if(gsl_spmatrix_get(g->o,p.player_color,i) != (double)1){
            gsl_spmatrix_transpose(mat);
            return mat;
        }
    }*/
    if(gsl_spmatrix_get(g->o,p.player_color,1) != 1){
        gsl_spmatrix_transpose(mat);
        return mat;
    }
    //gsl_spmatrix_transpose(mat);
    return mat;
}


int is_empty(struct graph_t * gra , size_t pos)
{
    int a = gsl_spmatrix_get(gra->o,0,pos);
    int b = gsl_spmatrix_get(gra->o,1,pos);
    return (a == 0 && b == 0);
}

///// the random pick

void random_init(void){
    srand(time(NULL));
}

int rand_pick(int n)
{
    random_init();
    if (n != 0)
    {
        return rand() % n;
    }
    else
    {
        return 0;
    }
}
struct move_t rand_mov(struct move_t previous_move,struct player p1,struct graph_t * player_g)
{
    size_t TAILLE = player_g->num_vertices;
    int tab[TAILLE];
    int taille = 0;
    int i;
    struct move_t mv;
    for (i = 0; (size_t)i < TAILLE; i++)
    {
        if ((int)gsl_spmatrix_get(player_g->o, BLACK, (size_t)i) == 0 && (int)gsl_spmatrix_get(player_g->o, WHITE, (size_t)i) == 0 && i != (int)previous_move.m)
        {
            tab[taille] = i;
            taille++;
        }
    }
    mv.m = (size_t)tab[rand_pick(taille)];
    mv.c = p1.player_color;
   
    return mv;
}


void print_matrix(gsl_spmatrix * a , size_t l , size_t c)
{
    printf("[");
    for (size_t i = 0; i < l; ++i){
        printf("[");
        for (size_t j = 0; j < c; ++j){
            /*printf("A(%zu,%zu) = %g", i, j,
            gsl_spmatrix_get(a, i, j));*/
            if(j == c -1 ){
                printf("%d",(int)gsl_spmatrix_get(a, i, j));
            }
            else{
                printf("%d,",(int)gsl_spmatrix_get(a, i, j));             
            }
        }
        printf("]");
        if(i < l - 1)
            printf("\n");
    }
    printf("]\n");
}