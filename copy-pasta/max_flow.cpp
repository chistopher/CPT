
struct edge {
    int from, to;
    int flow, cap;
    edge* twin;
};
vector<vector<edge*>> adj;

auto* e1 = new edge{a, b, 0, c, nullptr};
auto* e2 = new edge{b, a, 0, c, nullptr};
e1->twin = e2;
e2->twin = e1;
adj[a].push_back(e1);
adj[b].push_back(e2);

// Ford Fulkerson
int flow = 0;
while (true) {
    vector<edge*> inc(n, nullptr);
    queue<int> q{{s}};
    while (!q.empty()) {
        auto v = q.front(); q.pop();
        for (auto e : adj[v])
            if (!inc[e->to] && e->flow < e->cap) {
                q.push(e->to);
                inc[e->to] = e;
            }
    }
    if (!inc[t]) break;
    int aug = 1e9;
    for (int v = t; v != s; v = inc[v]->from)
        aug = min(aug, inc[v]->cap - inc[v]->flow);
    flow += aug;
    for (int v = t; v != s; v = inc[v]->from) {
        inc[v]->flow += aug;
        inc[v]->twin->flow -= aug;
    }
}

// Dinic's
int dfs(int v, int aug, vector<int>& dist, vector<int>& next) {
    if (v == t) return aug;
    for (int& i = next[v]; i<adj[v].size(); ++i) {
        auto e = adj[v][i];
        if (e->flow == e->cap) continue;
        if (dist[e->to] != dist[v] + 1) continue;
        int pushed = dfs(e->to, min(aug, e->cap - e->flow), dist, next);
        if (pushed == 0) continue;
        e->flow += pushed;
        e->twin->flow -= pushed;
        return pushed;
    }
    return 0;
}

int flow = 0;
while(true) {
    vector<int> dist(n, INF);
    dist[s] = 0;
    queue<int> q{{s}};
    while (!q.empty()) {
        auto v = q.front(); q.pop();
        for (auto e : adj[v])
            if (dist[e->to] == INF && e->flow < e->cap) {
                q.push(e->to);
                dist[e->to] = dist[v] + 1;
            }
    }
    if (dist[t]==INF) break;
    vector<int> next(n,0);
    int aug;
    while (aug = dfs(s,INF,dist,next)) flow += aug;
}

