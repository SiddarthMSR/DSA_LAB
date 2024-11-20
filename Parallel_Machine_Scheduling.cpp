#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;


// Finding the machine with the smallest load: O(m)
// Iterating over n jobs: O(n)
// Total time complexity: O(n⋅m).


// Function to find the index of the machine with the smallest load
int indexOfMin(const vector<int>& machineLoads) {
    int minIndex = 0;
    int minValue = INT_MAX;

    for (int i = 0; i < machineLoads.size(); i++) {
        if (machineLoads[i] < minValue) {
            minValue = machineLoads[i];
            minIndex = i;
        }
    }
    return minIndex;
}

// Greedy Parallel Machine Scheduling algorithm
int greedyParallelScheduling(const vector<int>& jobs, int m) {
    vector<int> machineLoads(m, 0); // Initialize machine loads to 0

    for (int job : jobs) {
        // Find the machine with the smallest load
        int machineIndex = indexOfMin(machineLoads);

        // Assign the job to this machine
        machineLoads[machineIndex] += job;
    }

    // The makespan is the maximum load among all machines
    return *max_element(machineLoads.begin(), machineLoads.end());
}

int main() {
    // Example input
    vector<int> jobs = {2, 12, 3, 5}; // Processing times of jobs
    int m = 2; // Number of machines

    // Call the greedy algorithm
    int makespan = greedyParallelScheduling(jobs, m);

    // Output the result
    cout << "The makespan is: " << makespan << endl;

    return 0;
}
