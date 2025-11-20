#include <stdio.h>
#include <stdlib.h>
#include "hasse.h"
#include "matrix.h"




int main() {
    printf("Les grandes étapes de ce qu'on a pour le moment ");
    printf("--- stack test ---\n");
    t_stack* stack = createStack(10);
    printf("Pile vide ? (1=oui, 0=non): %d\n", isEmpty(stack));
    printf("Push 5...\n");
    push(stack, 5);
    printf("Push 10...\n");
    push(stack, 10);
    printf("Pile vide ? (1=oui, 0=non): %d\n", isEmpty(stack));
    printf("Pop: %d\n", pop(stack));
    printf("Pop: %d\n", pop(stack));
    printf("Pile vide ? (1=oui, 0=non): %d\n", isEmpty(stack));
    freeStack(stack);
    printf("stack working sir\n\n");

    printf("--- 1. Test Lecture Graphe ---\n");
    t_adjacency_list* graph = readGraph("../data/exemple_meteo.txt");
    if (graph == NULL) {
        printf("Erreur: check si c'est bien :  'graphe_4v.txt'.\n");

        return 1;
    }
    printf("\n--- 2. Matrix Operations Test ---\n");

    // Create transition matrix from graph
    t_matrix M = createTransitionMatrix(graph);
    printf("Transition matrix M:\n");
    displayMatrix(M);

    // Calculate M^3
    printf("Calculating M^3:\n");
    t_matrix M3 = matrixPower(M, 3);
    displayMatrix(M3);

    // Calculate M^7
    printf("Calculating M^7:\n");
    t_matrix M7 = matrixPower(M, 7);
    displayMatrix(M7);

    // Find convergence
    printf("Finding convergence (epsilon = 0.01):\n");
    t_matrix Mn_prev = createEmptyMatrix(M.rows);
    t_matrix Mn = createEmptyMatrix(M.rows);
    copyMatrix(Mn, M);

    int n = 1;
    float epsilon = 0.01f;
    float difference;

    do {
        n++;
        copyMatrix(Mn_prev, Mn);
        t_matrix temp = matrixPower(M, n);
        copyMatrix(Mn, temp);
        freeMatrix(temp);

        difference = diff(Mn, Mn_prev);
        printf("n=%d, diff=%.6f\n", n, difference);
    } while (difference > epsilon && n < 1000);

    printf("\nConvergence reached at n=%d with diff=%.6f\n", n, difference);
    printf("Stationary distribution (row 1 of M^%d):\n[ ", n);
    for (int j = 0; j < Mn.cols; j++) {
        printf("%.4f ", Mn.data[0][j]);
    }
    printf("]\n");

    // Cleanup
    freeMatrix(M);
    freeMatrix(M3);
    freeMatrix(M7);
    freeMatrix(Mn);
    freeMatrix(Mn_prev);
    displayAdjList(graph);

    printf("--- 3. Markov matrix check  ---\n");
    isMarkov(graph);
    printf("\n");

    printf("--- 4. Test Mermaid ---\n");
    Markov_to_graph(graph);
    printf("Fichier '../graph.txt' generated \n\n");

    printf("--- 5. Test Initialisation Tarjan ---\n");
    t_tarjan_vertex* tarjan_vertices = initTarjanVertices(graph->size);
    printf("Tableau t_tarjan_vertex initialised pour %d sommets :\n", graph->size);

    printf("Sommets = id = identification num,");
    printf("num = C'est le numero temporaire. Le PDF demande de l'initialiser a -1.\nLe -1 signifie ce sommet n'a pas encore ete visiter par l'algo.\n");
    printf("lowlink = C'est le numero accessible. Le PDF demande de 'initialiser a -1.\nLe -1 signifie le numero accessible n'a pas encore ete calculer\n");
    printf("inStack = Cest l'indicateur boolean (0 pour faux). Le PDF demande de l'initialiser a 0.\nLe 0 signifie ce sommet n'est pas actuellement dans la pile de traitement\n");

    for (int i = 0; i < graph->size; i++) {
        printf("  Sommet %d: id=%d, num=%d, lowlink=%d, inStack=%d\n",
               i, tarjan_vertices[i].id, tarjan_vertices[i].num,
               tarjan_vertices[i].lowlink, tarjan_vertices[i].inStack);
    }
    printf("--- 6. Test Class functions ---\n");
    t_class* C1 = createClass("C1");
    printf("Test: Is class %s empty: %d\n",C1->name,isEmptyClassList(C1->vertices));
    printf("Test: Adding element in %s\n",C1->name);
    addClassCell(C1,tarjan_vertices[1]);
    printf("Test: Is class %s empty: %d\n",C1->name,isEmptyClassList(C1->vertices));


    printf("--- 7. Test Partition ---\n");
    t_partition p = tarjan(graph, tarjan_vertices);
    displayPartition(p);
    printf("Partition created. Taille: %d\n", p.size);

    printf("--- 8. Test Links ---\n");
    t_link_array links = createEmptyLinkArray(graph->size);
    makeLinks(&links, tarjan_vertices, *graph, p);
    printf("Links : ");
    displayLinksArray(links, p);


    printf("--- 9. Characteristics ---\n");
    getCharacteristics(links, p);

    printf("--- 10. clean  ---\n");
    free(tarjan_vertices);
    freePartition(&p);
    freeAdjList(graph);
    printf(" Tests finished.\n");

    return 0;
}