#include "main_aux.h"
#include <string.h>

void init_player(struct player_serv *player,void* strat)
{
  char const *(*get_player_name)() = dlsym(strat, "get_player_name");
  char const * name = get_player_name();
  player->name = name;
  //strcpy(player->name,name);
  //printf("name : %s \n",name);
  //struct graph_t (*own) = dlsym(strat,"g");
  //player->own_graph=own;
  struct move_t (*propose_opening)() = dlsym(strat, "propose_opening");
  player->propose_opening = propose_opening;
  int (*accept_opening)(const struct move_t) = dlsym(strat, "accept_opening");
  player->accept_opening = accept_opening;
  void (*initialize_graph)(struct graph_t *) = dlsym(strat, "initialize_graph");
  player->initialize_graph = initialize_graph;
  void (*initialize_color)(enum color_t) = dlsym(strat, "initialize_color");
  player->initialize_color = initialize_color;
  struct move_t (*play)(struct move_t) = dlsym(strat, "play");
  player->play = play;
  void (*finalize)() = dlsym(strat, "finalize");
  player->finalize = finalize;
}

void parcours(struct graph_t *graph, enum color_t color, int *visited, int current)
{
  visited[current] = 1;
  printf("current : %d \n",current);
  unsigned int i = 0;
  while (i < graph->num_vertices)
  {
    if (visited[i] == 0 && gsl_spmatrix_get(graph->t, current, i) == 1 && gsl_spmatrix_get(graph->o, color, i) == 1)
    {
      parcours(graph, color, visited, i); 
    }
    i++;
  }
}

int is_winning(struct player_serv *player, struct graph_t *graph)
{
  enum color_t color = player->color;
  int start;
  int end;
  if (color == 0)
  {
    start = 1;
    end = (graph->num_vertices) - 2;
  }
  else
  {
    start = 0;
    end = (graph->num_vertices) - 1;
  }
  int visited[graph->num_vertices];
  for (size_t i = 0; i < graph->num_vertices; i++)
    visited[i] = 0;
  parcours(graph, color, visited, start); //, end);
  return visited[end];
}

int is_full(struct graph_t * graph)
{
  size_t n = graph->num_vertices;

  for (size_t i = 0; i < n; i++) {
    if ( (gsl_spmatrix_get(graph->o, 0, i) == 0) && ( gsl_spmatrix_get(graph->o, 1, i) == 0))
      return 0;
  }
  
  return 1;
}
//this function prints the game board
void print_board(struct graph_t * g, size_t t)
{
  gsl_spmatrix * m = gsl_spmatrix_alloc(t+1,t+1);
  int k = 0;
  for(int i = 0 ; i <= (int)t ; i++){
    for(int j = 0 ; j <= (int)t ; j++){
      gsl_spmatrix_set(m,i,j,k);
      k++;
    }
  }
  printf("[");
  for(int i = 0 ; i <= (int)t ; i++){
    printf("[");
    for(int j = 0 ; j <= (int)t ; j++){
      int v = (int)gsl_spmatrix_get(m,i,j);
      if((int)gsl_spmatrix_get(g->o,0,v) == 1){
        printf(" b");
      }
      else if ((int)gsl_spmatrix_get(g->o,1,v) == 1){
        printf(" w");
      }
      else{
        printf(" x");
      }
    }
    printf("]\n");
  }
  printf("]\n");
  gsl_spmatrix_free(m);
}
