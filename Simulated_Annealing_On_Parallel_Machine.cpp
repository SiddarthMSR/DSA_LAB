#include <iostream>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <climits>

using namespace std;

// function to calculate the makespan of a schedule
int calculateMakespan(const vector<vector<int>> &schedule)
{
    int maxTime = 0;
    for (const auto &machine : schedule)
    {
        int load = 0;
        for (int job : machine)
        {
            load += job;
        }
        maxTime = max(maxTime, load);
    }
    return maxTime;
}

// Generate a random initial solution
vector<vector<int>> generateInitialSolution(const vector<int> &jobs, int m)
{
    vector<vector<int>> schedule(m);
    for (int job : jobs)
    {
        int randomMachine = rand() % m; // Assign job to a random machine
        schedule[randomMachine].push_back(job);
    }
    return schedule;
}

// Generate a neighboring solution by moving a job between machines
vector<vector<int>> generateNeighbor(const vector<vector<int>> &schedule)
{
    vector<vector<int>> newSchedule = schedule;

    // Randomly select a source machine with at least one job
    int srcMachine;
    do
    {
        srcMachine = rand() % newSchedule.size();
    } while (newSchedule[srcMachine].empty());

    // Randomly select a job from the source machine
    int jobIndex = rand() % newSchedule[srcMachine].size();
    int job = newSchedule[srcMachine][jobIndex];

    newSchedule[srcMachine].erase(newSchedule[srcMachine].begin() + jobIndex);

    // Randomly select a target machine to move the job
    int tgtMachine = rand() % newSchedule.size();
    newSchedule[tgtMachine].push_back(job);

    return newSchedule;
}

// Simulated Annealing algorithm
pair<vector<vector<int>>, int> simulatedAnnealing(
    const vector<int> &jobs, int m, double initialTemp, double finalTemp, double coolingRate)
{
    // Initialize random seed
    srand(time(0));

    // Generate initial solution
    vector<vector<int>> currentSolution = generateInitialSolution(jobs, m);
    int currentMakespan = calculateMakespan(currentSolution);

    // Initialize best solution
    vector<vector<int>> bestSolution = currentSolution;
    int bestMakespan = currentMakespan;

    // Initialize temperature
    double temperature = initialTemp;

    // Main loop
    while (temperature > finalTemp)
    {
        // Generate a neighboring solution
        vector<vector<int>> neighborSolution = generateNeighbor(currentSolution);
        int neighborMakespan = calculateMakespan(neighborSolution);

        // Accept the neighbor solution based on the acceptance probability
        if (neighborMakespan < currentMakespan ||
            exp((currentMakespan - neighborMakespan) / temperature) > (double)rand() / RAND_MAX)
        {
            currentSolution = neighborSolution;
            currentMakespan = neighborMakespan;

            // Update the best solution if improved
            if (currentMakespan < bestMakespan)
            {
                bestSolution = currentSolution;
                bestMakespan = currentMakespan;
            }
        }

        // Cool down
        temperature *= coolingRate;
    }

    return {bestSolution, bestMakespan};
}

// Print the schedule
void printSchedule(const vector<vector<int>> &schedule)
{
    for (int i = 0; i < schedule.size(); ++i)
    {
        cout << "Machine " << i + 1 << ": ";
        for (int job : schedule[i])
        {
            cout << job << " ";
        }
        cout << endl;
    }
}

int main()
{

    clock_t t;
    t = clock();

    vector<int> jobs = {2, 12, 3, 5}; 
    int m = 2;                        
    double initialTemp = 1000.0;      // starting temperature bacially it tell us how much we are ready to accept the worst solution
    double finalTemp = 0.001;         // final temperature basically it tell how refined solution we want nut it will increanse the time
    double coolingRate = 0.95;        // cooling rate basically slows the cooling giving the algorithm more time to explore solutions at each temperature.

    auto [bestSolution, bestMakespan] = simulatedAnnealing(jobs, m, initialTemp, finalTemp, coolingRate);

    cout << "Best Schedule:" << endl;
    printSchedule(bestSolution);
    cout << "Best Makespan: " << bestMakespan << endl;

    t = clock() - t;
    double time_taken = ((double)t) / CLOCKS_PER_SEC;
    printf("Took %f seconds to execute \n", time_taken);

    return 0;
}


// COOLING RATE

// 0.000529 FOR 0.001
// 0.000959 FOR 0.0000000000001
