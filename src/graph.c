#include "graph.h"


struct graph_t *hex_graph_old(unsigned int m){
    struct graph_t * grph=malloc(sizeof(struct graph_t));
    grph->num_vertices=(m+1)*(m+1);
    //grph->t=gsl_spmatrix_alloc(grph->num_vertices,grph->num_vertices);
    grph->t= gsl_spmatrix_alloc_nzmax(grph->num_vertices,grph->num_vertices, grph->num_vertices*4, GSL_SPMATRIX_CRS);
    grph->o=gsl_spmatrix_alloc(2,grph->num_vertices);
    unsigned int i=0,j=0;
    gsl_spmatrix_set(grph->o,1,i,1);
    while ((size_t)i<grph->num_vertices-1){
        if((size_t)i<(grph->num_vertices - (m+1))){
            if(i!=(m+(m+1)*j)){
                gsl_spmatrix_set(grph->t,i,i+1,1);
                gsl_spmatrix_set(grph->t,i,i+1+m,1);
                gsl_spmatrix_set(grph->t,i,i+2+m,1);
                gsl_spmatrix_set(grph->t,i+1,i,1);
                gsl_spmatrix_set(grph->t,i+1+m,i,1);
                gsl_spmatrix_set(grph->t,i+2+m,i,1);
            } else {
                gsl_spmatrix_set(grph->t,i,i+1+m,1);
                gsl_spmatrix_set(grph->t,i+m+1,i,1);
                if ((size_t)(i+1)!=(grph->num_vertices - (m+1))) {
                    gsl_spmatrix_set(grph->o,1,i+1,1);
                } else {
                    gsl_spmatrix_set(grph->o,1,grph->num_vertices-1,1);
                }
                if (j!=0) {
                    gsl_spmatrix_set(grph->o,1,i,1);
                } else {
                    gsl_spmatrix_set(grph->o,0,i,1);
                }
                j+=1;
            }
        } else {
            gsl_spmatrix_set(grph->t,i,i+1,1);
            gsl_spmatrix_set(grph->t,i+1,i,1);
            gsl_spmatrix_set(grph->o,0,i,1);
        }
        i+=1;
    }
    for (unsigned int k=1; k<m; k++){
        gsl_spmatrix_set(grph->o,0,k,1);
    }
    return grph;
}

struct graph_t *hex_graph(unsigned int m){
    struct graph_t * grph=malloc(sizeof(struct graph_t));
    grph->num_vertices=(m+1)*(m+1);
    //grph->t=gsl_spmatrix_alloc(grph->num_vertices,grph->num_vertices);
    grph->t= gsl_spmatrix_alloc_nzmax(grph->num_vertices,grph->num_vertices, 2*(grph->num_vertices*3-4*(m+1)+1), GSL_SPMATRIX_TRIPLET);
    grph->o=gsl_spmatrix_alloc_nzmax(2,grph->num_vertices,grph->num_vertices*2, GSL_SPMATRIX_TRIPLET);
    unsigned int i=0,j=0;
    gsl_spmatrix_set(grph->o,1,i,1);
    while ((size_t)i<grph->num_vertices-1){
        if((size_t)i<(grph->num_vertices - (m+1))){
            if(i!=(m+(m+1)*j)){
                gsl_spmatrix_set(grph->t,i,i+1,1);
                gsl_spmatrix_set(grph->t,i,i+1+m,1);
                gsl_spmatrix_set(grph->t,i,i+2+m,1);
                gsl_spmatrix_set(grph->t,i+1,i,1);
                gsl_spmatrix_set(grph->t,i+1+m,i,1);
                gsl_spmatrix_set(grph->t,i+2+m,i,1);
            } else {
                gsl_spmatrix_set(grph->t,i,i+1+m,1);
                gsl_spmatrix_set(grph->t,i+m+1,i,1);
                if ((size_t)(i+1)!=(grph->num_vertices - (m+1))) {
                    gsl_spmatrix_set(grph->o,1,i+1,1);
                } else {
                    gsl_spmatrix_set(grph->o,1,grph->num_vertices-1,1);
                }
                if (j!=0) {
                    gsl_spmatrix_set(grph->o,1,i,1);
                } else {
                    gsl_spmatrix_set(grph->o,0,i,1);
                }
                j+=1;
            }
        } else {
            gsl_spmatrix_set(grph->t,i,i+1,1);
            gsl_spmatrix_set(grph->t,i+1,i,1);
            gsl_spmatrix_set(grph->o,0,i,1);
        }
        i+=1;
    }
    for (unsigned int k=1; k<m; k++){
        gsl_spmatrix_set(grph->o,0,k,1);
    }
    return grph;
}

struct graph_t *square_graph(unsigned int m){
    struct graph_t * grph=malloc(sizeof(struct graph_t));
    grph->num_vertices=(m+1)*(m+1);
    grph->t=gsl_spmatrix_alloc(grph->num_vertices,grph->num_vertices);
    grph->o=gsl_spmatrix_alloc(2,grph->num_vertices);
    unsigned int i=0,j=0;
    gsl_spmatrix_set(grph->o,1,i,1);
    while ((size_t)i<grph->num_vertices-1){
        if((size_t)i<(grph->num_vertices - (m+1))){
            if(i!=(m+(m+1)*j)){
                gsl_spmatrix_set(grph->t,i,i+1,1);
                gsl_spmatrix_set(grph->t,i,i+1+m,1);
                gsl_spmatrix_set(grph->t,i+1,i,1);
                gsl_spmatrix_set(grph->t,i+1+m,i,1);
            } else {
                gsl_spmatrix_set(grph->t,i,i+1+m,1);
                gsl_spmatrix_set(grph->t,i+m+1,i,1);
                if ((size_t)(i+1)!=(grph->num_vertices - (m+1))) {
                    gsl_spmatrix_set(grph->o,1,i+1,1);
                } else {
                    gsl_spmatrix_set(grph->o,1,grph->num_vertices-1,1);
                }
                if (j!=0) {
                    gsl_spmatrix_set(grph->o,1,i,1);
                } else {
                    gsl_spmatrix_set(grph->o,0,i,1);
                }
                j+=1;
            }
        } else {
            gsl_spmatrix_set(grph->t,i,i+1,1);
            gsl_spmatrix_set(grph->t,i+1,i,1);
            gsl_spmatrix_set(grph->o,0,i,1);
        }
        i+=1;
    }
    for (unsigned int k=1; k<m; k++){
        gsl_spmatrix_set(grph->o,0,k,1);
    }
    return grph;
}

struct graph_t *triang_graph(unsigned int m){
    struct graph_t * grph=malloc(sizeof(struct graph_t));
    grph->num_vertices=6*(m*m);
    grph->t=gsl_spmatrix_alloc(grph->num_vertices,grph->num_vertices);
    grph->o=gsl_spmatrix_alloc(2,grph->num_vertices);
    unsigned int i=0,j=0,c=0,k=0;
    unsigned int L=0;
    gsl_spmatrix_set(grph->o,1,i,1);
    while (i<grph->num_vertices-1){
        if (i<grph->num_vertices-(2*m+1)) {
            if (i!=(2*(m+j)+k+(1*(j!=0)))){
                if (i%2==L){
                    gsl_spmatrix_set(grph->t,i,i+1,1);
                    gsl_spmatrix_set(grph->t,i+1,i,1);
                    gsl_spmatrix_set(grph->t,i,i+(2*(m+j)+1)+((j!=m-1) - (c==2)),1);
                    gsl_spmatrix_set(grph->t,i+(2*(m+j)+1)+((j!=m-1) - (c==2)),i,1);
                } else {
                    gsl_spmatrix_set(grph->t,i,i+1,1);
                    gsl_spmatrix_set(grph->t,i+1,i,1);
                }
            } else {
                k=i;
                gsl_spmatrix_set(grph->t,i,i+(2*(m+j)+1)+(1*(j!=m-1)),1);
                gsl_spmatrix_set(grph->t,i+(2*(m+j)+1)+(1*(j!=m-1)),i,1);
                if (j<m/2 && c==0) {
                    gsl_spmatrix_set(grph->o,0,i,1);
                    gsl_spmatrix_set(grph->o,0,i-1,1);
                    gsl_spmatrix_set(grph->o,1,i+1,1);
                    gsl_spmatrix_set(grph->o,1,i+2,1);
                } else {
                    if (j==m/2 && ((c-1)==0 || c==0)){
                        gsl_spmatrix_set(grph->o,1,i,1);
                        gsl_spmatrix_set(grph->o,1,i+1,1);
                        if (c==0) gsl_spmatrix_set(grph->o,1,i+2,1);
                    } else {
                        if (j>m/2){
                            gsl_spmatrix_set(grph->o,1,i-1,1);
                            gsl_spmatrix_set(grph->o,1,i,1);
                            if ((c==2) && j==((m/2)+1)) {
                                gsl_spmatrix_set(grph->o,1,i+1,1); //i+2
                            } else {
                                gsl_spmatrix_set(grph->o,1,i+1,1);
                                gsl_spmatrix_set(grph->o,1,i+2,1);
                            }
                        } else {
                            gsl_spmatrix_set(grph->o,1,i-1,1);
                            gsl_spmatrix_set(grph->o,1,i,1);
                            if (j<=m/2) {
                                gsl_spmatrix_set(grph->o,0,i+1,1);
                                gsl_spmatrix_set(grph->o,0,i+2,1);
                            }
                        }
                    }
                }
                if (j!=m-1) L=!(L);
                if (c==0) j++; else {
                    if (c==2) j--;
                    }
                if (j==m-1) c++;
            }
        } else {
            gsl_spmatrix_set(grph->t,i,i+1,1);
            gsl_spmatrix_set(grph->t,i+1,i,1);
            gsl_spmatrix_set(grph->o,0,i,1);
        }
        i++;
    }
    gsl_spmatrix_set(grph->o,1,grph->num_vertices-1,1);
    for (unsigned int n=1; n<=2*m; n++){
        gsl_spmatrix_set(grph->o,0,n,1);    
    }
    return grph;
}

void free_graphe(struct graph_t *grph){
    gsl_spmatrix_free(grph->t);
    gsl_spmatrix_free(grph->o);
    free(grph);
}

void free_principale(struct graph_t *grph)
{
    gsl_spmatrix_free(grph->t);
    gsl_spmatrix_free(grph->o);
    free(grph); 
}

void print_graph(struct graph_t *grp){
    printf("-- BEGIN PRINT GRAPH -- \n");
    printf("-- Graph has %ld summets --\n", grp->num_vertices);
    printf("Graph matrix : \n[");
    for (unsigned int i=0; i<grp->num_vertices; i++){
        if (i!=0 && i<10) printf(" %d[",i); else printf("%d[",i);
        for (unsigned int j=0; j<grp->num_vertices; j++){
            if (j!= grp->num_vertices-1 ) printf("%d,",(int)gsl_spmatrix_get(grp->t, i,j));
            else {printf("%d",(int)gsl_spmatrix_get(grp->t, i,j));}
        }
        if (i!=grp->num_vertices-1 ) printf("],\n");
        else {printf("]");}
    }
    printf("]\n");
    printf("Summets matrix of the playes :\n[");
    for (unsigned int i=0; i<2; i++){
        if (i!=0) printf(" ["); else printf("[");
        for (unsigned int j=0; j<grp->num_vertices; j++){
            if (j!= grp->num_vertices-1 ) printf("%d,",(int)gsl_spmatrix_get(grp->o, i,j)*(j+(j==0)));
            else {printf("%d",(int)gsl_spmatrix_get(grp->o, i,j)*j);}
        }
        if (i!=1) printf("],\n");
        else {printf("]");}
    }
    printf("]\n");
    printf("-- END PRINT GRAPH --\n");
}
void copy_graph(struct graph_t * dst , struct graph_t * src)
{
    dst->num_vertices = src->num_vertices;
    size_t n = src->num_vertices;
    dst->t = gsl_spmatrix_alloc(n, n);
    dst->o = gsl_spmatrix_alloc(2, n);
    gsl_spmatrix_memcpy(dst->t, src->t);
    gsl_spmatrix_memcpy(dst->o, src->o);
}


