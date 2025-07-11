#include <iostream>
#include <vector>
#include <set>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <algorithm>

using namespace std;

// Function to calculate the cost of a vertex cover
int costFunction(const set<int>& vertexCover) {
    
    return vertexCover.size();
}

// Function to check if the current vertex cover covers all edges
bool isValidCover(const vector<pair<int, int>>& edges, const set<int>& vertexCover) {
    
    for (const auto& edge : edges) {
        
        if (vertexCover.find(edge.first) == vertexCover.end() && vertexCover.find(edge.second) == vertexCover.end()) {

            return false;
        }
    }
    
    return true;
}

// Generate a neighbor solution by adding/removing a vertex
set<int> generateNeighbor(const set<int>& currentCover, int numVertices) {
    
    set<int> neighbor = currentCover;
    int vertex = rand() % numVertices;
    
    if (neighbor.find(vertex) != neighbor.end()) {
        neighbor.erase(vertex); // Remove vertex if it's in the cover
    } 
    
    else {
        neighbor.insert(vertex); // Add vertex if it's not in the cover
    }

    return neighbor;
}

// Simulated annealing to solve the vertex cover problem
set<int> simulatedAnnealing(const vector<pair<int, int>>& edges, int numVertices) {
    // Initialize random seed
    srand(time(0));

    // Initial temperature and cooling rate
    double temperature = 1000.0;
    double coolingRate = 0.95;

    // Initial solution: start with all vertices in the cover
    set<int> currentCover;
    for (int i = 0; i < numVertices; ++i) {
        currentCover.insert(i);
    }

    set<int> bestCover = currentCover;

    while (temperature > 1.0) {
        // Generate a neighbor solution
        set<int> neighborCover = generateNeighbor(currentCover, numVertices);

        // Ensure the neighbor solution is valid
        if (!isValidCover(edges, neighborCover)) {
            continue;
        }

        // Calculate the cost of the solutions
        int currentCost = costFunction(currentCover);
        int neighborCost = costFunction(neighborCover);

        // Decide whether to accept the neighbor solution
        if (neighborCost < currentCost ||
            exp((currentCost - neighborCost) / temperature) > ((double)rand() / RAND_MAX)) {
            currentCover = neighborCover;
        }

        // Update the best solution found so far
        if (costFunction(currentCover) < costFunction(bestCover)) {
            bestCover = currentCover;
        }

        // Cool down
        temperature *= coolingRate;
    }

    return bestCover;
}

int main() {

    vector<pair<int, int>> edges = {
        {0, 1}, {0, 2}, {1, 3}, {1, 4}, {2, 4}, {3, 5}, {4, 5}
    };

    int numVertices = 6;

    clock_t t;
    t = clock();

    // Solve the Vertex Cover problem using Simulated Annealing
    set<int> vertexCover = simulatedAnnealing(edges, numVertices);

    // Print the result
    cout << "Vertex Cover: ";
    for (int vertex : vertexCover) {
        cout << vertex << " ";
    }
    cout << endl;

    t = clock() - t;
    double time_taken = ((double)t) / CLOCKS_PER_SEC;
    printf("Took %f seconds to execute \n", time_taken);

    return 0;
}
