#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>

using namespace std;

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
vector<int> approximateSubsetSum(const vector<int>& S, int t, double epsilon) {
    vector<int> L = {0}; // Initialize with 0 sum
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

    return chosenSubset;
}

// Function to save input and output
void saveToFile(const vector<int>& S, int t, const vector<int>& subset) {
    ofstream outFile("output_data.txt");
    outFile << "{\n";
    outFile << "    \"sticks\": [";
    for (size_t i = 0; i < S.size(); i++) {
        outFile << S[i];
        if (i < S.size() - 1) outFile << ", ";
    }
    outFile << "],\n";
    outFile << "    \"target\": " << t << ",\n";
    outFile << "    \"subset\": [";
    for (size_t i = 0; i < subset.size(); i++) {
        outFile << subset[i];
        if (i < subset.size() - 1) outFile << ", ";
    }
    outFile << "]\n";
    outFile << "}\n";
    outFile.close();
}

int main() {
    int n, t;
    double epsilon;

    cout << "Enter the number of sticks: ";
    cin >> n;

    vector<int> S(n);
    cout << "Enter the lengths of the sticks: ";
    for (int i = 0; i < n; i++) {
        cin >> S[i];
    }

    cout << "Enter the target length: ";
    cin >> t;

    cout << "Enter the approximation factor (epsilon): ";
    cin >> epsilon;

    vector<int> subset = approximateSubsetSum(S, t, epsilon);

    // Save input and output to a file
    saveToFile(S, t, subset);

    cout << "Input and output data saved to output_data.txt for visualization." << endl;
    return 0;
}
