#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include<math.h>
#include "player.h"
#include "strategy.h"

struct player
{
    char player_name[100];
    enum color_t player_color;
};

struct player p1;

char const *get_player_name()
{
    strcpy(p1.player_name, "lasj");
    return "lasj";
}

struct graph_t *player_g = NULL;

struct move_t last ;
struct move_t propose_opening()
{
    int s = (int)sqrt(player_g->num_vertices) - 1;
    //struct move_t m = {s+2,p1.player_color};
    struct move_t m = {2*s,p1.player_color};
    last = m;
    return m; 
}


int accept_opening(const struct move_t opening)
{ 
    (void)opening;
    return 0;
}


void initialize_graph(struct graph_t *graph)
{
    player_g=graph;
}

void initialize_color(enum color_t id)
{
    p1.player_color = id;
}



int check_summet(struct graph_t *grph, unsigned int s)
{
    return !(gsl_spmatrix_get(grph->o, 0, s) || gsl_spmatrix_get(grph->o, 1, s));
}


void add_move(struct graph_t *grph, struct move_t mv)
{
    gsl_spmatrix_set(grph->o, mv.c, mv.m, 1);
}

// this helps to find the line that he wants to draw 
int find = 1;
struct couple last_up;
struct couple last_down;
// those three variable up are used in the strategy for the white player 

struct move_t play(struct move_t previous_move)
{
    add_move(player_g,previous_move);
    // s is the width of the graph
    int s = (int)sqrt(player_g->num_vertices) - 1;
    gsl_spmatrix * mat = graph_to_matrix(s,p1,player_g);
    // the case we are first player
    if(p1.player_color == BLACK){
        print_matrix(mat,s,s);
        //the position of our last move in the matrix
        struct couple current_point = mov_to_pos(last,s,mat);
        //the position of his move in the matrix 
        struct couple his_position = mov_to_pos(previous_move,s,mat);
        struct couple wanted = {current_point.x+1,current_point.y-1};
        struct move_t wanted_move = position_to_move(mat,wanted,p1);
        // le cas ou le sommet est disponible 
        if (check_summet(player_g,wanted_move.m))
        {
            add_move(player_g,wanted_move);
            last = wanted_move;
            gsl_spmatrix_free(mat);
            return wanted_move;
        }
        // le cas ou le sommet est plein
        else{
            // we play in the position next to the occupied position 
            wanted.y = wanted.y + 1;
            wanted_move = position_to_move(mat,wanted,p1);
            if(check_summet(player_g,wanted_move.m)){
                add_move(player_g,wanted_move);
                last = wanted_move;
                gsl_spmatrix_free(mat);
                return wanted_move;
            }
            // in case the space is full we will pass to defence
            else{
                wanted.y = wanted.y - 1;
                wanted_move = position_to_move(mat,wanted,p1);
                if(check_summet(player_g,wanted_move.m)){
                    add_move(player_g,wanted_move);
                    last = wanted_move;
                    gsl_spmatrix_free(mat);
                    return wanted_move;
                }
                else{
                    struct move_t r = rand_mov(previous_move,p1,player_g);
                    add_move(player_g,r);
                    last = r;
                    gsl_spmatrix_free(mat);
                    return r;
                }
            }
        }
    }
    else{
        print_matrix(mat,s,s);
        // i'm gonna try to use a defence technique 
        // i'm gonna find the line that he wants to draw and break his game 
        //this first if puts an obstacle in the line that  he wants to draw .
        struct couple his_position = mov_to_pos(previous_move,s,mat);        
        if(find){
            find = 0;
            struct couple wanted = {his_position.x,1};
            struct move_t wanted_move = position_to_move(mat,wanted,p1);
            if(check_summet(player_g,wanted_move.m)){
                add_move(player_g,wanted_move);
                last = wanted_move;
                last_down = mov_to_pos(last,s,mat);
                last_up = mov_to_pos(last,s,mat);
                gsl_spmatrix_free(mat);
                return wanted_move;
            }             
            else{
                wanted.y = s-1;
                wanted_move = position_to_move(mat,wanted,p1);
                if(check_summet(player_g,wanted_move.m)){
                    add_move(player_g,wanted_move);
                    last = wanted_move;
                    // this is just for first
                    last_up = mov_to_pos(last,s,mat);
                    last_down = mov_to_pos(last,s,mat);
                    gsl_spmatrix_free(mat);
                    return wanted_move;
                }
                // normaly this function wont get to this else because the other player could choose only 
                // one move in the begining
                else{
                    struct move_t r = rand_mov(previous_move,p1,player_g);
                    last = r;
                    add_move(player_g,r);
                    last_up = mov_to_pos(last,s,mat);
                    last_down = mov_to_pos(last,s,mat);
                    gsl_spmatrix_free(mat);
                    return r;
                }
            }
        } 
        // in this case we are not in the first move anymore 
        else{
            // we are going to start from the top
            struct couple his_position = mov_to_pos(previous_move,s,mat);
            // there are two cases eather we are in the right or the left collumn 
            struct couple last_couple = mov_to_pos(last,s,mat);
            // if we are in the left collumn or in another column beside the last
            if(last_couple.y != s-1){
                // if we are not in the top of the table 
                if(last_up.x != 1){ 
                    // we go up one column and +1 line (one line up)
                    // if not possible +1 line (one line up) and the same colomn 
                    // if not possible -1 colomn and the same line         
                    struct couple wanted = {last_up.x-1,last_up.y+1};
                    struct move_t wanted_move = position_to_move(mat,wanted,p1);
                    if(check_summet(player_g,wanted_move.m)){
                        add_move(player_g,wanted_move);
                    
                        // this is just for first
                        last_up = mov_to_pos(wanted_move,s,mat);
                        gsl_spmatrix_free(mat);
                        return wanted_move;
                    }
                    else{
                        // we go one line up
                        wanted.x = last_up.x-1;
                        wanted.y = last_up.y;
                        wanted_move = position_to_move(mat,wanted,p1);
                        if(check_summet(player_g,wanted_move.m)){
                            add_move(player_g,wanted_move);
                            last_up = mov_to_pos(wanted_move,s,mat);
                            gsl_spmatrix_free(mat);
                            return wanted_move;
                        }
                        else{
                            wanted.x = last_up.x - 1;
                            wanted.y = last_up.y;
                            wanted_move = position_to_move(mat,wanted,p1);
                            if(check_summet(player_g,wanted_move.m)){
                                add_move(player_g,wanted_move);
                                last_up = mov_to_pos(wanted_move,s,mat);
                                gsl_spmatrix_free(mat);
                                return wanted_move;
                            }
                            else{
                                wanted.x = last_up.x;
                                wanted.y = last_up.y-1;
                                wanted_move = position_to_move(mat,wanted,p1);
                                if(check_summet(player_g,wanted_move.m)){
                                    add_move(player_g,wanted_move);
                                    last_up = mov_to_pos(wanted_move,s,mat);
                                    gsl_spmatrix_free(mat);
                                    return wanted_move;
                                }
                                else{
                                    // we chenge the whole plan
                                    struct move_t r = rand_mov(previous_move,p1,player_g);
                                    last = r;
                                    add_move(player_g,r);
                                    last_up = mov_to_pos(last,s,mat);
                                    last_down = mov_to_pos(last,s,mat);
                                    gsl_spmatrix_free(mat);
                                    return r;
                                }
                            }
                        }
                    }
                }
                // if we reached the top we want to copmplete it from the bottom
                else{
                    // its gonna be simple 
                    struct couple wanted = {last_down.x+1,last_down.y};
                    struct move_t wanted_move = position_to_move(mat,wanted,p1);
                    if(check_summet(player_g,wanted_move.m)){
                        add_move(player_g,wanted_move);               
                        last_down = mov_to_pos(wanted_move,s,mat);
                        gsl_spmatrix_free(mat);
                        return wanted_move;
                    }
                    // its just random for the moment 
                    else{
                        struct move_t r = rand_mov(previous_move,p1,player_g);
                        last = r;
                        add_move(player_g,r);
                        last_up = mov_to_pos(last,s,mat);
                        last_down = mov_to_pos(last,s,mat);
                        gsl_spmatrix_free(mat);
                        return r;
                    }
                }
            }
            // if we are in the right side
            // just random for now
            else{
                if(last_up.x != s-1){
                    struct couple wanted = {last_up.x+1,last_up.y-1};
                    struct move_t wanted_move = position_to_move(mat,wanted,p1);
                    if(check_summet(player_g,wanted_move.m)){
                        add_move(player_g,wanted_move);
                        // this is just for first
                        last_up = mov_to_pos(wanted_move,s,mat);
                        gsl_spmatrix_free(mat);
                        return wanted_move;
                    }
                    else{
                        // we change only x 
                        wanted.y = last_up.y;
                        wanted_move = position_to_move(mat,wanted,p1);
                        if(check_summet(player_g,wanted_move.m)){
                            add_move(player_g,wanted_move);
                            last_up = mov_to_pos(wanted_move,s,mat);
                            gsl_spmatrix_free(mat);
                            return wanted_move;
                        }
                        else{
                            wanted.x = last_up.x + 1;
                            wanted.y = last_up.y;
                            wanted_move = position_to_move(mat,wanted,p1);
                            if(check_summet(player_g,wanted_move.m)){
                                add_move(player_g,wanted_move);
                                last_up = mov_to_pos(wanted_move,s,mat);
                                gsl_spmatrix_free(mat);
                                return wanted_move;
                            }
                            else{
                                wanted.x = last_up.x;
                                wanted.y = last_up.y+1;
                                wanted_move = position_to_move(mat,wanted,p1);
                                if(check_summet(player_g,wanted_move.m)){
                                    add_move(player_g,wanted_move);
                                    last_up = mov_to_pos(wanted_move,s,mat);
                                    gsl_spmatrix_free(mat);
                                    return wanted_move;
                                }
                                // random pick 
                                else{
                                    struct move_t r = rand_mov(previous_move,p1,player_g);
                                    last = r;
                                    add_move(player_g,r);
                                    last_up = mov_to_pos(last,s,mat);
                                    last_down = mov_to_pos(last,s,mat);
                                    gsl_spmatrix_free(mat);
                                    return r;
                                }
                            }
                        }
                    }
                }
                else{
                    struct couple wanted = {last_down.x-1,last_down.y};
                    struct move_t wanted_move = position_to_move(mat,wanted,p1);
                    if(check_summet(player_g,wanted_move.m)){
                        add_move(player_g,wanted_move);               
                        last_down = mov_to_pos(wanted_move,s,mat);
                        gsl_spmatrix_free(mat);
                        return wanted_move;
                    }
                    // its just random for the moment 
                    else{
                        struct move_t r = rand_mov(previous_move,p1,player_g);
                        last = r;
                        add_move(player_g,r);
                        last_up = mov_to_pos(last,s,mat);
                        last_down = mov_to_pos(last,s,mat);
                        gsl_spmatrix_free(mat);
                        return r;
                    }
                }
            }
        }
    }
}



void finalize()
{
    free_graphe(player_g);
}

