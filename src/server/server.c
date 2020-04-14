#include "option.h"
#include "main_aux.h"
#include "../player/player.h"

int main(int argc, char *argv[])
{
  int index_first_lib = parse_opts(argc,argv);
  struct player_serv *player1 = malloc(sizeof(struct player_serv));
  struct player_serv *player2 = malloc(sizeof(struct player_serv));
  struct player_serv *players[2] = {player1, player2};

  void *strat_1 = dlopen(argv[index_first_lib], RTLD_NOW);
  void *strat_2 = dlopen(argv[index_first_lib + 1], RTLD_NOW);

  init_player(player1, strat_1);
  init_player(player2, strat_2);

  //struct graph_t *main_graph = malloc(sizeof(struct graph_t));
  struct graph_t *main_graph = shape_foo(size_graph); // = initialize_graph()
  struct graph_t *graph_1=malloc(sizeof(struct graph_t));
  struct graph_t *graph_2=malloc(sizeof(struct graph_t));
  copy_graph(graph_1, main_graph);
  copy_graph(graph_2, main_graph);
  
  player1->initialize_graph(graph_1);
  player2->initialize_graph(graph_2);

  //init_graph(player1, 1, argv);
  //init_graph(player2, 2, argv);

  //printf("%d \n",player1->own_graph->num_vertices);

  struct move_t move = player1->propose_opening();
  int i;

  if (player2->accept_opening(move))
  {
    printf("player 1 :    ");
    player1->initialize_color(0);
    player1->color = 0;
    printf("player 2 :    ");
    player2->initialize_color(1);
    player2->color = 1;
    i = 0;
  }
  else
  {
    printf("player 1 :    ");
    player1->initialize_color(1);
    player1->color = 1;
    printf("player 2 :    ");
    player2->initialize_color(0);
    player2->color = 0;
    move = player2->propose_opening();
    i = 1;
  }

  add_move(main_graph, move);
  printf("OPENING : move : %ld | color : %d \n", move.m, move.c);

  while (1)
  {
    //print_board(main_graph,size_graph);
    i++;
    i = i % 2;
    struct player_serv *active_player = players[i];

    printf("********************new player -> color %d *******************\n", active_player->color);

    move = active_player->play(move);
    printf("move : %ld | color : %d \n", move.m, move.c);
    add_move(main_graph, move);
    if (is_winning(active_player, main_graph))
    {
      //printf("ah on est la \n");
      printf("%d a gg \n", active_player->color);
      break;
    } //TODO : players[i] fait ça
    if (is_full(main_graph)) { // If the board is full and there was no winner (tested with the previous if)
      // then its a draw
      printf("DRAW\n");
      break;
    }
  }
  printf("out of loop \n");

  // end_game
  free_principale(main_graph);
  for (int k = 0; k < 2; k++)
  {
    players[k]->finalize();
    free(players[k]);
  }
  
  dlclose(strat_2);
  dlclose(strat_1);
  return 0;
}

/*
for each player p
   p->initialize(graph)
move = first_player->propose_opening()
if second_player->accept_opening(move) // 2nd player plays next
   first_player->set_color(BLACK)
   second_player->set_color(WHITE)
else // 2nd player refuses and 1st player plays next
   first_player->set_color(WHITE)
   second_player->set_color(BLACK)
while true
   p = compute_next_player()
   move = p->play(move)
   if is_winning()
      break
for each player p
   p->finalize()
   */
