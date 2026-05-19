class Solution {
  public:
    // dfs function to explore all reachable nodes
    void dfs(vector<vector<int>> &adj, int c, vector<bool> &visited) {
        visited[c] = true;
        for (auto i : adj[c]) {
            if (!visited[i])
                dfs(adj, i, visited);
        }
    }

    // Construct adjacency list without the edge (c, d)
    vector<vector<int>> constructadj(int V, vector<vector<int>> &edges, int c, int d) {
        vector<vector<int>> adj(V);
        for (auto &edge : edges) {

            // Skip the edge (c, d) or (d, c)
            if ((edge[0] == c && edge[1] == d) || (edge[0] == d && edge[1] == c))
                continue;

            adj[edge[0]].push_back(edge[1]);
            adj[edge[1]].push_back(edge[0]);
        }
        return adj;
    }

    // Check if the edge (c, d) is a bridge
    bool isBridge(int V, vector<vector<int>> &edges, int c, int d) {
        vector<vector<int>> adj = constructadj(V, edges, c, d);

        vector<bool> visited(V, false);
        dfs(adj, c, visited);

        // if d is not reachable from c ? bridge
        return !visited[d];
    }
};


// tarjan
vector<int> tin, low;
vector<bool> visited;
vector<bool> is_bridge;
int timer = 0;

void dfs_bridge(int v, int parent_edge) {
    visited[v] = true;
    tin[v] = low[v] = timer++;

    for (auto &p : adj[v]) {
        int to = p.first;
        int id = p.second;

        if (id == parent_edge) continue;

        if (visited[to]) {
            low[v] = min(low[v], tin[to]);
        } else {
            dfs_bridge(to, id);
            low[v] = min(low[v], low[to]);

            if (low[to] > tin[v]) {
                is_bridge[id] = true;
            }
        }
    }
}
