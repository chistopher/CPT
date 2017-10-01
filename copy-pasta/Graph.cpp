
#include <vector>
#include <algorithm>
#include <cassert>
#include <functional>
#include <stack>
#include <unordered_map>


using namespace std;


struct Node;

struct Edge
{
    //data
    Node* from;
    Node* to;
};


struct Node
{
    int id;
    unordered_map<Node*, Edge*> edges;
};


struct Graph
{
    //data
    vector<Node*> nodes;
    unordered_map<pair<Node*,Node*>, Edge*> edges;

    //constructor
    Graph(int size)
    {
        nodes.reserve(size);
        for (int i = 0; i < size; ++i)
        {
            auto node = new Node;
            node->id = i;
            nodes.push_back(node);
        }
    }

    ~Graph()
    {
        for (auto node : nodes)
        {
            delete node;
        }
        for (auto& pair : edges)
        {
            delete pair.second;
        }
    }

    Edge* connect(Node* from, Node* to)
    {
        auto lower = (from->id < to->id) ? from : to;
        auto higher = (from->id > to->id) ? from : to;

        if (edges.count({lower, higher}) > 0) //edge already exists
            return;

        auto edge = new Edge{from, to};
        edges[{lower, higher}] = edge;

        from->edges[to] = edge;
        to->edges[from] = edge;

        return edge;
    }

    void dfs(Node* node, function<void(Node*)> fnc)
    {
        vector<bool> visited(nodes.size(), false);
        intern_dfs(node, visited, fnc);
    }

    void intern_dfs(Node* node, vector<bool>& visited, function<void(Node*)> fnc)
    {
        visited[node->id] = true;

        //do stuff
        fnc(node);

        for (auto& pair : node->edges) //pair is {neighbor, edge}
        { 
            if (!visited[pair.first->id])
                intern_dfs(pair.first, visited, fnc);
        }
    }

    void bfs(Node* node, function<void(Node*)> fnc)
    {
        stack<Node*, vector<Node*>> stack;
        vector<bool> seen(nodes.size(), false);

        seen[node->id] = true;
        stack.push(node);

        while (!stack.empty())
        {
            auto current = stack.top();
            stack.pop();

            fnc(current);

            for (auto& pair : current->edges) //pair is {neighbor, edge}
            {
                if (!seen[pair.first->id])
                {
                    seen[pair.first->id] = true;
                    stack.push(pair.first);
                }
            }
        }
    }
};