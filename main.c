#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hasse.h"
#include "matrix.h"
#include "utils.h"

// Utility function to clear the input buffer (prevents menu skipping issues)
void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Function to free memory using your existing cleanup functions
void cleanMemory(t_adjacency_list** graph, t_tarjan_vertex** vertices, t_partition* p, t_matrix* M, int* is_partition_computed, int* is_matrix_computed) {
    if (*graph != NULL) {
        freeAdjList(*graph); // Function from hasse.h
        *graph = NULL;
    }
    if (*vertices != NULL) {
        free(*vertices); // Standard free, as no specific function exists
        *vertices = NULL;
    }
    if (*is_partition_computed) {
        freePartition(p); // Function from hasse.h
        *is_partition_computed = 0;
    }
    if (*is_matrix_computed) {
        freeMatrix(*M); // Function from matrix.h
        *is_matrix_computed = 0;
    }
    printf("--> Memory cleaned.\n");
}

int main() {
    // Main variables
    t_adjacency_list* graph = NULL;
    t_tarjan_vertex* vertices = NULL;
    t_partition p;      // Partition structure returned by tarjan()
    t_matrix M;         // Transition matrix
    t_link_array links; // Link array for Hasse diagram

    // Program state flags
    int is_loaded = 0;
    int is_partition_computed = 0;
    int is_matrix_computed = 0;

    int choice = -1;
    char filename[256];

    printf("==========================================\n");
    printf("   MARKOV PROJECT INTERFACE - TI301\n");
    printf("==========================================\n");

    while (choice != 0) {
        printf("\n--- MAIN MENU ---\n");
        if (is_loaded) {
            printf("Active file: %s (%d vertices)\n", filename, graph->size);
        } else {
            printf("No file loaded.\n");
        }
        printf("-----------------\n");
        printf("1. Load a graph file\n");

        if (is_loaded) {
            printf("2. Display Graph (Adjacency List)\n");
            printf("3. Generate/Display Transition Matrix\n");
            printf("4. Check Markov Property\n");
            printf("5. Compute Classes (Tarjan's Algo)\n");

            if (is_partition_computed) {
                printf("6. Compute and Display Links (Hasse Diagram)\n");
                printf("7. Analyze Characteristics (Transient/Persistent)\n");
                printf("8. Analyze Sub-Matrices by Class (Stationary Distributions)\n");
            }
            printf("9. Export Graph for Mermaid (graph.txt)\n");
        }
        printf("0. Quit\n");
        printf("Your choice: ");

        if (scanf("%d", &choice) != 1) {
            printf("Invalid input.\n");
            clearInputBuffer();
            continue;
        }
        clearInputBuffer(); // Consume the newline character

        switch (choice) {
            case 1: // LOAD FILE
                if (is_loaded) {
                    cleanMemory(&graph, &vertices, &p, &M, &is_partition_computed, &is_matrix_computed);
                    is_loaded = 0;
                }
                printf("Enter file path (e.g., ../data/exemple1.txt): ");
                if (fgets(filename, sizeof(filename), stdin) != NULL) {
                    filename[strcspn(filename, "\n")] = 0; // Remove the newline char

                    // Check if file exists to prevent readGraph from crashing the program
                    FILE* f = fopen(filename, "r");
                    if (f) {
                        fclose(f);
                        graph = readGraph(filename); // Call to hasse.h function
                        if (graph != NULL) {
                            is_loaded = 1;
                            // Mandatory initialization for Tarjan (as per project requirements)
                            vertices = initTarjanVertices(graph->size); // Call to hasse.h
                            printf("Graph loaded and vertices initialized.\n");
                        }
                    } else {
                        printf("Error: Cannot open '%s'. Please check the path.\n", filename);
                    }
                }
                break;

            case 2: // DISPLAY LIST
                if (!is_loaded) { printf("Please load a graph first.\n"); break; }
                displayAdjList(graph); // Call to hasse.h
                break;

            case 3: // MATRIX
                if (!is_loaded) { printf("Please load a graph first.\n"); break; }
                if (!is_matrix_computed) {
                    M = createTransitionMatrix(graph); // Call to matrix.h
                    is_matrix_computed = 1;
                }
                displayMatrix(M); // Call to matrix.h
                break;

            case 4: // MARKOV CHECK
                if (!is_loaded) { printf("Please load a graph first.\n"); break; }
                isMarkov(graph); // Call to hasse.h
                break;

            case 5: // TARJAN (CLASSES)
                if (!is_loaded) { printf("Please load a graph first.\n"); break; }
                if (is_partition_computed) freePartition(&p); // Clean up if re-running

                // Reset vertices (necessary if re-running algorithm)
                free(vertices);
                vertices = initTarjanVertices(graph->size);

                p = tarjan(graph, vertices); // Core algorithm from hasse.h
                is_partition_computed = 1;

                printf("Detected Class Partition:\n");
                displayPartition(p); // Call to hasse.h
                break;

            case 6: // LINKS / HASSE
                if (!is_partition_computed) { printf("Please run step 5 (Tarjan) first.\n"); break; }

                links = createEmptyLinkArray(graph->size); // Call to hasse.h
                makeLinks(&links, vertices, *graph, p);    // Call to hasse.h

                // Optional: simplify transitive links for a proper Hasse diagram
                removeTransitiveLinks(&links); // Call to hasse.h

                printf("Links between classes (Hasse Diagram):\n");
                displayLinksArray(links, p); // Call to hasse.h

                // No freeLinkArray in headers, freeing internal array manually
                free(links.links);
                break;

            case 7: // CHARACTERISTICS
                if (!is_partition_computed) { printf("Please run step 5 (Tarjan) first.\n"); break; }

                // Re-create links temporarily as the function needs them
                links = createEmptyLinkArray(graph->size);
                makeLinks(&links, vertices, *graph, p);

                getCharacteristics(links, p); // Call to hasse.h (prints Transient/Persistent)

                free(links.links);
                break;

            case 8: // SUB-MATRICES & STATIONARY DISTRIBUTION
                if (!is_partition_computed) { printf("Please run step 5 (Tarjan) first.\n"); break; }
                if (!is_matrix_computed) {
                    M = createTransitionMatrix(graph);
                    is_matrix_computed = 1;
                }

                printf("\n--- Analysis by Class ---\n");
                t_partition_cell *curr = p.classes.head;
                int idx = 0;

                // Loop through ALL classes in the partition
                while (curr != NULL) {
                    printf("\n>>> Class: %s\n", curr->class.name);

                    // Extract sub-matrix (Call to matrix.h)
                    t_matrix subM = subMatrix(M, p, idx);
                    printf("Sub-matrix:\n");
                    displayMatrix(subM);

                    // Compute stationary distribution (Call to matrix.h)
                    printf("Stationary distribution for %s:\n", curr->class.name);
                    t_matrix stat = stationaryDistribution(subM);
                    displayMatrix(stat);

                    // Free temporary matrices for this iteration
                    freeMatrix(subM);
                    freeMatrix(stat);

                    curr = curr->next;
                    idx++;
                }
                printf("\n--- End of Analysis ---\n");
                break;

            case 9: // MERMAID EXPORT
                if (!is_loaded) { printf("Please load a graph first.\n"); break; }
                Markov_to_graph(graph); // Call to hasse.h
                printf("File generated: ../graph.txt\n");
                break;

            case 0:
                printf("Exiting program. Goodbye!\n");
                break;

            default:
                printf("Unknown choice.\n");
        }
    }

    // Final cleanup before exit
    cleanMemory(&graph, &vertices, &p, &M, &is_partition_computed, &is_matrix_computed);

    return 0;
}