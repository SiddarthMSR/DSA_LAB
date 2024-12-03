#include <iostream>
#include <vector>
#include <cstring>

using namespace std;



//1st approch
void vertexCover(vector<int> edges[], int n)
{
    vector<bool> visited(n, false);

    // Iterate over all vertices
    for (int i = 0; i < n; i++)
    {
        // If the vertex is not yet visited
        if (!visited[i])
        {
            // Traverse all adjacent vertices of the current vertex
            for (int adj : edges[i])
            {
                if (!visited[adj])
                {
                    // Include both vertices in the vertex cover
                    visited[i] = true;
                    visited[adj] = true;
                    break;
                }
            }
        }
    }

    // Print the vertices in the vertex cover
    cout << "Vertex Cover: ";
    for (int i = 0; i < n; i++)
    {
        if (visited[i])
        {
            cout << i + 1 << " "; // Convert back to 1-based for output
        }
    }
    cout << endl;
}

int main()
{
    int n, m;
    cout << "Enter the number of vertices and edges: ";
    cin >> n >> m;

    // Initialize an adjacency list for the graph
    vector<int> edges[n];
    cout << "Enter the edges (u v):" << endl;
    for (int i = 0; i < m; i++)
    {
        int u, v;
        cin >> u >> v;
        u--; // Convert to 0-based indexing
        v--; // Convert to 0-based indexing
        edges[u].push_back(v);
        edges[v].push_back(u);
    }

    // Call the vertex cover function
    vertexCover(edges, n);

    return 0;
}



// 2nd approch
void vertexCover(vector<pair<int, int>> edges, int n)
{
    vector<bool> visited(n, false);

    // Iterate over all edges
    for (int i = 0; i < edges.size(); i++)
    {
        int u = edges[i].first;
        int v = edges[i].second;

        // If neither vertex is visited, include both in the vertex cover
        if (!visited[u] && !visited[v])
        {
            visited[u] = true;
            visited[v] = true;
        }
    }

    // Print the vertices in the vertex cover
    cout << "Vertex Cover: ";
    for (int i = 0; i < n; i++)
    {
        if (visited[i])
        {
            cout << i + 1 << " "; // Convert to 1-based indexing for output
        }
    }
    cout << endl;
}

int main()
{
    int n, m;
    cout << "Enter the number of vertices and edges: ";
    cin >> n >> m;

    // Initialize the edge list
    vector<pair<int, int>> edges;
    cout << "Enter the edges (u v):" << endl;
    for (int i = 0; i < m; i++)
    {
        int u, v;
        cin >> u >> v;
        u--; // Convert to 0-based indexing
        v--; // Convert to 0-based indexing
        edges.push_back({u, v});
    }

    // Call the vertex cover function
    vertexCover(edges, n);

    return 0;
}




// 3rd approch

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

        // Gosper's Hack for generating the next combination
        int c = set & -set;
        int r = set + c;
        set = (((r ^ set) >> 2) / c) | r;
    }

    return false; // Add a return statement if no vertex cover is found
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

    vector<pair<int, int>> e;
    cout << "Enter the edges (u v):" << endl;
    for (int i = 0; i < m; i++)
    {
        int u, v;
        cin >> u >> v;
        e.push_back({u, v});
    }

    int ans = vertexCover(e, n);

    cout << "Minimum Vertex Cover: " << ans << endl;

    return 0;
}