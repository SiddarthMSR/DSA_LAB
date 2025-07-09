#include <bits/stdc++.h>
using namespace std;

class Setcover {
private:
    vector<set<int>> FS; // family of sets
    set<int> X;
    random_device rd;
    mt19937 gen;

    set<int> Union(const vector<set<int>> &sets) {
        set<int> fin;
        for (const auto &x : sets) {
            fin.insert(x.begin(), x.end());
        }
        return fin;
    }

    int intersection_len(set<int> a, set<int> b) {
        int len = 0;
        for (auto &x : a) {
            if (b.find(x) != b.end()) len++;
        }
        return len;
    }

    int find_max_set(vector<set<int>> subfamily, set<int> Y) {
        int max_idx = 0, maxv = 0;
        int len;
        for (int i = 0; i < subfamily.size(); i++) {
            if (subfamily[i].size() < Y.size())
                len = intersection_len(subfamily[i], Y);
            else
                len = intersection_len(Y, subfamily[i]);
            if (len > maxv) max_idx = i, maxv = len;
        }
        return max_idx;
    }

    void set_diff(set<int> &Y, set<int> &Z) {
        set<int> L;
        for (auto &x : Y) {
            if (Z.find(x) == Z.end()) L.insert(x);
        }
        Y.clear();
        Y = L;
    }

    void my_set_union(set<int> &a, set<int> &b) {
        for (auto &x : b) a.insert(x);
    }

    vector<int> RandVec() {
        vector<int> v(FS.size(), 0);
        set<int> covered_ele;
        set<int> uncovered_idx;
        for (int i = 0; i < FS.size(); i++) uncovered_idx.insert(i);

        while (covered_ele.size() < X.size()) {
            uniform_int_distribution<> dis(0, uncovered_idx.size() - 1);
            auto it = uncovered_idx.begin();
            advance(it, dis(gen));

            my_set_union(covered_ele, FS[*it]);
            v[*it] = 1;
            uncovered_idx.erase(it);
        }
        return v;
    }

    vector<int> Neighbor(vector<int> v) {
        uniform_int_distribution<> dis(0, FS.size() - 1);
        int idx = dis(gen);
        v[idx] ^= 1;
        return v;
    }

    bool accept(vector<int> v) {
        vector<set<int>> subfamily;
        for (int i = 0; i < FS.size(); i++) {
            if (v[i]) subfamily.push_back(FS[i]);
        }
        return X == Union(subfamily);
    }

    int cost(vector<int> &v) {
        return accumulate(v.begin(), v.end(), 0);
    }

public:
    Setcover(const vector<set<int>> &sets) : gen(rd()) {
        FS = sets;
        X = Union(sets);
    }

    void TakeInput() {
        FS.clear();
        X.clear();
        cout << "Enter the # of sets in the family.\n";
        int n;
        cin >> n;
        for (int i = 0; i < n; i++) {
            set<int> temp;
            cout << "Enter the number of elements in the set " << i + 1 << " \n";
            int j;
            cin >> j;
            cout << "Enter the elements.\n";
            int k;
            while (j--) {
                cin >> k;
                temp.insert(k);
                X.insert(k);
            }
            FS.push_back(temp);
        }
    }

    vector<set<int>> GreedyCover() {
        vector<set<int>> subfamily = FS;
        vector<set<int>> ans;
        set<int> Y = X;
        int idx;
        while (!Y.empty()) {
            idx = find_max_set(subfamily, Y);
            ans.push_back(subfamily[idx]);
            set_diff(Y, ans.back());
            subfamily.erase(subfamily.begin() + idx);
        }
        return ans;
    }

    vector<set<int>> Simulated_Annealing() {
        vector<int> curr = RandVec(), best = curr;
        int batches = 10;
        int bestval = cost(best);
        int currval = bestval;
        int max_Iter = 1e4;
        double Temp = 1000;
        double alpha = 0.95;
        double eps = 1e-5;
        int delta;
        uniform_real_distribution<> dis(0.0, 1.0);

        for (int i = 0; i < batches; i++) {
            Temp = 1000;
            for (int j = 0; j < max_Iter && Temp > eps; j++) {
                vector<int> neigh = Neighbor(curr);
                if (!accept(neigh)) continue;
                delta = cost(curr) - cost(neigh);
                if (delta < 0 || exp(-1 * delta / Temp) > dis(gen)) {
                    curr = neigh;
                    currval = cost(curr);
                }
                if (currval < bestval) {
                    best = curr;
                    bestval = currval;
                }
                Temp *= alpha;
            }
        }

        vector<set<int>> ans;
        for (int i = 0; i < best.size(); i++) {
            if (best[i]) ans.push_back(FS[i]);
        }
        return ans;
    }

    vector<set<int>> BruteForce() {
        if (FS.size() >= 30) {
            cout << "Sorry unable to fit in the memory.\n";
            return {};
        }
        vector<set<int>> subfamily;
        vector<set<int>> best = FS;
        size_t maxpos = 1ULL << FS.size();
        for (size_t i = 1; i < maxpos; i++) {
            subfamily.clear();
            for (size_t j = 0; j < FS.size(); j++) {
                if ((i & (1ULL << j)) != 0) subfamily.push_back(FS[j]);
            }
            if (subfamily.size() > best.size()) continue;
            if (X == Union(subfamily)) {
                if (best.size() > subfamily.size()) {
                    best = subfamily;
                }
            }
        }
        return best;
    }
};

void print(const vector<set<int>> &vecOfSets) {
    cout << "{" << endl;
    for (size_t i = 0; i < vecOfSets.size(); ++i) {
        cout << "    {";
        size_t count = 0;
        for (int val : vecOfSets[i]) {
            cout << val;
            if (++count != vecOfSets[i].size()) cout << ",";
        }
        cout << "}";
        if (i != vecOfSets.size() - 1) cout << ",";
        cout << endl;
    }
    cout << "};" << endl;
}

int main() {
    vector<set<int>> F = {
        {1, 2, 3, 4, 5, 6},
        {5, 6, 8, 9},
        {1, 4, 7, 10},
        {2, 5, 8, 11, 7},
        {3, 6, 9, 12},
        {10, 11}
    };

    Setcover ans(F);

    cout << "Enter the way you want to give the input.\n";
    cout << "1.Hardcoded\n";
    cout << "2.In the terminal\n";
    int choice;
    cin >> choice;

    if (choice == 2) {
        ans.TakeInput();
    }

    vector<set<int>> Greedy = ans.GreedyCover();
    vector<set<int>> Brute = ans.BruteForce();
    vector<set<int>> SA = ans.Simulated_Annealing();

    cout << "Greedy Set Cover.\n";
    print(Greedy);
    cout << "BruteForce Set Cover.\n";
    print(Brute);
    cout << "Simulated Annealing Set Cover.\n";
    print(SA);

    cout << "\n| Algorithm           | Size of Cover |\n";
    cout << "|---------------------|---------------|\n";
    cout << "| Brute Force         | " << Brute.size() << "             |\n";
    cout << "| Greedy              | " << Greedy.size() << "             |\n";
    cout << "| Simulated Annealing | " << SA.size() << "             |\n";
}
