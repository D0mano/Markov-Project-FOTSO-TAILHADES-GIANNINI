#ifndef __HASSE_H__
#define __HASSE_H__
#include "types.h"

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

t_tarjan_vertex *initTarjanVertices(int n);

/**
 * @param name The name of the class.
 * @return A new class with the given name
 */
t_class *createClass(const char *name);

typedef struct {
    int *data;
    int top;
    int capacity;
} t_stack;

t_class_cell* createClassCell(t_tarjan_vertex vertex);
t_class_list createEmptyClassList();
int isEmptyClassList(t_class_list list);
void addClassCell(t_class* class,t_tarjan_vertex vertex);
void displayClass(t_class class);
int compareTwoClasses(t_class C1, t_class C2);
int getClassIndex(t_class class, t_partition partition);

/**
 * @return A new partition
 */
t_partition *createPartition();

t_partition_cell* createPartitionCell(t_class class);
t_partition_list createEmptyPartitionList();
void addPartitionCell(t_partition* p,t_class class);
int isEmptyPartitionList(t_partition_list list);
void displayPartition(t_partition p);


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


/**
 * @brief go through the graph
 * @param v id of the edge of our graph
 * @param num temporary number, marks the order in which nodes are visited during DFS
 * @param p is an empty partition
 * @param s is an empty stack
 * @param graph is a graph
 * @param vertices
 */
void parcours(int v, int *num, t_partition *p, t_stack *s, t_adjacency_list* graph, t_tarjan_vertex *vertices);
#endif

t_partition tarjan(t_adjacency_list* graph, t_tarjan_vertex *vertices);

t_link_array createEmptyLinkArray(int capacity);
int doesLinkExist(t_link_array p_link_array, int p1, int p2);
void addLink(t_link_array * p_link_array, t_link link);
void displayLinksArray(t_link_array p_link_array, t_partition partition);
void removeTransitiveLinks(t_link_array *p_link_array);
t_class getClassFromVertex(t_tarjan_vertex vertex, t_partition partition);
void makeLinks(t_link_array *p_link_array, t_tarjan_vertex *vertices, t_adjacency_list graph, t_partition partition);

void getCharacteristics(t_link_array links, t_partition partition);