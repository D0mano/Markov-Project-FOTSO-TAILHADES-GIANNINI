#include <stdio.h>
#include <stdlib.h>
#include "hasse.h"




int main() {
    const char* filename = "../data/exemple1_chatGPT_fixed.txt";

    printf("--- Testing readGraph function with '%s' ---\n", filename);

    t_adjacency_list* graph = readGraph(filename);
    Markov_to_graph(graph);

    printf("\n--- Adjacency List read from file: ---\n");
    displayAdjList(graph);
    isMarkov(graph);

    printf("\n--- Step 1 part2 test ---\n");

    int n = graph->size;
    t_tarjan_vertex *vertices = initTarjanVertices(n);
    printf("Vertices initialized:\n");
    for (int i = 0; i < n; i++) {
        printf("Vertex %d -> num=%d, lowlink=%d, inStack=%d\n",
               vertices[i].id, vertices[i].num,
               vertices[i].lowlink, vertices[i].inStack);
    }

    t_stack *stack = createStack(n);
    printf("Stack created (capacity=%d)\n", stack->capacity);

    t_partition *partition = createPartition();
    t_class *class1 = createClass("C1");
    partition->classes[partition->size++] = class1;

    class1->vertices[class1->size++] = &vertices[0];
    printf(" class %s containing vertex %d\n", class1->name, class1->vertices[0]->id);

    free(class1->vertices);
    free(class1);
    free(partition->classes);
    free(partition);
    free(stack->data);
    free(stack);
    free(vertices);

    freeAdjList(graph);
    printf("Memory freed successfully.\n");

    return EXIT_SUCCESS;
}
