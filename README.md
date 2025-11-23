# Markov project 
## Nolann Fotso, Loic Giannini and Benoit Tailhades (P2-Int 3 2025)

This project is part of the TI301 – Algorithms and Data Structures 2 course and is carried out in collaboration with the Mathematics Department. Its goal is to process, analyze, and visualize discrete-time Markov graphs, focusing on the structural and probabilistic properties associated with Markov chains.

##  What is this?
We built this tool to analyze **Markov Graphs**.

In simple terms, a Markov graph is a map of "states" (like weather: Sunny, Rainy, Cloudy) with probabilities of moving from one to another. Our program reads these maps, checks if they are valid, groups them logically, and uses math to predict what happens in the future.

---

##  How the code is organized

| File | What it does |
| :--- | :--- |
| **`main.c`** | **The Manager.** It runs the whole show, step by step. |
| **`utils.c`** | **The Helper.** Reads your text files and runs the Tarjan algorithm to find groups. |
| **`hasse.c`** | **The Organizer.** figures out the "big picture" connections between groups. |
| **`matrix.c`** | **The Calculator.** Handles all the probability math and predictions. |
| **`types.h`** | **The Blueprints.** Defines what a Graph, a List, or a Matrix looks like. |

---

##  Key Features (How it works)

### 1. Reading & Checking (`utils.c`)
* **`readGraph`**: Reads a simple text file where you list connections (Start -> End -> Probability) and builds the graph in memory
* **`isMarkovGraph`**: acts like a security guard. It checks every node to make sure the outgoing probabilities add up to exactly 1 (100%). If they don't, it warns you that the math won't work
* **`generateMermaidCode`**: **The Artist.** It turns our code into a text format that the [Mermaid](https://mermaid.live) website can turn into a beautiful diagram.

### 2. Grouping & Structure (Tarjan & Hasse)
* **`tarjan`**: This uses a smart algorithm to find "communities" (classes). A community is a group of nodes where everyone can reach everyone else.
* **`buildHasseGraph`**: Once we find the communities, this function draws a simple map showing how you travel *between* the communities.
* **`classifyComponents`**: It gives each group a label:
    * **Transient:** You can leave this group and never come back.
    * **Persistent:** Once you enter, you are stuck here forever.

### 3. Predicting the Future (`matrix.c`)
* **`listToMatrix`**: Converts our graph into a grid of numbers (a matrix) so we can do math with it.
* **`findStationaryDistribution`**: **The Crystal Ball.** It multiplies the matrix over and over to see what happens in the long run. For example, "In 100 days, what is the chance of rain?".
* **`getPeriod` (Bonus)**: Checks if a group goes in circles. For example, if you can only return to the start every 3 steps, this function figures that out.

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


