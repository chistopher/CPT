
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
    list<Edge*>::iterator selfOut;
    list<Edge*>::iterator selfIn;

    //constructor
    Edge(Node* _from, Node* _to)
    {
        assert(_from);
        assert(_to);

        from = _from;
        to = _to;

        from->outgoingEdges.push_front(this);
        to->incomingEdges.push_front(this);

        selfOut = from->outgoingEdges.begin();
        selfIn = to->incomingEdges.begin();   
    }

    void remove()
    {
        from->outgoingEdges.erase(selfOut);
        to->incomingEdges.erase(selfIn);
    }
};


struct Node
{
    int id;
    list<Edge*> outgoingEdges;
    list<Edge*> incomingEdges;
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

    Edge* connect(Node* from, Node* to)
    {
        auto edge = new Edge(from, to);
        edges.push_back(edge);
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

        for (auto& edge : node->outgoingEdges)
        {
            if (!visited[edge->to->id])
                intern_dfs(edge->to, visited, fnc);
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