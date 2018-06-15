
struct Edge{
    int to;
    int weight;
};

void bellman_ford(vector<vector<Edge>>& graph, int source, int* /*out*/ dist) {

    auto n = graph.size();
    fill(dist, dist+n, numeric_limits<int>::max() / 2);

    int numChanged = 0;
    auto changed = vector<bool>(n, false);

    dist[source] = 0;
    changed[source] = true;
    ++numChanged;

    while(numChanged) {
        //relax all edges
        numChanged = 0;
        for(int i=0; i<n; ++i) {
            if(!changed[i]) continue;
            changed[i] = false;
            for(const auto & edge : graph[i]) {
                auto u = i;
                auto v = edge.to;
                if(dist[u] + edge.weight < dist[v]) {
                    dist[v] = dist[u] + edge.weight;
                    if(!changed[v]) changed[v] = true;
                    ++numChanged;
                }
            }
        }
    }
}
