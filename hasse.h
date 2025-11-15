#ifndef __HASSE_H__
#define __HASSE_H__
#include "types.h"


typedef struct s_cell{
    struct s_cell* arrival;
    struct s_cell* next;
    int arrival_vertex;
    float probability;
} t_cell;

typedef t_cell* p_cell;

typedef struct s_list {
    t_cell* head;
}t_list;

typedef struct s_adjacency_list {
    int size;
    t_list* tab;
} t_adjacency_list;

/**
 * @brief Create a cell with the value
 * @param vertice An int representing the vertice
 * @param prob A float representing the probability of the vertice
 * @return A pointers to a t_cell
 */
t_cell* createCell(int vertice, float prob);

/**
 * @brief Create an Empty linked list
 * @return The empty list
 */
t_list createEmptyList();

/**
 * @brief Check if the linked list is Empty
 * @param list The list who will be verified
 * @return
 */
int isEmptyList(t_list list);

/**
 * @brief Add a cell with the vertice and his probability in the list
 * @param list The list where the vertice will be added
 * @param vertice An int representing the vertice added to the linked list
 * @param prob A float representing the probability of the added vertice
 */
void addCell(t_list* list,int vertice, float prob);

/**
 * @brief Display the linked list
 * @param list The list to be displayed
 */
void displayList(t_list list);

/**
 *
 * @param nb_vertices The size of your adjacency list
 * @return The adjacency list
 */
t_adjacency_list* createAdjList(int nb_vertices);

/**
 * @brief Display an adjacency list
 * @param adj The adjacency list to be displayed
 */
void displayAdjList(t_adjacency_list* adj);


void removeTransitiveLinks(t_link_array *p_link_array);

/**
 * @brief Read a graph from a file and return the adjacency list representation.
 *
 * @param filename The name of the file from which the graph will be read.
 * @return The adjacency list representation of the graph.
*/
t_adjacency_list* readGraph(const char *filename);

/**
 * @brief Creates a link array from the given partition and graph.
 *
 * @param part The partition of the graph.
 * @param graph The adjacency list representation of the graph.
 * @return The created link array.
 */
void freeAdjList(t_adjacency_list* adj);

/**
 * @brief Check if the adjacency list is a Markov graph
 * @param adj The adjacency list to be verified
 */
void isMarkov(t_adjacency_list* adj);

/**
 * @brief Give you a string of character associated with an integer
 * @param num The number to be converted
 * @return The associated string character
 */


/**
 * @brief Convert a markov graph into a text file containing the mermaid code of the graph
 * @param adj The adjacency list
 */
void Markov_to_graph(t_adjacency_list* adj);

typedef struct {
    int id;
    int num;
    int lowlink;
    int inStack;
} t_tarjan_vertex;

typedef struct s_class_cell {
    struct s_class_cell *next;
    t_tarjan_vertex vertex;
}t_class_cell;

typedef struct s_class_list {
    t_class_cell* head;
}t_class_list;

typedef struct {
    char name[10];
    t_class_list vertices;
    int size;
} t_class;

typedef struct {
    t_class **classes;
    int size;
    int capacity;
} t_partition;

t_tarjan_vertex *initTarjanVertices(int n);

/**
 * @param name The name of the class.
 * @return A new class with the given name
 */
t_class *createClass(const char *name);

/**
 * @return A new partition
 */
t_partition *createPartition();

typedef struct {
    int *data;
    int top;
    int capacity;
} t_stack;
t_class_cell* createClassCell(t_tarjan_vertex vertex);
t_class_list createEmptyClassList();
int isEmptyClassList(t_class_list list);
void addClassCell(t_class_list* list,t_tarjan_vertex vertex);


/**
 * @brief Initialize the stack
 * @param capacity The maximum number of elements the stack can hold
 * @return A new stack
 */
t_stack *createStack(int capacity);
int isEmpty(t_stack *s);
int pop(t_stack *s);
void push(t_stack *s, int value);
void freePartition(t_partition *p);
void freeStack(t_stack *s);



void parcours(t_list edge,t_stack *stack,t_tarjan_vertex* vertice,t_partition* partition,int id,int num);
#endif