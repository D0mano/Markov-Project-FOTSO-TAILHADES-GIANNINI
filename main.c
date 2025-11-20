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
    t_adjacency_list* graph = readGraph("../data/exemple2.txt");
    if (graph == NULL) {
        printf("Erreur: check si c'est bien :  'graphe_4v.txt'.\n");

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

    printf("Sommets = id = identification num,");
    printf("num = C'est le numero temporaire. Le PDF demande de l'initialiser a -1.\nLe -1 signifie ce sommet n'a pas encore ete visiter par l'algo.\n");
    printf("lowlink = C'est le numero accessible. Le PDF demande de 'initialiser a -1.\nLe -1 signifie le numero accessible n'a pas encore ete calculer\n");
    printf("inStack = Cest l'indicateur boolean (0 pour faux). Le PDF demande de l'initialiser a 0.\nLe 0 signifie ce sommet n'est pas actuellement dans la pile de traitement\n");

    for (int i = 0; i <= graph->size; i++) {
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



    printf("--- 9. clean  ---\n");
    free(tarjan_vertices);
    freePartition(&p);
    freeAdjList(graph);
    printf(" Tests finished.\n");

    return 0;
}