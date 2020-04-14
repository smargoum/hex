#include "main_aux.h"
#include "../graph.h"
#include "../move.h"
#include "../player/player.h"
#include <stdio.h>


void test__is_winning()
{
    int all_success = 1;

    // TEST 1 : SQUARE GRAPH
    struct graph_t * s_graph = square_graph(3);
    struct player_serv player = {.color = 1};
    if (is_winning(&player, s_graph) != 0) {
        printf("\033[31;01mFAIL\033[00m for function is_winning 1\n");
        all_success = 0;
    }

    gsl_spmatrix_set(s_graph->o, 1, 5, 1);
    if (is_winning(&player, s_graph) != 0) {
        printf("\033[31;01mFAIL\033[00m for function is_winning 2\n");
        all_success = 0;
    }

    gsl_spmatrix_set(s_graph->o, 1, 6, 1);
    if (is_winning(&player, s_graph) != 1) {
        printf("\033[31;01mFAIL\033[00m for function is_winning 3\n");
        all_success = 0;
    }

    gsl_spmatrix_set(s_graph->o, 1, 9, 1);
    gsl_spmatrix_set(s_graph->o, 1, 10, 1);

    if (is_winning(&player, s_graph) != 1) {
        printf("\033[31;01mFAIL\033[00m for function is_winning 4\n");
        all_success = 0;
    }

    free_graphe(s_graph);

    // TEST 2 : HEX GRAPH
    struct graph_t * h_graph = hex_graph(3);

    if (is_winning(&player, h_graph) != 0) {
        printf("\033[31;01mFAIL\033[00m for function is_winning 5\n");
        all_success = 0;
    }

    gsl_spmatrix_set(h_graph->o, 1, 5, 1);
    if (is_winning(&player, h_graph) != 0) {
        printf("\033[31;01mFAIL\033[00m for function is_winning 6\n");
        all_success = 0;
    }

    gsl_spmatrix_set(h_graph->o, 1, 9, 1);
    if (is_winning(&player, h_graph) != 0) {
        printf("\033[31;01mFAIL\033[00m for function is_winning 7\n");
        all_success = 0;
    }

    gsl_spmatrix_set(h_graph->o, 1, 10, 1);
    if (is_winning(&player, h_graph) != 1) {
        printf("\033[31;01mFAIL\033[00m for function is_winning 8\n");
        all_success = 0;
    }

    free_graphe(h_graph);

    // TEST 3 : TRIANGULAR GRAPH
    struct graph_t * t_graph = triang_graph(2);

    if (is_winning(&player, t_graph) != 0) {
        printf("\033[31;01mFAIL\033[00m for function is_winning 9\n");
        all_success = 0;
    }

    gsl_spmatrix_set(t_graph->o, 1, 14, 1);
    gsl_spmatrix_set(t_graph->o, 1, 15, 1);
    if (is_winning(&player, t_graph) != 0) {
        printf("\033[31;01mFAIL\033[00m for function is_winning 10\n");
        all_success = 0;
    }

    gsl_spmatrix_set(t_graph->o, 1, 21, 1);
    gsl_spmatrix_set(t_graph->o, 1, 22, 1);
    if (is_winning(&player, t_graph) != 0) {
        printf("\033[31;01mFAIL\033[00m for function is_winning 11\n");
        all_success = 0;
    }

    gsl_spmatrix_set(t_graph->o, 1, 6, 1);
    gsl_spmatrix_set(t_graph->o, 1, 7, 1);
    if (is_winning(&player, t_graph) != 1) {
        printf("\033[31;01mFAIL\033[00m for function is_winning 12\n");
        all_success = 0;
    }

    free_graphe(t_graph);

    if (all_success == 1)
        printf("\033[32;01mSUCCESS\033[00m for for the function is_winning\n");
}


void test__is_full()
{
    int all_success = 1;

    struct graph_t * s_graph = square_graph(3);
    if (is_full(s_graph) != 0) {
        printf("\033[31;01mFAIL\033[00m for function is_full 1\n");
        all_success = 0;
    }

    gsl_spmatrix_set(s_graph->o, 1, 5, 1);
    if (is_full(s_graph) != 0) {
        printf("\033[31;01mFAIL\033[00m for function is_full 2\n");
        all_success = 0;
    }

    gsl_spmatrix_set(s_graph->o, 1, 9, 1);
    gsl_spmatrix_set(s_graph->o, 0, 6, 1);
    gsl_spmatrix_set(s_graph->o, 0, 10, 1);
    if (is_full(s_graph) != 1) {
        printf("\033[31;01mFAIL\033[00m for function is_full 3\n");
        all_success = 0;
    }

     if (all_success == 1)
        printf("\033[32;01mSUCCESS\033[00m for for the function is_full\n");
}

int main()
{
    test__is_winning();
    test__is_full();
    return 0;
}
