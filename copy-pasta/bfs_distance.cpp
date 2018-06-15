
using Graph = vector<vector<int>>; // adjacency list

// return bfs distance to source
vector<int> bfs_distance(Graph& neighbors, int source) {
    auto dist = vector<int>(neighbors.size(), -1);
    queue<int> Q;

    dist[source] = source;
    Q.push(source);

    while(!Q.empty()) {
        auto current = Q.front(); Q.pop();
        // handle current here!
        for (auto neighbor : neighbors[current])
            if (dist[neighbor] == -1) {
                dist[neighbor] = 1 + dist[current];
                Q.push(neighbor);
            }
    }
    return dist;
}
