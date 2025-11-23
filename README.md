# Markov project 
## Nolann Fotso, Loic Giannini and Benoit Tailhades (P2-Int 3 2025)

This project is part of the TI301 – Algorithms and Data Structures 2 course and is carried out in collaboration with the Mathematics Department. Its goal is to process, analyze, and visualize discrete-time Markov graphs, focusing on the structural and probabilistic properties associated with Markov chains.

## Aim of the Project
The objective of this project is to design a C program capable of:
Loading Markov graph data from input files
Building an adjacency-list representation of the graph
Validating that the graph satisfies the mathematical conditions of a Markov chain
Extracting graph components and properties (Tarjan algorithm, graph partitioning, Hasse diagram, transient/persistent states, etc.)
Performing probability calculations to study the evolution of distributions and stationary states
Generating visual representations of graphs in Mermaid flowchart format
This project emphasizes practical implementation of data structures and algorithms rather than the probabilistic theory behind them.

## Technical tools  
C  
CMake  

Graph algorithms:  
Tarjan SCC  
Hasse graph extraction  
Matrix algebra for Markov chains (from both this year and last year by the way)

# TI301 - Étude des Graphes de Markov

**Auteurs :** Nolann Fotso, Loïc Giannini, Benoît Tailhades
**Contexte :** Projet conjoint Informatique & Mathématiques (Algorithmique 2)

## 🎯 Objectif
Ce projet implémente une suite d'outils en C pour l'analyse, la validation et la visualisation de chaînes de Markov à temps discret. Il traite les graphes orientés pondérés pour en extraire les propriétés structurelles et probabilistes.

---

## 📂 Organisation du Code

| Fichier | Rôle Principal |
| :--- | :--- |
| **`main.c`** | Point d'entrée, orchestration des étapes (chargement -> analyse -> calcul). |
| **`utils.c/h`** | Gestion I/O (lecture fichiers), algo de **Tarjan**, export Mermaid. |
| **`hasse.c/h`** | Gestion du diagramme de **Hasse** et classification des composants. |
| **`matrix.c/h`** | Opérations matricielles ($M^n$, distributions stationnaires). |
| **`types.h`** | Structures de données (Listes d'adjacence, Matrices, Partitions). |

---

## 🔑 Fonctions Clés (Core Logic)

### 1. Représentation & Validation (`utils.c`)
* [cite_start]**`readGraph`** : Charge un fichier `.txt` (format `src dest proba`) vers une liste d'adjacence dynamique[cite: 633].
* [cite_start]**`isMarkovGraph`** : Vérifie la propriété fondamentale de Markov : la somme des probabilités sortantes de chaque nœud doit être égale à 1 (avec tolérance flottante)[cite: 527].
* [cite_start]**`generateMermaidCode`** : Génère le code source pour la visualisation graphique via MermaidJS[cite: 694].

### 2. Analyse Structurelle (Tarjan & Hasse)
* [cite_start]**`tarjan`** (`utils.c`) : Implémente l'algorithme de Tarjan (parcours en profondeur + pile) pour partitionner le graphe en **Composantes Fortement Connexes (SCC)** ou "classes"[cite: 297].
* [cite_start]**`buildHasseGraph`** (`hasse.c`) : Construit le graphe des classes (diagramme de Hasse) représentant les transitions irréversibles entre les composants[cite: 382].
* **`classifyComponents`** : Détermine la nature des classes :
    * *Transitoire* : On peut en sortir.
    * *Persistante* : Une fois dedans, on ne peut plus en sortir.
    * [cite_start]*Absorbante* : Classe persistante à un seul état[cite: 496].

### 3. Calculs de Probabilités (`matrix.c`)
* [cite_start]**`listToMatrix`** : Convertit la liste d'adjacence en matrice de transition $M$ $N \times N$ pour les calculs algébriques[cite: 119].
* [cite_start]**`findStationaryDistribution`** : Calcule la distribution limite $\Pi^*$ en itérant $M^n$ jusqu'à ce que la différence soit négligeable ($\epsilon < 0.01$)[cite: 129].
* [cite_start]**`subMatrix`** : Isole la sous-matrice d'une composante connexe spécifique pour calculer sa distribution stationnaire locale[cite: 155].
* [cite_start]**`getPeriod`** (Bonus) : Calcule la périodicité d'une classe via le PGCD des longueurs de cycles de retour[cite: 221].

---

## 🚀 Compilation & Usage

Pré-requis : `cmake`, `gcc`.

```bash
# Compilation
mkdir build && cd build
cmake ..
make

# Exécution
./markov_project

```text
Directory structure:
└── d0mano-markov-project-fotso-tailhades-giannini/
    ├── CMakeLists.txt
    ├── graph.mmd
    ├── graph.txt
    ├── hasse.c
    ├── hasse.h
    ├── main.c
    ├── matrix.c
    ├── matrix.h
    ├── types.h
    ├── utils.c
    ├── utils.h
    └── data/
        ├── exemple1.txt
        ├── exemple1_chatGPT_fixed.txt
        ├── exemple1_chatGPT_fixed_graph.mmd
        ├── exemple1_chatGPT_fixed_hasse.mmd
        ├── exemple1_from_chatGPT.txt
        ├── exemple1_graph.mmd
        ├── exemple1_hasse.mmd
        ├── exemple2.txt
        ├── exemple2_graph.mmd
        ├── exemple2_hasse.mmd
        ├── exemple3.txt
        ├── exemple3_graph.mmd
        ├── exemple3_hasse.mmd
        ├── exemple4_2check.txt
        ├── exemple_hasse1.txt
        ├── exemple_meteo.txt
        ├── exemple_meteo_graph.mmd
        ├── exemple_meteo_hasse.mmd
        ├── exemple_scc1.txt
        ├── exemple_valid_step3.txt
        ├── exemple_valid_step3_graph.mmd
        └── exemple_valid_step3_hasse.mmd


