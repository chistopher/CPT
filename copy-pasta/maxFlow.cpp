#include <iostream>
#include <vector>
#include <cassert>

using namespace std;


struct Edge; // FWD

struct Node
{
    int id;

    vector<Edge*> outgoingEdges;
    bool inCut = false; // relevant to find set of cut edges
};

struct Edge
{
    Node* from;
    Node* to;

    int flow = 0;
    int capacity = 1;

    bool isResidual = false;
    Edge* twin = nullptr;

    void createResidual();
};

void Edge::createResidual()
{
    if(twin != nullptr)
        return;

    //create residual Edge
    auto resEdge = new Edge;

    resEdge->from = to;
    resEdge->to = from;
    resEdge->isResidual = true;
    resEdge->flow = 0;
    resEdge->capacity = 0;

    //connect both edges
    twin = resEdge;
    resEdge->twin = this;

    to->outgoingEdges.push_back(resEdge);
}

vector<Edge*> realEdges;

void createEdge(Node* from, Node* to, int capacity)
{
    auto edge = new Edge;
    edge->from = from;
    edge->to = to;
    edge->capacity = capacity;

    from->outgoingEdges.push_back(edge);
    edge->createResidual();

    realEdges.push_back(edge);
}

int numNodes=0;

// find augmenting path; augment and update graph; return how much was augmented
int augmentingPath(Node* source, Node* target)
{
    auto visited = vector<bool>(numNodes, false);
    auto prev = vector<Edge*>(numNodes);

    prev[target->id] = nullptr;
    prev[source->id] = nullptr;
    // vector and start pointer is more efficient than a real queue
    vector<Node*> Q;
    int front = 0;
    Q.push_back(source);
    visited[source->id] = true;

    bool found = false;
    while(front!=Q.size())
    {
        Node* current = Q[front++];
        for(Edge* edge : current->outgoingEdges)
        {
            //already seen this node
            if(!visited[edge->to->id] && !(edge->capacity == edge->flow))
            {
                Q.push_back(edge->to);
                prev[edge->to->id] = edge;
                visited[edge->to->id] = true;
                if(edge->to == target)
                {
                    found = true;
                    break;
                }
            }
        }
        //break if target was found
        if(found) break;
    }

    vector<Edge*> path;
    int pathCapacity = 100000;
    Edge* edge = prev[target->id];
    if(edge == nullptr)
        return 0;
    while(edge != nullptr)
    {
        path.push_back(edge);
        pathCapacity = min(pathCapacity, edge->capacity - edge->flow);
        edge = prev[edge->from->id];
    }

    //augment path by pathcapacity
    for(Edge* edge : path)
    {
        edge->flow += pathCapacity;

        if(edge->isResidual)
        {
            edge->twin->flow -= pathCapacity;
        }
        else
        {
            edge->twin->capacity = edge->flow;
        }
    }

    return pathCapacity;
}


//to mark nodes reachable from source
void bfs(Node* source)
{
    //bfs from source
    auto visited = vector<bool>(numNodes, false);

    vector<Node*> Q;
    int front = 0;
    Q.push_back(source);
    visited[source->id] = true;
    source->inCut = true;


    while(front!=Q.size())
    {
        Node* current = Q[front++];
        //Q.pop();

        for(Edge* edge : current->outgoingEdges)
        {
            //already seen this node
            if(!visited[edge->to->id] && !(edge->capacity == edge->flow))
            {
                Q.push_back(edge->to);
                visited[edge->to->id] = true;
                edge->to->inCut = true;
            }
        }
    }
}





int main()
{
    std::iostream::sync_with_stdio(false);
    cin.tie(NULL);
    //std::freopen("../sample.in", "r", stdin);
    //std::freopen("../largeSample.in", "r", stdin);


    //read some data
    int n,m;
    cin >> n >> m;
    numNodes = n;

    //build nodes
    auto nodes = vector<Node*>(n);
    for(int i=0; i<n; ++i)
    {
        nodes[i] = new Node;
        nodes[i]->id = i;
    }

    //build edges
    for(int i=0; i<m; ++i)
    {
        int from, to, weight;
        cin >> from >> to >> weight;

        createEdge(nodes[from], nodes[to], weight);
    }


    //compute maxFlow
    int flow = 0;

    for(int i=0; i<100000*m; ++i)
    {
        int augmented = augmentingPath(nodes[0], nodes[n-1]);

        if(augmented == 0)
            break;
        else
            flow += augmented;
    }

    bfs(nodes[0]);

    for(Edge* edge : realEdges)
    {
        if(edge->from->inCut && !edge->to->inCut)
        {
            cout << edge->from->id << " " << edge->to->id << endl;

        }
    }

    return 0;
}
