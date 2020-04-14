#ifndef OPTION_H
#define OPTION_H

#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../graph.h"

#define MAX_SIZE_GRAPH 10000
#define MIN_SIZE_GRAPH 2

// Width of the graph
size_t size_graph;

// Shape of the graph
struct graph_t *(*shape_foo)(unsigned int);

/*
   Function for parsing the options of the program
   Currently available options are :
    * -m <m..> : sets the width of the graph
    * -t <t..> : sets the shape of the graph: 
                                                * t -> triangular
                                                * c -> square
                                                * h -> hexagonal
*/
int parse_opts(int argc, char *argv[]);

#endif