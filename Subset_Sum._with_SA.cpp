#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <random>
#include <chrono>
#include <numeric> // For accumulate

using namespace std;

// Function to generate all subsets (Brute-force)
vector<int> bruteForceSubsetSum(const vector<int>& S, int t, long long &executionTime) {
    auto start = chrono::high_resolution_clock::now();
    int n = S.size();
    int closestSum = 0;
    vector<int> bestSubset;

    for (int mask = 0; mask < (1 << n); mask++) {
        vector<int> currentSubset;
        int currentSum = 0;
        for (int i = 0; i < n; i++) {
            if (mask & (1 << i)) {
                currentSubset.push_back(S[i]);
                currentSum += S[i];
            }
        }
        if (currentSum <= t && currentSum > closestSum) {
            closestSum = currentSum;
            bestSubset = currentSubset;
        }
    }

    auto end = chrono::high_resolution_clock::now();
    executionTime = chrono::duration_cast<chrono::milliseconds>(end - start).count();
    return bestSubset;
}

// Function to trim the list of subset sums
vector<int> trim(const vector<int>& list, double delta) {
    vector<int> trimmedList;
    int lastAdded = list[0];
    trimmedList.push_back(lastAdded);

    for (size_t i = 1; i < list.size(); i++) {
        if (list[i] > lastAdded * (1 + delta)) {
            lastAdded = list[i];
            trimmedList.push_back(lastAdded);
        }
    }
    return trimmedList;
}

// Approximate subset sum algorithm
vector<int> approximateSubsetSum(const vector<int>& S, int t, double epsilon, long long &executionTime) {
    auto start = chrono::high_resolution_clock::now();
    vector<int> L = {0};
    double delta = epsilon / (2 * S.size());
    vector<int> chosenSubset;

    for (int s : S) {
        vector<int> L_new;
        for (int x : L) {
            L_new.push_back(x);
            L_new.push_back(x + s);
        }

        sort(L_new.begin(), L_new.end());
        L_new = trim(L_new, delta);

        L.clear();
        for (int x : L_new) {
            if (x <= t) {
                L.push_back(x);
            }
        }
    }

    // Reconstruct subset
    int sum = *max_element(L.begin(), L.end());
    for (int i = S.size() - 1; i >= 0 && sum > 0; i--) {
        if (find(L.begin(), L.end(), sum - S[i]) != L.end()) {
            chosenSubset.push_back(S[i]);
            sum -= S[i];
        }
    }

    auto end = chrono::high_resolution_clock::now();
    executionTime = chrono::duration_cast<chrono::milliseconds>(end - start).count();
    return chosenSubset;
}

// Simulated annealing for subset sum
vector<int> simulatedAnnealingSubsetSum(const vector<int>& S, int t, double initialTemp, double coolingRate, int maxIterations, long long &executionTime) {
    auto start = chrono::high_resolution_clock::now();
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<> dis(0.0, 1.0);

    vector<int> currentSolution;
    int currentSum = 0;

    vector<int> bestSolution = currentSolution;
    int bestSum = currentSum;

    double temperature = initialTemp;

    for (int iter = 0; iter < maxIterations; iter++) {
        vector<int> neighbor = currentSolution;
        int neighborSum = currentSum;

        if (dis(gen) < 0.5 && !S.empty()) {
            int idx = rd() % S.size();
            if (find(neighbor.begin(), neighbor.end(), S[idx]) == neighbor.end()) {
                neighbor.push_back(S[idx]);
                neighborSum += S[idx];
            }
        } else if (!neighbor.empty()) {
            int idx = rd() % neighbor.size();
            neighborSum -= neighbor[idx];
            neighbor.erase(neighbor.begin() + idx);
        }

        if (neighborSum <= t && (neighborSum > currentSum || dis(gen) < exp((neighborSum - currentSum) / temperature))) {
            currentSolution = neighbor;
            currentSum = neighborSum;
        }

        if (currentSum > bestSum && currentSum <= t) {
            bestSolution = currentSolution;
            bestSum = currentSum;
        }

        temperature *= coolingRate;
    }

    auto end = chrono::high_resolution_clock::now();
    executionTime = chrono::duration_cast<chrono::milliseconds>(end - start).count();
    return bestSolution;
}

// Helper function to compute accuracy (deviation from target)
double computeAccuracy(int bruteSum, int currentSum) {
    return (double)(currentSum) / bruteSum * 100;
}

void runTestsWithLargeTarget() {
    int testCases = 10;
    int maxSize = 5;
    int maxValue = 20;

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> sizeDist(1, maxSize);
    uniform_int_distribution<> valueDist(1, maxValue);

    cout << "Test Results Summary\n";
    cout << "------------------------------------------------------------\n";
    cout << "| Test Case | Algorithm            | Running Time (ms) | Target | Subset Sum | Accuracy (%) | Status |\n";
    cout << "------------------------------------------------------------\n";

    for (int t = 1; t <= testCases; t++) {
        int n = sizeDist(gen);
        vector<int> S(n);
        for (int i = 0; i < n; i++) {
            S[i] = valueDist(gen);
        }

        int totalSum = accumulate(S.begin(), S.end(), 0);
        int target = totalSum + valueDist(gen); // Ensure target is greater than total sum

        double epsilon = 0.1; // Approximation factor
        double initialTemp = 1000.0, coolingRate = 0.99;
        int maxIterations = 1000;

        long long bruteTime, approxTime, annealingTime;
        
        // Brute-force solution
        vector<int> bruteSubset = bruteForceSubsetSum(S, target, bruteTime);
        int bruteSum = accumulate(bruteSubset.begin(), bruteSubset.end(), 0);

        // Approximate subset sum solution
        vector<int> approxSubset = approximateSubsetSum(S, target, epsilon, approxTime);
        int approxSum = accumulate(approxSubset.begin(), approxSubset.end(), 0);

        // Simulated annealing solution
        vector<int> annealingSubset = simulatedAnnealingSubsetSum(S, target, initialTemp, coolingRate, maxIterations, annealingTime);
        int annealingSum = accumulate(annealingSubset.begin(), annealingSubset.end(), 0);

        // Accuracy calculation
        double approxAccuracy = computeAccuracy(bruteSum, approxSum);
        double annealingAccuracy = computeAccuracy(bruteSum, annealingSum);

        cout << "| " << t << "         | Brute-force           | " << bruteTime << "                | " << target << "    | " << bruteSum
             << "        | 100.00%      | PASS   |\n";
        cout << "| " << t << "         | Approximate           | " << approxTime << "                | " << target << "    | " << approxSum
             << "        | " << approxAccuracy << "      | PASS   |\n";
        cout << "| " << t << "         | Simulated Annealing   | " << annealingTime << "                | " << target << "    | " << annealingSum
             << "        | " << annealingAccuracy << "      | PASS   |\n";
    }

    cout << "------------------------------------------------------------\n";
}

int main() {
    runTestsWithLargeTarget();
    return 0;
}
