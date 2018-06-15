
struct Edge{
    int to;
    int weight;
};

void dijkstra(vector<vector<Edge>>& graph, int source, int* /*out*/ dist) {

    auto n = graph.size();
    fill(dist, dist+n, numeric_limits<int>::max() / 2);

    using T = pair<int, int>; // first is weight second is node index
    priority_queue<T, vector<T>, greater<T> > prio_queue;

    dist[source] = 0;
    prio_queue.push({0, source});

    auto finalized = vector<bool>(n, false);
    while(!prio_queue.empty()){
        auto u = prio_queue.top().second;
        prio_queue.pop();

        if(finalized[u]) continue;
        finalized[u] = true;

        for(Edge& edge : graph[u]){
            auto v = edge.to;
            if(dist[u] + edge.weight < dist[v]) {
                dist[v] = dist[u] + edge.weight;
                prio_queue.push({dist[v], v});
            }
        }
    }
}
