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
 * @return 1 if empty, 0 otherwise
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
 * @brief Create an adjacency list structure
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
 * @param filename The name of the file from which the graph will be read.
 * @return The adjacency list representation of the graph.
*/
t_adjacency_list* readGraph(const char *filename);

/**
 * @brief Free the memory allocated for the adjacency list
 * @param adj The adjacency list to free
 */
void freeAdjList(t_adjacency_list* adj);

/**
 * @brief Check if the adjacency list is a Markov graph
 * @param adj The adjacency list to be verified
 */
void isMarkov(t_adjacency_list* adj);

/**
 * @brief Convert a markov graph into a text file containing the mermaid code of the graph
 * @param adj The adjacency list
 */
void Markov_to_graph(t_adjacency_list* adj);

/**
 * @brief Initialize the array of vertices used for Tarjan's algorithm
 * @param n The number of vertices in the graph
 * @return A pointer to the array of t_tarjan_vertex
 */
t_tarjan_vertex *initTarjanVertices(int n);

/**
 * @brief Create a new class structure with a name
 * @param name The name of the class.
 * @return A new class with the given name
 */
t_class *createClass(const char *name);

typedef struct {
    int *data;
    int top;
    int capacity;
} t_stack;

/**
 * @brief Create a cell for a class linked list
 * @param vertex The Tarjan vertex to store in the cell
 * @return A pointer to the new class cell
 */
t_class_cell* createClassCell(t_tarjan_vertex vertex);

/**
 * @brief Create an empty class list
 * @return An empty t_class_list
 */
t_class_list createEmptyClassList();

/**
 * @brief Check if a class list is empty
 * @param list The class list to check
 * @return 1 if empty, 0 otherwise
 */
int isEmptyClassList(t_class_list list);

/**
 * @brief Add a vertex to a class
 * @param class The class to modify
 * @param vertex The vertex to add
 */
void addClassCell(t_class* class, t_tarjan_vertex vertex);

/**
 * @brief Display the content of a class
 * @param class The class to display
 */
void displayClass(t_class class);

/**
 * @brief Compare two classes to see if they are identical
 * @param C1 The first class
 * @param C2 The second class
 * @return 1 if they are the same, 0 otherwise
 */
int compareTwoClasses(t_class C1, t_class C2);

/**
 * @brief Get the index of a specific class within a partition
 * @param class The class to find
 * @param partition The partition to search in
 * @return The index of the class, or -1 if not found
 */
int getClassIndex(t_class class, t_partition partition);

/**
 * @brief Create a new empty partition structure
 * @return A pointer to the new partition
 */
t_partition *createPartition();

/**
 * @brief Create a cell for the partition linked list (which holds a class)
 * @param class The class to store in the cell
 * @return A pointer to the new partition cell
 */
t_partition_cell* createPartitionCell(t_class class);

/**
 * @brief Create an empty list of partitions
 * @return An empty t_partition_list
 */
t_partition_list createEmptyPartitionList();

/**
 * @brief Add a class to a partition
 * @param p The partition to modify
 * @param class The class to add
 */
void addPartitionCell(t_partition* p, t_class class);

/**
 * @brief Check if the partition list is empty
 * @param list The partition list to check
 * @return 1 if empty, 0 otherwise
 */
int isEmptyPartitionList(t_partition_list list);

/**
 * @brief Display the content of a partition
 * @param p The partition to display
 */
void displayPartition(t_partition p);

/**
 * @brief Initialize the stack
 * @param capacity The maximum number of elements the stack can hold
 * @return A new stack pointer
 */
t_stack *createStack(int capacity);

/**
 * @brief Check if the stack is empty
 * @param s The stack to check
 * @return 1 if empty, 0 otherwise
 */
int isEmpty(t_stack *s);

/**
 * @brief Remove and return the top element of the stack
 * @param s The stack to pop from
 * @return The value at the top of the stack
 */
int pop(t_stack *s);

/**
 * @brief Add a value to the top of the stack
 * @param s The stack to push to
 * @param value The value to add
 */
void push(t_stack *s, int value);

/**
 * @brief Free the memory allocated for a partition
 * @param p The partition to free
 */
void freePartition(t_partition *p);

/**
 * @brief Free the memory allocated for a stack
 * @param s The stack to free
 */
void freeStack(t_stack *s);

/**
 * @brief Recursive function to traverse the graph (Depth First Search) for Tarjan's algorithm
 * @param v id of the current vertex being visited
 * @param num temporary number, marks the order in which nodes are visited
 * @param p The partition being built
 * @param s The stack used for the algorithm
 * @param graph The graph being traversed
 * @param vertices The array of Tarjan vertices info
 */
void parcours(int v, int *num, t_partition *p, t_stack *s, t_adjacency_list* graph, t_tarjan_vertex *vertices);

/**
 * @brief Main execution of Tarjan's algorithm to find Strongly Connected Components (SCCs)
 * @param graph The graph to analyze
 * @param vertices The array of Tarjan vertices
 * @return A partition containing the SCCs
 */
t_partition tarjan(t_adjacency_list* graph, t_tarjan_vertex *vertices);

/**
 * @brief Initialize an empty link array (for Hasse diagram edges)
 * @param capacity The maximum capacity of links
 * @return An initialized t_link_array
 */
t_link_array createEmptyLinkArray(int capacity);

/**
 * @brief Check if a link already exists in the array
 * @param p_link_array The array of links
 * @param p1 The source identifier (e.g., class index)
 * @param p2 The destination identifier
 * @return 1 if link exists, 0 otherwise
 */
int doesLinkExist(t_link_array p_link_array, int p1, int p2);

/**
 * @brief Add a new link to the array
 * @param p_link_array Pointer to the link array
 * @param link The link structure to add
 */
void addLink(t_link_array * p_link_array, t_link link);

/**
 * @brief Display the array of links (connections between classes)
 * @param p_link_array The array of links
 * @param partition The partition associated with these links (for naming)
 */
void displayLinksArray(t_link_array p_link_array, t_partition partition);

/**
 * @brief Remove transitive links to reduce the graph to a Hasse diagram
 * @param p_link_array Pointer to the link array to optimize
 */
void removeTransitiveLinks(t_link_array *p_link_array);

/**
 * @brief Retrieve the Class containing a specific vertex
 * @param vertex The vertex to search for
 * @param partition The partition containing all classes
 * @return The class containing the vertex
 */
t_class getClassFromVertex(t_tarjan_vertex vertex, t_partition partition);

/**
 * @brief Generate links between classes based on the original graph connections
 * @param p_link_array Pointer to the link array to fill
 * @param vertices Array of Tarjan vertices
 * @param graph The original adjacency list
 * @param partition The partition of SCCs
 */
void makeLinks(t_link_array *p_link_array, t_tarjan_vertex *vertices, t_adjacency_list graph, t_partition partition);

/**
 * @brief Convert a class linked list into an array of integers
 * @param class a class of a graph
 * @return an array of integers
 */
int * LinkedClass_to_Arrays(t_class class);

/**
 * @brief Compute and display characteristics of the Hasse diagram (e.g., levels, depth)
 * @param links The array of optimized links
 * @param partition The partition of classes
 */
void getCharacteristics(t_link_array links, t_partition partition);


/**
 * @brief Use a list of link to create  into a text file containing the mermaid code of the graph
 * @param link
 * @param p
 */
void Link_to_Graph(t_link_array link,t_partition p);

#endif