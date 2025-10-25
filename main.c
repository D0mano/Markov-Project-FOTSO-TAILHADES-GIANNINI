#include <stdio.h>
#include <stdlib.h>
#include "hasse.h"



int main() {
    const char* filename = "../data/exemple1_chatGPT_fixed.txt";

    printf("--- Testing readGraph function with '%s' ---\n", filename);

    // Read the graph from the file
    t_adjacency_list* graph = readGraph(filename);

    // Display the graph to verify it was read correctly
    printf("\n--- Adjacency List read from file: ---\n");
    displayAdjList(graph);
    isMarkov(graph);

    // Free the allocated memory for the graph
    printf("\n--- Freeing graph memory ---\n");
    freeAdjList(graph);
    printf("Memory freed successfully.\n");

    return EXIT_SUCCESS;
}
