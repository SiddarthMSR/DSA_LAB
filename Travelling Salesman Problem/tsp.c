#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <stdbool.h>

#define INF 1000000       // Representing infinity
#define START_TEMP 1000.0 // Initial temperature for simulated annealing
#define END_TEMP 0.001    // Final temperature
#define COOLING_RATE 0.995

// Graph Representation
typedef struct {
    int V;        // Number of vertices
    int **matrix; // Adjacency matrix
} Graph;

// Function to create a graph
Graph *createGraph(int V) {
    Graph *graph = (Graph *)malloc(sizeof(Graph));
    graph->V = V;

    graph->matrix = (int **)malloc(V * sizeof(int *));
    for (int i = 0; i < V; i++) {
        graph->matrix[i] = (int *)malloc(V * sizeof(int));
        for (int j = 0; j < V; j++) {
            graph->matrix[i][j] = (i == j) ? 0 : INF; // No self-loops
        }
    }

    return graph;
}

// Function to add an edge to the graph
void addEdge(Graph *graph, int u, int v, int weight) {
    // Check if it's not a self-loop and the edge does not already exist
    if (u != v && graph->matrix[u][v] == INF) {
        graph->matrix[u][v] = weight;
        graph->matrix[v][u] = weight; // Undirected graph
    }
}

// Function to generate a random graph
void generateRandomGraph(Graph *graph, int maxWeight) {
    int V = graph->V;
    for (int i = 0; i < V; i++) {
        for (int j = i + 1; j < V; j++) {
            int weight = rand() % maxWeight + 1;
            addEdge(graph, i, j, weight);
        }
    }
}

// Function to calculate the cost of a tour
int calculateTourCost(Graph *graph, int *tour, int V) {
    int cost = 0;
    for (int i = 0; i < V; i++) {
        int u = tour[i];
        int v = tour[(i + 1) % V];
        cost += graph->matrix[u][v];
    }
    return cost;
}

void preorderWalk(int node, int *tour, int *index, int *visited, int *parent, int V) {
    visited[node] = 1;
    tour[(*index)++] = node;

    for (int i = 0; i < V; i++) {
        if (parent[i] == node && !visited[i]) {
            preorderWalk(i, tour, index, visited, parent, V);
        }
    }
}

// Function to test if a tour is valid
bool isValidTour(Graph *graph, int *tour, int V) {
    bool *visited = (bool *)calloc(V, sizeof(bool));

    // Check each vertex is visited exactly once
    for (int i = 0; i < V; i++) {
        if (tour[i] < 0 || tour[i] >= V || visited[tour[i]]) {
            free(visited);
            return false; // Invalid vertex or duplicate visit
        }
        visited[tour[i]] = true;
    }

    // Check the connectivity of the tour
    for (int i = 0; i < V; i++) {
        int u = tour[i];
        int v = tour[(i + 1) % V]; // Wrap around for closed tour
        if (graph->matrix[u][v] == INF) {
            free(visited);
            return false; // Invalid edge
        }
    }

    free(visited);
    return true;
}

// 1. Prim's MST Approximation
int approxTSP(Graph *graph, int *tour) {
    int V = graph->V;
    int *parent = (int *)malloc(V * sizeof(int));
    int *visited = (int *)calloc(V, sizeof(int));
    int index = 0;

    // Construct MST (Prim's Algorithm)
    int *key = (int *)malloc(V * sizeof(int));
    int *inMST = (int *)calloc(V, sizeof(int));

    for (int i = 0; i < V; i++) key[i] = INF;
    key[0] = 0;
    parent[0] = -1;

    for (int count = 0; count < V - 1; count++) {
        int min = INF, minIndex = -1;
        for (int i = 0; i < V; i++) {
            if (!inMST[i] && key[i] < min) {
                min = key[i];
                minIndex = i;
            }
        }

        inMST[minIndex] = 1;
        for (int v = 0; v < V; v++) {
            if (!inMST[v] && graph->matrix[minIndex][v] < key[v]) {
                key[v] = graph->matrix[minIndex][v];
                parent[v] = minIndex;
            }
        }
    }

    preorderWalk(0, tour, &index, visited, parent, V);
    // tour[index] = 0; // Close the tour

    int cost = calculateTourCost(graph, tour, V);
    
    if(!isValidTour(graph, tour, V)) return -1;

    free(parent);
    free(visited);
    free(key);
    free(inMST);

    return cost;
}

// 2. Simulated Annealing
int simulatedAnnealing(Graph *graph, int *bestTour) {
    int V = graph->V;
    int *currentTour = (int *)malloc(V * sizeof(int));
    for (int i = 0; i < V; i++) currentTour[i] = i;

    int currentCost = calculateTourCost(graph, currentTour, V);
    int bestCost = currentCost;
    for (int i = 0; i < V; i++) bestTour[i] = currentTour[i];

    double temperature = START_TEMP;

    while (temperature > END_TEMP) {
        int i = rand() % V;
        int j = rand() % V;

        int temp = currentTour[i];
        currentTour[i] = currentTour[j];
        currentTour[j] = temp;

        int newCost = calculateTourCost(graph, currentTour, V);

        if (newCost < currentCost || exp((currentCost - newCost) / temperature) > (double)rand() / RAND_MAX) {
            currentCost = newCost;
            if (newCost < bestCost) {
                bestCost = newCost;
                for (int k = 0; k < V; k++) bestTour[k] = currentTour[k];
            }
        } else {
            temp = currentTour[i];
            currentTour[i] = currentTour[j];
            currentTour[j] = temp;
        }

        temperature *= COOLING_RATE;
    }
    // bestTour[V] = -1; 
    if(!isValidTour(graph, bestTour, V)) return -1;
    free(currentTour);
    return bestCost;
}

// 3. Brute Force 
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void tspBruteForce(Graph *graph, int *tour, int l, int r, int *minCost, int *bestTour) {
    if (l == r) {
        int cost = calculateTourCost(graph, tour, graph->V);
        if (cost < *minCost) {
            *minCost = cost;
            // Store the best tour
            for (int i = 0; i < graph->V; i++) {
                bestTour[i] = tour[i];
            }
        }
        return;
    }

    for (int i = l; i <= r; i++) {
        swap(&tour[l], &tour[i]);         // Corrected: Pass addresses of elements
        tspBruteForce(graph, tour, l + 1, r, minCost, bestTour);
        swap(&tour[l], &tour[i]);         // Backtrack: Undo the swap
    }
 
}

// Modified part of main to save Brute Force tour
int findOptimalCost(Graph *graph, int *bestTour) {
    int V = graph->V;
    int *tour = (int *)malloc(V * sizeof(int));
    for (int i = 0; i < V; i++) tour[i] = i; // Initialize tour

    int minCost = INF;
    tspBruteForce(graph, tour, 0, V - 1, &minCost, bestTour);
    if(!isValidTour(graph, tour, V)) return -1;
    free(tour);
    return minCost;
}

void saveTourToFile(FILE *file, const char *algorithm, int *tour, int V, int cost) {
    fprintf(file, "\n%s Tour (Cost: %d):\n", algorithm, cost);
    for (int i = 0; i < V; i++) {
        fprintf(file, "%d ", tour[i]);
    }
    // if (algorithm == "Brute Force") fprintf(file, "%d ", 0);
    fprintf(file, "\n");
}

// Main
int main() {
    srand(time(0));
    int sizes[] = {5, 7, 9, 11}; // Test cases (adjust for more sizes)
    int maxWeight = 100;

    FILE *file = fopen("results.txt", "w");
    if (!file) {
        printf("Error opening file for writing.\n");
        return 1;
    }

    printf("Graph Size |   Brute Force      |    2- Approximation Algorithm   |        Simulated Annealing      \n");
    printf("           | Cost |  Time (ms)  | Cost | Time (ms) | Accuracy (%%) | Cost | Time (ms) | Accuracy (%%)\n");
    printf("-----------------------------------------------------------------------------------------------------\n");

    for (int s = 0; s < 5; s++) {
        int size = (s==4 ? 4 : sizes[s]);
        Graph *graph = createGraph(size);

        // Own test case, with no tsp path.
        if (s==4){  
            addEdge(graph, 0, 1, 1);
            addEdge(graph, 0, 2, 1);
            addEdge(graph, 3, 1, 1);
        }

        else{
            generateRandomGraph(graph, maxWeight);
        }

        fprintf(file, "Graph Adjacency Matrix (%d vertices):\n", graph->V);
        for (int i = 0; i < graph->V; i++) {
            for (int j = 0; j < graph->V; j++) {
                fprintf(file, "%d ", graph->matrix[i][j]);
            }
            fprintf(file, "\n");
        }

        // Brute force takes too much time for larger graphs. Hence, only implemented for smaller graphs
        int *bestBruteTour = (int *)malloc(size * sizeof(int)); // Allocate space for the best tour
        clock_t start = clock();
        int optimalCost = findOptimalCost(graph, bestBruteTour); // Pass in best tour pointer
        clock_t end = clock();
        double bruteTime = ((double)(end - start) / CLOCKS_PER_SEC) * 1000;
        saveTourToFile(file, "Brute Force", bestBruteTour, size, optimalCost);

        // Approximation
        int *tour = (int *)malloc((size + 1) * sizeof(int));
        start = clock();
        int approxCost = approxTSP(graph, tour);
        end = clock();
        double approxTime = ((double)(end - start) / CLOCKS_PER_SEC) * 1000;
        saveTourToFile(file, "Approximation TSP", tour, size, approxCost);

        // Simulated Annealing
        int *saTour = (int *)malloc((size + 1) * sizeof(int));
        start = clock();
        int saCost = simulatedAnnealing(graph, saTour);
        end = clock();
        double saTime = ((double)(end - start) / CLOCKS_PER_SEC) * 1000;
        saveTourToFile(file, "Simulated Annealing", saTour, size, saCost);

        // Accuracy
        double approxAccuracy = ((double)optimalCost / approxCost) * 100;
        double saAccuracy = ((double)optimalCost / saCost) * 100;

        // Print results
        printf("%10d | %4d | %11.6f | %4d | %9.6f | %12.2f | %4d | %9.6f | %10.2f \n",
               size, optimalCost, bruteTime, approxCost, approxTime, approxAccuracy, saCost, saTime, saAccuracy);
        fprintf(file, "\n");

        // Free memory
        for (int i = 0; i < size; i++) free(graph->matrix[i]);
        free(graph->matrix);
        free(graph);
        free(tour);
        free(saTour);
    }
    printf("Note: -1 indicates no solution found.\n");   // The indicator can be changed accordingly if negative weights are allowed
    printf("Tour results along with test cases have been saved as file 'results.txt'.\n");
    return 0;
}
