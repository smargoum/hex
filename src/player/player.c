#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "player.h"
#include"strategy.h"

struct player
{
    char player_name[100];
    enum color_t player_color;
};

struct player p1;

/*! Access to player informations
  RETURNS:
  - the player name as an [a-zA-Z0-9 -_]* string
 */
char const *get_player_name()
{
    strcpy(p1.player_name, "lasjr_random");
    return "lasjr_random";
}

struct graph_t *player_g=NULL;



/*! Returns a sequence of three moves for an opening
  PRECOND:
  - a call to initialize_graph has been made
  RETURNS:
  - a correct move inside the graph
 */

struct move_t propose_opening()
{
    int s = (int)sqrt(player_g->num_vertices) - 1;
    struct move_t m = {2*s,p1.player_color};
    return m; 
}

/*! Acceptation of the opening
  PARAM:
  - opening : a move inside the graph
  PRECOND:
  - a call to initialize_graph has been made
  - the move is valid with regard to this graph
  RETURNS:
  - a boolean telling if the player accepts the opening
 */

int accept_opening(const struct move_t opening)
{
    const struct move_t op = propose_opening();
    if (opening.m == op.m)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

/*! Player graph initialization
  PARAM:
  - graph : the graph where the game is played
  PRECOND:
  - `graph` is a heap-allocated copy of the graph where the game is
    played, that must be freed in the end
  - initialize_graph has never been called before
 */

void initialize_graph(struct graph_t *graph)
{
    player_g=graph;
}
/*! Player color initialization
  PARAM:
  - id : the color assigned to the player
  PRECOND:
  - id is either BLACK or WHITE
  - initialize_color has never been called before
 */
void initialize_color(enum color_t id)
{
    p1.player_color = id;
    printf("color initialize at : %d \n",p1.player_color);
}

/*! Checks the move
  PARAM:
  - graph renewed with the previous move, summet decided by the player
  RETURNS:
  - If the summet can be occupied or not.
*/

int check_summet(struct graph_t *grph, unsigned int s)
{
    return !(gsl_spmatrix_get(grph->o, 0, s) || gsl_spmatrix_get(grph->o, 1, s));
}
/*! Adds an acceptable move to a graph
  PARAM:
  - old graph, move of either of the players
  RETURNS:
  - new graph
*/
void add_move(struct graph_t *grph, struct move_t mv)
{
    gsl_spmatrix_set(grph->o, mv.c, mv.m, 1);
}
// c'est le random player

/*! Computes next move
  PARAM:
  - previous_move: the move from the previous player
  RETURNS:
  - the next move for the player.
 */
struct move_t play(struct move_t previous_move)
{
    add_move(player_g, previous_move);      
    struct move_t mv = rand_mov(previous_move,p1,player_g);
    add_move(player_g, mv);
    return mv;
}

/*! Announces the end of the game to the player, and cleans up the
   memory he may have been using.
    POSTCOND:
  - every allocation done during the calls to initialize and play
    functions must have been freed
*/

void finalize()
{
    free_graphe(player_g);
}

