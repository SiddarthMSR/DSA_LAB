#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include <ctime>

using namespace std;


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

int greedyParallelScheduling(const vector<int>& jobs, int m) {
    vector<int> machineLoads(m, 0); 

    for (int job : jobs) {
        int machineIndex = indexOfMin(machineLoads);

        machineLoads[machineIndex] += job;
    }

    return *max_element(machineLoads.begin(), machineLoads.end());
}

int main() {

    clock_t t;
    t = clock();

    vector<int> jobs = {2, 12, 3, 5}; 
    int m = 2; 

    int makespan = greedyParallelScheduling(jobs, m);

    cout << "The makespan is: " << makespan << endl;


    t = clock() - t;
    double time_taken = ((double)t) / CLOCKS_PER_SEC;
    printf("Took %f seconds to execute \n", time_taken);

    return 0;
}
