#ifndef MAIN_AUX
#define MAIN_AUX
#include "../move.h"
#include "../graph.h"
#include <dlfcn.h>

struct player_serv
{
  char const * name;
  enum color_t color;
  struct graph_t *own_graph;
  struct move_t (*propose_opening)();
  int (*accept_opening)(const struct move_t);
  void (*initialize_graph)(struct graph_t *);
  void (*initialize_color)(enum color_t);
  struct move_t (*play)(struct move_t);
  void (*finalize)();
};


/*! Initializes a player with its strategy
 * PARAM:
 * - player is an uninitialized player
 * - strat is the result of a dlopen
 */
void init_player(struct player_serv *player,void* strat);// int arg_pos, char *argv[]);


/*! A recursive graph search algorithm
 * PARAM:
 * - graph : the graph you want to search
 * - color : 0 (BLACK) or 1 (WHITE)
 * - current : a vertice
 * - visited : visited[i] == 1 means the vertice i already has been visited
 * PRECOND:
 * - the vertice current is of color color
 */
void parcours(struct graph_t* graph,enum color_t color, int* visited, int current);// ,int end);


/*! Determines if a player has won
 * PARAM:
 * - player : a valid initialized player
 * - graph : the game's current graph
 * PRECOND:
 * RETURNS:
 * - a boolean telling if the player has won
 */
int is_winning(struct player_serv *player, struct graph_t *graph);

/*! Determines if the board is fully colored
 * PARAM:
 * - graph : the game's current graph
 * PRECOND:
 * RETURNS:
 * - a boolean telling if the board is fully colored
 */
int is_full(struct graph_t * graph);
//this function prints the game board
void print_board(struct graph_t * g, size_t t);

#endif
