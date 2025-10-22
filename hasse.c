#include <malloc.h>
#include "hasse.h"
#include <stdlib.h>
#include <stdio.h>
#include "types.h"

t_cell* createCell(int value) {
    t_cell* cell = (t_cell*) malloc(sizeof(t_cell));
    cell->value = value;
    cell->next = NULL;
    cell->arrival = NULL;
    return cell;
}
t_list createEmptyList() {
    t_list list;
    list.head = NULL;
    return list;
}
int isEmptyList(t_list list) {
    return list.head == NULL;
}
void addCell(t_list* list,int val) {
    t_cell* new_cell = createCell(val);
    if (isEmptyList(*list)) {
        list->head = new_cell;
    }else {
        t_cell* cur = list->head;
        while (cur->next != NULL) {
            cur = cur->next;
        }
        cur->next = new_cell;
    }
}
void displayList(t_list list){
    t_cell* cur = list.head;
    printf("[head|@]->");
    while (cur != NULL) {
        printf("[%d|@]->", cur->value);
        cur = cur->next;
    }
    printf("NULL\n");
}
t_adjacency_list* createAdjList(int nb_vertices) {
    t_adjacency_list* adjacency_list = (t_adjacency_list*) malloc(sizeof(t_adjacency_list));
    adjacency_list->size = nb_vertices;
    adjacency_list->tab = (t_list*) malloc(adjacency_list->size * sizeof(t_list));
    for (int i = 0; i < adjacency_list->size; i++) {
        adjacency_list->tab[i] = createEmptyList();
    }
    return adjacency_list;
}
void displayAdjList(t_adjacency_list* adj) {
    for (int i = 0; i < adj->size; i++) {
        printf("List for vertex %d:",i);
        displayList(adj->tab[i]);
    }
}


void removeTransitiveLinks(t_link_array *p_link_array)
{
    int i = 0;
    while (i < p_link_array->log_size)
    {
        t_link link1 = p_link_array->links[i];
        int j = 0;
        int to_remove = 0;
        while (j < p_link_array->log_size && !to_remove)
        {
            if (j != i)
            {
                t_link link2 = p_link_array->links[j];
                if (link1.from == link2.from)
                {
                    // look for a link from link2.to to link1.to
                    int k = 0;
                    while (k < p_link_array->log_size && !to_remove)
                    {
                        if (k != j && k != i)
                        {
                            t_link link3 = p_link_array->links[k];
                            if ((link3.from == link2.to) && (link3.to == link1.to))
                            {
                                to_remove = 1;
                            }
                        }
                        k++;
                    }
                }
            }
            j++;
        }
        if (to_remove)
        {
            // remove link1 by replacing it with the last link
            p_link_array->links[i] = p_link_array->links[p_link_array->log_size - 1];
            p_link_array->log_size--;
        }
        else
        {
            i++;
        }
    }
}
