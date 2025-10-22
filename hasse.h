#ifndef __HASSE_H__
#define __HASSE_H__
#include "types.h"


typedef struct s_cell{
    struct s_cell* arrival;
    struct s_cell* next;
    int value;
}t_cell;

typedef struct s_list {
    t_cell* head;
}t_list;

typedef struct s_adjacency_list {
    int size;
    t_list* tab;

}t_adjacency_list;

/**
 * @brief Create a cell with tha value
 * @param value The value in the cell
 * @return t_cell*  A pointers to a t_cell
 */
t_cell* createCell(int value);

/**
 * @brief Create an Empty linked list
 * @return The empty list
 */
t_list createEmptyList();

/**
 *
 * @param list The list who will be verified
 * @return
 */
int isEmptyList(t_list list);

/**
 * @brief Add a cell with the value in the list
 * @param list The list where the value will be added
 * @param val The value to be added to the list
 */
void addCell(t_list* list,int val);

/**
 *
 * @param list The list to be displayed
 */
void displayList(t_list list);

/**
 *
 * @param nb_vertices The size of your adjacency list
 * @return
 */
t_adjacency_list* createAdjList(int nb_vertices);

void displayAdjList(t_adjacency_list* adj);


void removeTransitiveLinks(t_link_array *p_link_array);

/**
 * @brief Creates a link array from the given partition and graph.
 *
 * @param part The partition of the graph.
 * @param graph The adjacency list representation of the graph.
 * @return The created link array.
 */

#endif