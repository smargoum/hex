#ifndef STRAT

#define STRAT
#include "player.h"
#include "../graph.h"
#include "../move.h"

struct couple {
    int x;
    int y;
};
gsl_spmatrix * graph_to_matrix(int m, struct player p , struct graph_t * g);
struct couple mov_to_pos(struct move_t mov , int m , gsl_spmatrix * mat);
struct move_t position_to_move(gsl_spmatrix * mat , struct couple c , struct player p);
int is_empty(struct graph_t * gra , size_t pos);
struct move_t rand_mov(struct move_t previous_move,struct player p1,struct graph_t * player_g);
int rand_pick(int n);
void random_init(void);
void print_matrix(gsl_spmatrix * a , size_t l , size_t c);



#endif