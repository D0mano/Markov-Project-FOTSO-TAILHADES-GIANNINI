#include <stdio.h>
#include <stdlib.h>
#include "hasse.h"




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

    printf("--- 2. Test Lecture Graphe ---\n");
    t_adjacency_list* graph = readGraph("../data/exemple1_chatGPT_fixed.txt");
    if (graph == NULL) {
        printf("Erreur: bouffon check si c'est bien :  'graphe_4v.txt'.\n");

        return 1;
    }
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

    printf("Sommets = id= identification num,");
    printf("num = C est le numero temporaire. Le PDF demande de linitialiser a -1. Le -1 signifie ce sommet n'a pas encore been visited par lalgo");
    printf("lowlink= Cest le numero accessible. Le PDF demande de 'initialiser a -1. Le -1 signifie le numero accessible na pas encore been computed");
    printf("inStack = Cest lindicateur boolean (0 pour faux). Le PDF demande de l'initialiser a 0. Le 0 signifie ce sommet nest pas actuellement dans la pile de traitement");

    for (int i = 0; i < graph->size; i++) {
        printf("  Sommet %d: id=%d, num=%d, lowlink=%d, inStack=%d\n",
               i, tarjan_vertices[i].id, tarjan_vertices[i].num,
               tarjan_vertices[i].lowlink, tarjan_vertices[i].inStack);
    }


    printf("--- 6. Test Partition ---\n");
    t_partition* partition = createPartition();
    printf("Partition created. Taille: %d, Capacitad: %d\n", partition->size, partition->capacity);

    printf("--- 7. clean  ---\n");
    free(tarjan_vertices);
    freePartition(partition);
    freeAdjList(graph);
    printf(" Tests finished. me faites pas chier\n");

    return 0;
}
