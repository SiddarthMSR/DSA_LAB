#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <fstream>
#include <cmath>
#include <limits>
#include <numeric>
using namespace std;

// Function to calculate the makespan of a schedule
int calculateMakespan(const vector<int>& machineLoads) {
    return *max_element(machineLoads.begin(), machineLoads.end());
}

// Brute force: Compute the optimal schedule
int bruteForceOptimal(vector<int> jobs, int numMachines) {
    int n = jobs.size();
    int minMakespan = numeric_limits<int>::max();

    int totalAssignments = pow(numMachines, n); // Total combinations
    for (int mask = 0; mask < totalAssignments; ++mask) {
        vector<int> machineLoads(numMachines, 0);
        int currentMask = mask;

        for (int i = 0; i < n; ++i) {
            int machine = currentMask % numMachines;
            machineLoads[machine] += jobs[i];
            currentMask /= numMachines;
        }

        minMakespan = min(minMakespan, calculateMakespan(machineLoads));
    }

    return minMakespan;
}

// Simulated Annealing implementation
vector<vector<int>> simulatedAnnealing(vector<int> jobs, int numMachines) {
    int n = jobs.size();
    vector<int> currentAssignment(n, 0); 
    vector<int> bestAssignment = currentAssignment;
    vector<int> machineLoads(numMachines, 0);

    for (int i = 0; i < n; ++i) {
        machineLoads[currentAssignment[i]] += jobs[i];
    }

    int currentMakespan = calculateMakespan(machineLoads);
    int bestMakespan = currentMakespan;

    double temperature = 1000.0;
    double coolingRate = 0.95;
    int maxIterations = 1000;

    for (int iter = 0; iter < maxIterations && temperature > 1e-3; ++iter) {
        int jobIdx = rand() % n;
        int oldMachine = currentAssignment[jobIdx];
        int newMachine = rand() % numMachines;

        if (oldMachine == newMachine) continue;

        machineLoads[oldMachine] -= jobs[jobIdx];
        machineLoads[newMachine] += jobs[jobIdx];
        currentAssignment[jobIdx] = newMachine;

        int newMakespan = calculateMakespan(machineLoads);

        if (newMakespan < currentMakespan || 
            exp((currentMakespan - newMakespan) / temperature) > (double)rand() / RAND_MAX) {
            currentMakespan = newMakespan;
            if (currentMakespan < bestMakespan) {
                bestMakespan = currentMakespan;
                bestAssignment = currentAssignment;
            }
        } else {
            machineLoads[newMachine] -= jobs[jobIdx];
            machineLoads[oldMachine] += jobs[jobIdx];
            currentAssignment[jobIdx] = oldMachine;
        }

        temperature *= coolingRate;
    }

    vector<vector<int>> schedule(numMachines);
    for (int i = 0; i < n; ++i) {
        schedule[bestAssignment[i]].push_back(jobs[i]);
    }
    return schedule;
}

// 2-Approximation algorithm
vector<vector<int>> twoApproximation(vector<int> jobs, int numMachines) {
    vector<vector<int>> schedule(numMachines);
    vector<int> machineLoads(numMachines, 0);

    sort(jobs.rbegin(), jobs.rend());

    for (int job : jobs) {
        int minMachine = min_element(machineLoads.begin(), machineLoads.end()) - machineLoads.begin();
        schedule[minMachine].push_back(job);
        machineLoads[minMachine] += job;
    }

    return schedule;
}

int main() {
    srand(time(0)); 

    int numTestCases = 4; // Number of test cases
    int numJobsRange[] = {10, 20}; 
    int numMachinesRange[] = {10, 20}; 

    ofstream outFile("results.csv");
    outFile << "TestCase,NumJobs,NumMachines,BruteForce,SimulatedAnnealing,TwoApproximation\n";

    for (int test = 1; test <= numTestCases; ++test) {
        int numJobs = rand() % (numJobsRange[1] - numJobsRange[0] + 1) + numJobsRange[0];
        int numMachines = rand() % (numMachinesRange[1] - numMachinesRange[0] + 1) + numMachinesRange[0];
        vector<int> jobs(numJobs);

        for (int i = 0; i < numJobs; ++i) {
            jobs[i] = rand() % 20 + 1;
        }

        int bruteForceMakespan = bruteForceOptimal(jobs, numMachines);

        vector<vector<int>> saSchedule = simulatedAnnealing(jobs, numMachines);
        vector<int> saLoads(numMachines, 0);
        for (size_t i = 0; i < saSchedule.size(); ++i) {
            for (int job : saSchedule[i]) {
                saLoads[i] += job;
            }
        }
        int saMakespan = calculateMakespan(saLoads);

        vector<vector<int>> approxSchedule = twoApproximation(jobs, numMachines);
        vector<int> approxLoads(numMachines, 0);
        for (size_t i = 0; i < approxSchedule.size(); ++i) {
            for (int job : approxSchedule[i]) {
                approxLoads[i] += job;
            }
        }
        int approxMakespan = calculateMakespan(approxLoads);

        outFile << test << "," << numJobs << "," << numMachines << "," << bruteForceMakespan << ","
                << saMakespan << "," << approxMakespan << "\n";
    }

    outFile.close();
    cout << "Results saved to results.csv." << endl;

    return 0;
}
