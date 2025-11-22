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


