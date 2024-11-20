#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

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
    vector<int> jobs = {2, 12, 3, 5}; 
    int m = 2; 

    int makespan = greedyParallelScheduling(jobs, m);

    cout << "The makespan is: " << makespan << endl;

    return 0;
}
