#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include"player.h"
#include"strategy.h"

// this function prints the matrix 
struct player {
    char player_name[100];
    enum color_t player_color;
};




void test_get_player_name()
{
    if(strcmp(get_player_name(),"lasj") == 0){
        printf("\033[32;01mSUCCESS\033[00m for for the function get_player_name()\n");
    }
    else{
        printf("\033[31;01mFAIL\033[00m for function get_player_name()\n");
    }
}

void test_propose_opening(struct graph_t g)
{
    struct move_t m = propose_opening();
    int a = sqrt(g.num_vertices) - 1;
    if(m.m == 2*a){
        printf("\033[32;01mSUCCESS\033[00m for for the function propose_opening()\n");
    }
    else{
        printf("\033[31;01mFAIL\033[00m for function propose_opening()\n");
    }
    if(m.m == 2*a){
        printf("\033[32;01mSUCCESS\033[00m for for the function propose_opening()\n");
    }
    else{
        printf("\033[31;01mFAIL\033[00m for function propose_opening()\n");
    }
}
void test_accept_opening(const struct move_t opening)
{
    struct move_t p = propose_opening();
    if(opening.m == p.m){
        if(accept_opening(opening)){
            printf("\033[31;01mFAIL(1)\033[00m for function accept_opening()\n");
        }
        else{
            printf("\033[32;01mSUCCESS(1)\033[00m for for the function accept_opening()\n");
        }
    }
    else{
        if(accept_opening(opening)){
            printf("\033[32;01mSUCCESS(2)\033[00m for for the function propose_opening()\n");
        }
        else{
            printf("\033[31;01mFAIL(2)\033[00m for function accept_opening()\n");
        }
    }
}


void test_initialize_graph(struct graph_t* graph,struct graph_t *g)
{
    if(graph != NULL){
        if(gsl_spmatrix_equal(graph->t,g->t) && graph->num_vertices == g->num_vertices && gsl_spmatrix_equal(graph->o,g->o)){
            printf("\033[32;01mSUCCESS\033[00m for for the function initialize_graph()\n");
        }
        else{
            printf("\033[31;01mFAIL\033[00m for function initialize_graph()\n");
        }
    }
    else{
        printf("\033[31;01mWARNING\033[00m for function initialize_graph() , graph is NULL\n");
    }
}


void test_initialize_color(enum color_t id, struct player * p1)
{
    if (p1->player_color == id)
    {
        printf("\033[32;01mSUCCESS\033[00m for for the function initialize_color()\n");
    }
    else{
        printf("\033[31;01mFAIL\033[00m for function initialize_color() \n");
    }
}

void test_play(struct move_t previous_move);



    
// to compile we used gcc -fPIC -shared ${GSL_PATH} player.c 
int main()
{
    extern struct graph_t *player_g;
    extern struct player p1;
    gsl_spmatrix * gra = gsl_spmatrix_alloc(4,4);
    gsl_spmatrix * o = gsl_spmatrix_alloc(2,4);
    struct graph_t gr = {4,gra,o};
    test_get_player_name();
    gsl_spmatrix_set(gra, 0, 1, 1);
    gsl_spmatrix_set(gra, 0, 3, 1);
    gsl_spmatrix_set(gra, 1, 0, 1);
    gsl_spmatrix_set(gra, 1, 2, 1);
    gsl_spmatrix_set(gra, 3, 0, 1);
    gsl_spmatrix_set(gra, 2, 1, 1);
    struct graph_t * new = malloc(sizeof(struct graph_t));
    copy_graph(new , &gr);
    initialize_graph(new);
    test_propose_opening(gr);
    test_initialize_graph(&gr,player_g);
    test_initialize_color(0 , &p1);
    finalize();
    gsl_spmatrix_free(gra);
    gsl_spmatrix_free(o);
    return 0;
}
