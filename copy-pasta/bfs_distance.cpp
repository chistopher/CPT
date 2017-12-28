
struct Graph
{
    int n; //vetices from 0 to n-1
    vector<vector<int>> neighbors; //adjacency list

    Graph(int size)
    {
        n = size;
        neighbors.resize(n);
    }

    void addEdge(int from, int to)
    {
        neighbors[from].push_back(to);
    }

    int bfs_distance(int from, int to)
    {
        if(from == to)
            return 0;

        auto visited = vector<bool>(n,false);
        auto prev = vector<int>(n, -1);

        list<int> queue;
        visited[from] = true;
        queue.push_back(from);

        while(!queue.empty())
        {
            auto current = queue.front();
            queue.pop_front();

            // handle current here!

            // queue all neighbors
            for (auto neighbor : neighbors[current])
                if (!visited[neighbor])
                {
                    visited[neighbor] = true;
                    queue.push_back(neighbor);
                    prev[neighbor] = current;
                    if(neighbor == to)
                        break;
                }
        }

        auto p = to;
        auto dist = 0;
        while(prev[p] != -1)
        {
            dist++;
            p=prev[p];
        }
        return dist == 0 ? -1 : dist;
    }
};
