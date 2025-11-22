# Markov project 
## Nolann Fotso, Loic Giannini and Benoit Tailhades (P2-Int 3 2025)

The aim of this project is to implement automatic processing and visualization of Markov graphs, which are representations of discrete-time Markov chains. The program must load graph data from text files, build an adjacency-list structure, verify that the graph satisfies the properties of a valid Markov chain, and finally generate visual representations of the graph using the Mermaid format. The project focuses on the practical manipulation of data structures rather than the theoretical probabilistic background.

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


