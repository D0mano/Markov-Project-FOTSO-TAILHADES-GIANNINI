#include <malloc.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "hasse.h"
#include "types.h"
#include "utils.h"

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

void Markov_to_graph(t_adjacency_list* adj) {
    FILE* graph;
    graph = fopen("../graph.mmd", "w");
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
        vertices[i].id = i+1;
        vertices[i].num = -1;
        vertices[i].lowlink = -1;
        vertices[i].inStack = 0;
    }
    return vertices;
}
t_class_cell* createClassCell(t_tarjan_vertex vertex) {
    t_class_cell* cell = (t_class_cell*) malloc(sizeof(t_class_cell));
    cell->vertex = vertex;
    cell->next = NULL;
    return cell;
}
t_class_list createEmptyClassList() {
    t_class_list list;
    list.head = NULL;
    return list;
}
t_class *createClass(const char *name){
    t_class *c = malloc(sizeof(t_class));
    strcpy(c->name,name);
    c->size = 0;
    c->vertices = createEmptyClassList();
    return c;
}
int isEmptyClassList(t_class_list list) {
    return list.head == NULL;
}
void addClassCell(t_class* class,t_tarjan_vertex vertex){
    t_class_cell* new_cell = createClassCell(vertex);
    t_class_list *list = &class->vertices;
    if (isEmptyClassList(*list)) {
        list->head = new_cell;
    }else {
        t_class_cell* cur = list->head;
        while (cur->next != NULL) {
            cur = cur->next;
        }
        cur->next = new_cell;
    }
    class->size++;
}
void displayClass(t_class class) {
    t_class_cell * curr = class.vertices.head;
    printf("%s: {", class.name);
    while (curr->next != NULL) {
        printf("%d,", curr->vertex.id);
        curr = curr->next;
    }
    printf("%d}",curr->vertex.id);
}

//PARTITION
t_partition_cell* createPartitionCell(t_class class) {
    t_partition_cell* new_cell = (t_partition_cell*) malloc(sizeof(t_partition_cell));
    new_cell->class = class;
    new_cell->next = NULL;
    return new_cell;
}
t_partition_list createEmptyPartitionList() {
    t_partition_list list;
    list.head = NULL;
    return list;
}
t_partition *createPartition() {
    t_partition *p = malloc(sizeof(t_partition));
    p->size = 0;
    p->classes = createEmptyPartitionList();
    return p;
}
int isEmptyPartitionList(t_partition_list list) {
    return list.head == NULL;
}
void addPartitionCell(t_partition* p,t_class class) {
    t_partition_cell* new_cell = createPartitionCell(class);
    t_partition_list* list = &p->classes;
    if (isEmptyPartitionList(*list)) {
        list->head = new_cell;
    } else {
        t_partition_cell* cur = list->head;
        while (cur->next != NULL) {
            cur = cur->next;
        }
        cur->next = new_cell;
    }
    p->size++;

}
void displayPartition(t_partition p) {
    t_partition_cell* curr = p.classes.head;
    printf("{");
    while (curr->next != NULL) {
        displayClass(curr->class);
        printf(", ");
        curr = curr->next;
    }
    displayClass(curr->class);
    printf("}\n");
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
        t_partition_cell * curr = p->classes.head;
        while (curr != NULL) {
            t_partition_cell * next = curr->next;
            free(curr);
            curr = next;
        }
    }
}

void push(t_stack *s, int v) { s->data[++s->top] = v; }
int pop(t_stack *s) { return s->data[s->top--]; }
int isEmpty(t_stack *s) { return s->top == -1; }

void parcours(int v, int *num, t_partition *p, t_stack *s, t_adjacency_list* graph, t_tarjan_vertex *vertices) {
    t_tarjan_vertex* vertex = &vertices[v];
    vertex->num = *num;
    vertex->lowlink = *num;
    *num = *num + 1;
    push(s, v);
    vertex->inStack = 1;
    p_cell curr = graph->tab[v].head;

    while (curr != NULL) {
        int w = curr->arrival_vertex-1;
        if (vertices[w].num == -1) {
            parcours(w, num, p, s, graph, vertices);
            if (vertex->lowlink > vertices[w].lowlink) {
                vertex->lowlink = vertices[w].lowlink;
            }
        } else if (vertices[w].inStack == 1) {
            if (vertex->lowlink > vertices[w].num) {
                vertex->lowlink = vertices[w].num;
            }
        }
        curr = curr->next;
    }

    if (vertex->lowlink == vertex->num) {
        char str[3];
        sprintf(str, "C%d", p->size+1);
        t_class *class = createClass(str);
        int w;
        do {
            w = pop(s);
            vertices[w].inStack = 0;
            addClassCell(class, vertices[w]);
        } while (w != v);
        addPartitionCell(p, *class);
    }
}

t_partition tarjan(t_adjacency_list* graph, t_tarjan_vertex *vertices) {
    t_partition *p = createPartition();
    t_stack *s = createStack(graph->size);
    int num = 0;
    for (int v = 0; v < graph->size; v++) {
        if (vertices[v].num == -1) {
            parcours(v, &num, p, s, graph, vertices);
        }
    }
    return *p;
}

t_class getClassFromVertex(t_tarjan_vertex vertex, t_partition partition) {
    t_partition_cell* curr_c = partition.classes.head;
    while (curr_c != NULL) {
        t_class_cell* curr_v = curr_c->class.vertices.head;
        while (curr_v != NULL) {
            if (curr_v->vertex.id == vertex.id) {
                return curr_c->class;
            }
            curr_v = curr_v->next;
        }
        curr_c = curr_c->next;
    }
}

int compareTwoClasses(t_class C1, t_class C2) {
    t_class_cell* curr_c1 = C1.vertices.head;
    t_class_cell* curr_c2 = C2.vertices.head;
    while (curr_c1 != NULL && curr_c2 != NULL) {
        if (curr_c1->vertex.id != curr_c2->vertex.id) {
            return 0;
        }
        curr_c1 = curr_c1->next;
        curr_c2 = curr_c2->next;
    }
    return 1;
}

int getClassIndex(t_class class, t_partition partition) {
    t_partition_cell * curr = partition.classes.head;
    int i = 0;
    while (curr != NULL) {
       if (compareTwoClasses(class, curr->class) == 1) {
           return i;
       }
        curr = curr->next;
        i++;
    }
    return -1;
}
t_class getClassFromIndex(int index, t_partition partition) {
    int i = 0;
    t_partition_cell* curr = partition.classes.head;
    while (curr != NULL && i < index) {
        curr = curr->next;
        i++;
    }
    return curr->class;
}

t_link_array createEmptyLinkArray(int capacity) {
    t_link_array p_link_array;
    p_link_array.log_size = 0;
    p_link_array.links = malloc(sizeof(t_link) * capacity);
    return p_link_array;
}
int doesLinkExist(t_link_array p_link_array, int p1, int p2) {
    for (int i=0; i < p_link_array.log_size; i++) {
        if (p_link_array.links[i].from == p1 && p_link_array.links[i].to == p2) {
            return 1;
        }
    }
    return 0;
}
void addLink(t_link_array * p_link_array, t_link link) {
    p_link_array->log_size++;
    p_link_array->links[p_link_array->log_size-1] = link;
}
void makeLinks(t_link_array *p_link_array, t_tarjan_vertex *vertices, t_adjacency_list graph, t_partition partition) {
    for (int i=1; i <= graph.size; i++) {
        t_class Ci = getClassFromVertex(vertices[i-1], partition);
        p_cell curr = graph.tab[i-1].head;
        while (curr != NULL) {
            t_class Cj = getClassFromVertex(vertices[curr->arrival_vertex-1], partition);
            if (compareTwoClasses(Ci, Cj) == 0) {
                int Ci_index = getClassIndex(Ci, partition);
                int Cj_index = getClassIndex(Cj, partition);
                if (doesLinkExist(*p_link_array, Ci_index, Cj_index) == 0) {
                    t_link link;
                    link.from = Ci_index;
                    link.to = Cj_index;
                    addLink(p_link_array, link);
                }
            }
            curr = curr->next;
        }
    }
}
void displayLinksArray(t_link_array p_link_array, t_partition partition) {
    printf("[");
    if (p_link_array.log_size == 0) {
        printf("]\n");
        return;
    }
    for (int i=0; i < p_link_array.log_size-1; i++) {
        printf("(");
        displayClass(getClassFromIndex(p_link_array.links[i].from, partition));
        printf(" -> ");
        displayClass(getClassFromIndex(p_link_array.links[i].to, partition));
        printf("),");
    }
    printf("(");
    displayClass(getClassFromIndex(p_link_array.links[p_link_array.log_size-1].from, partition));
    printf(" -> ");
    displayClass(getClassFromIndex(p_link_array.links[p_link_array.log_size-1].to, partition));
    printf(")");
    printf("]\n");
}

int * LinkedClass_to_Arrays(t_class class) {
    t_class_list list = class.vertices;
    int* array = (int*)malloc(class.size*sizeof(int));
    t_class_cell* curr = list.head;
    int index = 0;
    while (curr != NULL) {
        array[index] = curr->vertex.id;
        curr = curr->next;
        index++;
    }
    return array;
}



int isValInArray(int* arr, int val, int size) {
    for (int i=0; i < size; i++) {
        if (arr[i] == val) {
            return 1;
        }
    }
    return 0;
}

void getCharacteristics(t_link_array links, t_partition partition) {
    printf("The Markov graph is%sirreducible\n", (partition.size == 1) ? " " : " not ");
    int* transient = malloc(partition.size*sizeof(int));
    t_stack* persistent = createStack(partition.size);
    int j = 0;

    if (links.log_size != 0) {
        for (int i=0; i < links.log_size; i++) {
            if (isValInArray(transient, links.links[i].from, partition.size) == 0) {
                transient[j] = links.links[i].from;
                j++;
            }
        }
        for (int i=0; i < partition.size; i++) {
            if (isValInArray(transient, i, j) == 0) {
                push(persistent, i);
            }
        }
    } else {
        for (int i=0; i < partition.size; i++) {
            push(persistent, i);
        }
    }

    for (int i=0; i < j; i++) {
        t_class c = getClassFromIndex(transient[i], partition);
        printf("The class ");
        displayClass(c);
        printf(" is transient - ");
        printf("state%s", (c.size == 1) ? " " : "s ");
        t_class_cell* curr = c.vertices.head;
        printf("%d", c.vertices.head->vertex.id);
        t_class_cell * prev = curr;
        curr = curr->next;
        while (curr != NULL) {
            printf(", %d", curr->vertex.id);
            prev = curr;
            curr = curr->next;
        }
        if (c.size != 1) {
            printf(" and %d", prev->vertex.id);
        }
        printf("%s transient.\n", (c.size == 1) ? " is " : " are ");

    }
    while (isEmpty(persistent) == 0) {
        t_class c = getClassFromIndex(pop(persistent), partition);
        printf("The class ");
        displayClass(c);
        printf(" is persistent - ");
        printf("state%s", (c.size == 1) ? " " : "s ");
        t_class_cell* curr = c.vertices.head;
        printf("%d", c.vertices.head->vertex.id);
        t_class_cell * prev = curr;
        curr = curr->next;
        while (curr != NULL) {
            printf(", %d", curr->vertex.id);
            prev = curr;
            curr = curr->next;
        }
        if (c.size != 1) {
            printf(" and %d", prev->vertex.id);
        }
        if (c.size == 1) {
            printf(" is persistent and absorbing.\n");
        } else {
            printf(" are persistent.\n");
        }
    }
}