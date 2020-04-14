#ifndef _HEX_GRAPH_H_
#define _HEX_GRAPH_H_

#include <stdlib.h>
#include <gsl/gsl_spmatrix.h>

struct graph_t {
  size_t num_vertices;  //! Number of vertices in the graph
  gsl_spmatrix* t;      //! Sparse matrix of size n*n,
                        //! t[i][j] == 1 means there is an edge from i to j
  gsl_spmatrix* o;      //! Sparse matrix of size 2*n, one line per player
                        //! o[p][i] == 1 means that the vertex i is owned by p
};
//! this function generates hexagnal graph 
struct graph_t *hex_graph(unsigned int m);
//! this function generates a squre graph 
struct graph_t *square_graph(unsigned int m);
//! this function generates a triangular graph  
struct graph_t *triang_graph(unsigned int m);
//! this function frees the graph
void free_graphe(struct graph_t * grph);
void free_principale(struct graph_t * grph);
void print_graph(struct graph_t * grp);
void copy_graph(struct graph_t * dst , struct graph_t * src);
#endif // _HEX_GRAPH_H_
