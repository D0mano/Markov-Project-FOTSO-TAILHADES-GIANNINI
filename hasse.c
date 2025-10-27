#include <malloc.h>
#include "hasse.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "types.h"

t_cell* createCell(int arrival_vertex, float prob) {
    t_cell* cell = (t_cell*) malloc(sizeof(t_cell));
    cell->arrival_vertex = arrival_vertex;
    cell->probability = prob;
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
void addCell(t_list* list, int arrival_vertex, float prob) {
    t_cell* new_cell = createCell(arrival_vertex, prob);
    if (isEmptyList(*list)) {
        list->head = new_cell;
    }else {
        t_cell* cur = list->head;
        while (cur->next != NULL) {
            cur = cur->next;
        }
        new_cell->arrival = cur;
        cur->next = new_cell;
    }
}
void displayList(t_list list){
    t_cell* cur = list.head;
    printf("[head|@]->");
    while (cur != NULL) {
        printf("[(%d, %g)|@]->", cur->arrival_vertex, cur->probability);
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

void freeAdjList(t_adjacency_list* adj) {
    if (adj == NULL) {
        return;
    }
    for (int i = 0; i < adj->size; i++) {
        t_cell* current = adj->tab[i].head;
        while (current != NULL) {
            t_cell* to_free = current;
            current = current->next;
            free(to_free);
        }
    }
    free(adj->tab);
    free(adj);
}

t_adjacency_list* readGraph(const char *filename) {
    FILE *file = fopen(filename, "rt");
    if (file == NULL) {
        perror("Could not open file for reading");
        exit(EXIT_FAILURE);
    }

    int nbvert, start, end;
    float proba;

    if (fscanf(file, "%d", &nbvert) != 1) {
        perror("Could not read number of vertices");
        fclose(file);
        exit(EXIT_FAILURE);
    }

    t_adjacency_list *graph = createAdjList(nbvert);

    while (fscanf(file, "%d %d %f", &start, &end, &proba) == 3) {
        addCell(&(graph->tab[start - 1]), end, proba);
    }

    fclose(file);
    return graph;
}

void isMarkov(t_adjacency_list* adj) {
    for (int i = 0; i < adj->size; i++) {
        t_list list = adj->tab[i];
        p_cell curr = list.head;
        float sum = 0;
        while (curr != NULL) {
            sum += curr->probability;
            curr = curr->next;
        }
        if (sum > 1 || sum < 0.99) {
            printf("The graph is not a Markov graph\n");
            printf("The sum of vertex %d is %g\n", i, sum);
            return;
        }
    }
    printf("The graph is a Markov graph\n");
    printf("For each vertex, the sum of probabilities is 1\n");
}

char *getID(int num) {
    if (num < 1) {
        return NULL;
    }

    // Calculate the length needed for the result
    int len = 0;
    int temp = num;
    while (temp > 0) {
        len++;
        temp = (temp - 1) / 26;
    }

    // Allocate memory for the result (+1 for null terminator)
    char *result = (char *)malloc((len + 1) * sizeof(char));
    if (result == NULL) {
        return NULL;
    }

    // Fill the string from right to left
    result[len] = '\0';
    temp = num;

    for (int i = len - 1; i >= 0; i--) {
        temp--;
        result[i] = 'A' + (temp % 26);
        temp /= 26;
    }

    return result;
}

void Markov_to_graph(t_adjacency_list* adj) {
    FILE* graph;
    graph = fopen("../graph.txt", "w");
    fprintf(graph,"---\n"
                        "config:\n"
                        "   theme: neo\n"
                        "   look: neo\n"
                        "   layout: elk\n"
                        "---");
    fprintf(graph, "\n\n"
                        "flowchart LR\n");
    for (int i = 0; i < adj->size; i++) {
        fprintf(graph,"%s((%d))\n",getID(i+1),i+1);
    }
    fprintf(graph, "\n");
    for (int i = 0; i < adj->size; i++) {
        t_list list = adj->tab[i];
        t_cell* cur = list.head;
        while (cur != NULL) {
            fprintf(graph,"%s -->|%.2f|%s\n",getID(i+1),cur->probability,getID(cur->arrival_vertex));
            cur = cur->next;
        }
    }
    fclose(graph);
}

t_tarjan_vertex *initTarjanVertices(int n) {
    t_tarjan_vertex *vertices = malloc(n * sizeof(t_tarjan_vertex));
    for (int i = 0; i < n; i++) {
        vertices[i].id = i;
        vertices[i].num = -1;
        vertices[i].lowlink = -1;
        vertices[i].inStack = 0;
    }
    return vertices;
}

t_class *createClass(const char *name) {
    t_class *c = malloc(sizeof(t_class));
    strcpy(c->name, name);
    c->size = 0;
    c->capacity = 4;
    c->vertices = malloc(c->capacity * sizeof(t_tarjan_vertex *));
    return c;
}

t_partition *createPartition() {
    t_partition *p = malloc(sizeof(t_partition));
    p->size = 0;
    p->capacity = 4;
    p->classes = malloc(p->capacity * sizeof(t_class *));
    return p;
}


t_stack *createStack(int capacity) {
    t_stack *s = malloc(sizeof(t_stack));
    s->data = malloc(capacity * sizeof(int));
    s->top = -1;
    s->capacity = capacity;
    return s;
}
void freeStack(t_stack *s) {
    if (s) {
        free(s->data);
        free(s);
    }
}

void freePartition(t_partition *p) {
    if (p) {
        free(p->classes);
        free(p);
    }
}

void push(t_stack *s, int v) { s->data[++s->top] = v; }
int pop(t_stack *s) { return s->data[s->top--]; }
int isEmpty(t_stack *s) { return s->top == -1; }






