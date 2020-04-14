#include "../graph.h"
#include "option.h"

size_t size_graph = 3;
struct graph_t *(*shape_foo)(unsigned int) = square_graph;
int parse_opts(int argc, char *argv[])
{
    int first_lib = 1;
    int opt;
    while ((opt = getopt(argc, argv, "t:m:")) != -1)
    {
        switch (opt)
        {
        case 't':
            switch(optarg[0])
            {
                case 't':
                    shape_foo = triang_graph;
                    break;
                case 'c':
                    shape_foo = square_graph;
                    break;
                case 'h':
                    shape_foo = hex_graph;
                    break;
                default:
                    fprintf(stderr, "Usage of : %s -t [c square_graph] [h hexagonal graph] [t triangular_graph] \n",
                        argv[0]);
                    exit(EXIT_FAILURE); 
            }
            first_lib = first_lib + 2;
            break;
        case 'm':
            if (atoi(optarg) > MAX_SIZE_GRAPH)
            {
                printf("Error in usage of %s  ----- \nWarning : MAX_SIZE_GRAPH = %d \n",
                        argv[0],MAX_SIZE_GRAPH);
                exit(EXIT_FAILURE);
            }
            else if (atoi(optarg) < MIN_SIZE_GRAPH)
            {
                printf("Error in usage of %s  ----- \nWarning : MIN_SIZE_GRAPH = %d \n",
                        argv[0],MIN_SIZE_GRAPH);
                exit(EXIT_FAILURE);
            }
            else 
            {
                size_graph = atoi(optarg);
            }
            first_lib = first_lib + 2;
            break;
        default: 
            fprintf(stderr, "Usage: %s [-s seed] [-n number of players] [-m number of turns]\n",
                    argv[0]);
            exit(EXIT_FAILURE);
        }
    }
    return first_lib;
}
/*
int main(int argc, char *argv[])
{
    int i = parse_opts(argc,argv);
    printf("m -> %ld \n",size_graph);
    printf("i -> %d \n",i);
    struct graph_t *graph_test = shape_foo(size_graph);
    print_graph(graph_test);
    printf("%s \n",argv[i]); // code 
    return 0;
}
*/
