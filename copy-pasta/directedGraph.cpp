
#include <vector>
#include <list>
#include <algorithm>
#include <cassert>
#include <functional>
#include <stack>


using namespace std;


struct Node;

struct Edge
{
    //data
    Node* from;
    Node* to;
    list<Edge*>::iterator twin;

    //constructor
    Edge(Node* _from, Node* _to)
    {
        assert(_from);
        assert(_to);

        from = _from;
        to = _to;
    }

    void remove()
    {
        from->outgoingEdges.erase((**twin).twin);
        to->outgoingEdges.erase(twin);
    }
};


struct Node
{
    int id;
    list<Edge*> outgoingEdges;
};


struct Graph
{
    //data
    vector<Node*> nodes;
    vector<Edge*> edges;

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
        for (auto edge : edges)
        {
            delete edge;
        }
    }

    pair<Edge*, Edge*> connect(Node* from, Node* to)
    {
        auto first = new Edge(from, to);
        auto second = new Edge(to, from);

        edges.push_back(first);
        edges.push_back(second);

        from->outgoingEdges.push_front(first);
        to->outgoingEdges.push_front(second);

        first->twin = to->outgoingEdges.begin();
        second->twin = from->outgoingEdges.begin();

        return { first, second };
    }

    void dfs(Node* node, function<void(Node*)> fnc)
    {
        vector<bool> visited(nodes.size(), false);
        internal_dfs(node, visited, fnc);
    }

    void internal_dfs(Node* node, vector<bool>& visited, function<void(Node*)> fnc)
    {
        visited[node->id] = true;

        //do stuff
        fnc(node);

        for (auto& edge : node->outgoingEdges)
        {
            if (!visited[edge->to->id])
                internal_dfs(edge->to, visited, fnc);
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

            for (auto edge : current->outgoingEdges)
            {
                if (!seen[edge->to->id])
                {
                    seen[edge->to->id] = true;
                    stack.push(edge->to);
                }
            }
        }
    }
};