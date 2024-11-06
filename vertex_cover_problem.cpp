#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

// approch one

// Function to find the minimal vertex cover using a greedy approach
// void vertexCover(vector<int> edges[], int n)
// {
//     vector<bool> visited(n, false);

//     // Iterate over all vertices
//     for (int i = 0; i < n; i++)
//     {
//         // If the vertex is not yet visited
//         if (!visited[i])
//         {
//             // Traverse all adjacent vertices of the current vertex
//             for (int adj : edges[i])
//             {
//                 if (!visited[adj])
//                 {
//                     // Include both vertices in the vertex cover
//                     visited[i] = true;
//                     visited[adj] = true;
//                     break;
//                 }
//             }
//         }
//     }

//     // Print the vertices in the vertex cover
//     cout << "Vertex Cover: ";
//     for (int i = 0; i < n; i++)
//     {
//         if (visited[i])
//         {
//             cout << i << " ";
//         }
//     }
//     cout << endl;
// }

// int main()
// {
//     int n, m;
//     cout << "Enter the number of vertices and edges: ";
//     cin >> n >> m;

//     // Initialize an adjacency list for the graph
//     vector<int> edges[n];
//     cout << "Enter the edges (u v):" << endl;
//     for (int i = 0; i < m; i++)
//     {
//         int u, v;
//         cin >> u >> v;
//         edges[u].push_back(v);
//         edges[v].push_back(u);
//     }

//     // Call the vertex cover function
//     vertexCover(edges, n);

//     return 0;
// }

// 2nd approch
bool check(int n, int k, int m, vector<vector<int>> &e)
{
    int v = n;
    int set = (1 << k) - 1;
    int limit = (1 << v);
    bool vis[n + 1][n + 1];

    while (set < limit)
    {
        memset(vis, false, sizeof(vis));
        int cnt = 0;

        for (int j = 1, v = 1; j < limit; j = j << 1, v++)
        {
            if (set & j)
            {
                // cnt++;
                for (int k = 1; k <= m; k++)
                {

                    if (e[v][k] && !vis[v][k])
                    {
                        vis[v][k] = 1;
                        vis[k][v] = 1;
                        cnt++;
                    }
                }
            }
        }

        if (cnt == m)
        {
            return 1;
        }

        // gosper's hack
        int c = set & -set;
        int r = set + c;
        set = (((r ^ set) >> 2) / c) | r;
    }
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

int vertexCover(vector<pair<int, int>> &e, int n)
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
    int n, m;
    cout << "Enter the number of vertices and edges: ";
    cin >> n >> m;

    // Initialize an adjacency list for the graph
    vector<pair<int, int>> e;
    cout << "Enter the edges (u v):" << endl;
    for (int i = 0; i < m; i++)
    {
        int u, v;
        cin >> u >> v;
        e.push_back({u, v});
        e.push_back({v, u});
    }

    int ans = vertexCover(e, n);

    cout << "Vertex Cover: " << ans << endl;
}