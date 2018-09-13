/**
    Developed by 
        Chrystian Melo
        Gabriel Siroco
        Samuel Henrique
*/

#ifndef LIBRARYGRAPHS_H_INCLUDED
#define LIBRARYGRAPHS_H_INCLUDED
 
struct node {
    
    //viaduct's data
    int height_go;
    int height_come;
 
    //city's data
    char name[100];
 
    //geral
    int id;//identifier every nodes
    int current_node;
    struct node *next;
 
};
 
typedef struct node viaduct;
typedef struct node city;
typedef struct node lists;

struct graphs {
    int vertex;
    struct node **list;
};
 
typedef struct graphs graph;

graph *createNewGraph();

void insertGraph(graph *g, viaduct v, int id);

void linkNodesGraph(graph *g, int id);

void printGraph(graph *g);

viaduct writeNodesGraph();

void removeGraph(graph *g, char name[], char otherName[], int choice);

void freeGraph(graph *g);

struct node *searchOnGraph(graph g, int id, char name[100]);

int otherSearch(graph g, int id, char name[100]);

void dijkstra(graph *gf, int part, int dest, int height_load);

//file
void graph_to_file(graph gr);

void file_to_graph(graph *gr);
//file

#endif
