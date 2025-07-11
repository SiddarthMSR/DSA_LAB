#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

void vertexCoverApproach1(vector<int> edges[], int n)
{
    vector<bool> visited(n, false);

    for (int i = 0; i < n; i++)
    {
        if (!visited[i])
        {
            for (int adj : edges[i])
            {
                if (!visited[adj])
                {
                    visited[i] = true;
                    visited[adj] = true;
                    break;
                }
            }
        }
    }

    cout << "Vertex Cover: ";
    for (int i = 0; i < n; i++)
    {
        if (visited[i])
        {
            cout << i + 1 << " ";
        }
    }
    cout << endl;
}

void vertexCoverApproach2(vector<pair<int, int>> edges, int n)
{
    vector<bool> visited(n, false);

    for (int i = 0; i < edges.size(); i++)
    {
        int u = edges[i].first;
        int v = edges[i].second;

        if (!visited[u] && !visited[v])
        {
            visited[u] = true;
            visited[v] = true;
        }
    }

    cout << "Vertex Cover: ";
    for (int i = 0; i < n; i++)
    {
        if (visited[i])
        {
            cout << i + 1 << " ";
        }
    }
    cout << endl;
}

bool check(int n, int k, int m, vector<vector<int>> &e)
{
    int set = (1 << k) - 1;
    int limit = (1 << n);

    while (set < limit)
    {
        vector<vector<bool>> vis(n + 1, vector<bool>(n + 1, false));
        int cnt = 0;

        for (int i = 0; i < n; i++)
        {
            if (set & (1 << i))
            {
                for (int j = 1; j <= n; j++)
                {
                    if (e[i + 1][j] && !vis[i + 1][j])
                    {
                        vis[i + 1][j] = true;
                        vis[j][i + 1] = true;
                        cnt++;
                    }
                }
            }
        }

        if (cnt == m)
        {
            return true;
        }

        int c = set & -set;
        int r = set + c;
        set = (((r ^ set) >> 2) / c) | r;
    }

    return false;
}

int helper(vector<vector<int>> &e, int n, int m)
{
    int low = 1;
    int high = n;
    int ans = -1;

    while (low <= high)
    {
        int mid = low + (high - low) / 2;

        if (check(n, mid, m, e))
        {
            ans = mid;
            high = mid - 1;
        }
        else
        {
            low = mid + 1;
        }
    }

    return ans;
}

int vertexCoverApproach3(vector<pair<int, int>> &e, int n)
{
    int m = e.size();
    vector<vector<int>> g(n + 1, vector<int>(n + 1, 0));

    for (int i = 0; i < m; i++)
    {
        g[e[i].first][e[i].second] = 1;
        g[e[i].second][e[i].first] = 1;
    }

    return helper(g, n, m);
}

int main()
{
    int n, m, approach;
    cout << "Enter the number of vertices and edges: ";
    cin >> n >> m;
    
    cout << "Choose approach (1, 2, or 3): ";
    cin >> approach;

    if (approach == 1)
    {
        vector<int> edges[n];
        cout << "Enter the edges (u v):" << endl;
        for (int i = 0; i < m; i++)
        {
            int u, v;
            cin >> u >> v;
            u--;
            v--;
            edges[u].push_back(v);
            edges[v].push_back(u);
        }
        vertexCoverApproach1(edges, n);
    }
    else if (approach == 2)
    {
        vector<pair<int, int>> edges;
        cout << "Enter the edges (u v):" << endl;
        for (int i = 0; i < m; i++)
        {
            int u, v;
            cin >> u >> v;
            u--;
            v--;
            edges.push_back({u, v});
        }
        vertexCoverApproach2(edges, n);
    }
    else if (approach == 3)
    {
        vector<pair<int, int>> e;
        cout << "Enter the edges (u v):" << endl;
        for (int i = 0; i < m; i++)
        {
            int u, v;
            cin >> u >> v;
            e.push_back({u, v});
        }
        int ans = vertexCoverApproach3(e, n);
        cout << "Minimum Vertex Cover: " << ans << endl;
    }
    else
    {
        cout << "Invalid approach selected!" << endl;
    }

    return 0;
}