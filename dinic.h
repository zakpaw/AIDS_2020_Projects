#pragma once
#include <iostream>
#include <vector>
#include <list>
#include <climits>
using namespace std;

struct Edge
{
    int v;
    int flow;
    int C;
    int rev;
};

class Graph
{
    int V;
    int *level;
    vector<Edge> *adj;
    friend class Plague;

public:
    Graph(int V)
    {
        adj = new vector<Edge>[V];
        this->V = V;
        level = new int[V];
    }

    void addEdge(int u, int v, int C)
    {
        Edge a{v, 0, C, int(adj[v].size())};

        Edge b{u, 0, 0, int(adj[u].size())};

        adj[u].push_back(a);
        adj[v].push_back(b); // reverse edge
    }

    bool BFS(int s, int t);
    int sendFlow(int s, int flow, int t, int ptr[]);
    int DinicMaxflow(int s, int t);
};

// Finds if more flow can be sent from s to t.
// Also assigns levels to nodes.
bool Graph::BFS(int s, int t)
{
    for (int i = 0; i < V; i++)
        level[i] = -1;

    level[s] = 0; // Level of source vertex

    list<int> q;
    q.push_back(s);

    vector<Edge>::iterator i;
    while (!q.empty())
    {
        int u = q.front();
        q.pop_front();
        for (i = adj[u].begin(); i != adj[u].end(); i++)
        {
            Edge &e = *i;
            if (level[e.v] < 0 && e.flow < e.C)
            { // Level of current vertex is level of parent + 1
                level[e.v] = level[u] + 1;
                q.push_back(e.v);
            }
        }
    }
    // IF we can not reach to the sink we return false else true
    return level[t] < 0 ? false : true;
}

int min(int a, int b)
{
    if (a > b)
        return b;
    else
        return a;
}

// u : Current vertex
int Graph::sendFlow(int u, int flow, int t, int start[])
{
    // Sink reached
    if (u == t)
        return flow;

    for (; start[u] < adj[u].size(); start[u]++)
    {
        // Pick next edge from adjacency list of u
        Edge &e = adj[u][start[u]];

        if (level[e.v] == level[u] + 1 && e.flow < e.C)
        {
            int curr_flow = min(flow, e.C - e.flow);
            int temp_flow = sendFlow(e.v, curr_flow, t, start);
            if (temp_flow > 0)
            {
                e.flow += temp_flow;
                // subtract flow from reverse edge of current edge
                adj[e.v][e.rev].flow -= temp_flow;
                return temp_flow;
            }
        }
    }

    return 0;
}

int Graph::DinicMaxflow(int s, int t)
{
    // Corner case
    if (s == t)
        return -1;

    int total = 0;

    while (BFS(s, t) == true)
    {
        // store how many edges are visited from V { 0 to V }
        int *start = new int[V + 1]{};
        while (int flow = sendFlow(s, INT_MAX, t, start))
            total += flow;
    }

    return total;
}
