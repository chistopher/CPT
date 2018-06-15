
struct Edge {
    Edge* twin = nullptr;
    int to;
    unsigned short flow = 0;
    unsigned short capacity = 0;
    bool isResidual = false;
    Edge(int to_) : to{to_} {}
};
using Graph = vector<vector<Edge*>>;

void createEdge(Graph& graph, int from, int to, unsigned short capacity) {
    auto edge = new Edge(to);
    edge->capacity = capacity;
    graph[from].push_back(edge);
    auto resEdge = new Edge(from);
    resEdge->isResidual = true;
    edge->twin = resEdge;
    resEdge->twin = edge;
    graph[to].push_back(resEdge);
}

vector<Edge*> bfs_with_path(Graph& graph, int source, int target){
    auto n = graph.size();
    auto visited = vector<bool>(n, false);
    auto prev = vector<Edge*>(n, nullptr);
    queue<int> Q;
    Q.push(source);
    visited[source] = true;
    while(!Q.empty()) {
        auto current = Q.front(); Q.pop();
        for(auto edge : graph[current]) {
            if(!visited[edge->to] && edge->capacity != edge->flow) {
                Q.push(edge->to);
                prev[edge->to] = edge;
                visited[edge->to] = true;
                if(edge->to == target)
                    return prev; // break!!!
            }
        }
    }
    return prev;
}

// find augmenting path; augment and update graph; return how much was augmented
int augmentingPath(Graph& graph, int source, int target) {
    auto prev = bfs_with_path(graph, source, target);
    vector<Edge*> path;
    int pathCapacity = INT_MAX;
    Edge* edge = prev[target];
    if(edge == nullptr) // target not reachable
        return 0;
    while(edge != nullptr) {
        path.push_back(edge);
        pathCapacity = min(pathCapacity, edge->capacity - edge->flow);
        edge = prev[edge->twin->to];
    }
    //augment path by pathcapacity
    for(auto edge : path) {
        edge->flow += pathCapacity;
        if(edge->isResidual)
            edge->twin->flow -= pathCapacity;
        else
            edge->twin->capacity = edge->flow;
    }
    return pathCapacity;
}
