#include "Graph.h"
#include <queue>   // for priority_queue in Dijkstra
#include <climits> // for int max

using namespace std;

// CAMPUS ROADS
//had to fix everything bc if not toggling wasnt going to work

// contructor
Graph::Graph() {}

// adds undirected edge between a and b with weight time
void Graph::addEdge(int a, int b, int weight) {
    // create edge from a → b
    Edge e1;
    e1.to = b;
    e1.weight = weight;
    e1.open = true; // new edge is always open

    // create edge from b to a
    Edge e2;
    e2.to = a;
    e2.weight = weight;
    e2.open = true;

    // push into adjacency list
    adj[a].push_back(e1);
    adj[b].push_back(e2);
}

// checks if edge exists in adjacency list
bool Graph::edgeExists(int a, int b) const {
    if (!adj.count(a)) return false;

    for (const Edge &e : adj.at(a)) {
        if (e.to == b)
            return true;
    }
    return false;
}

void Graph::toggleEdge(int a, int b) {
    // toggle a to b
    for (Edge &e : adj[a]) {
        if (e.to == b) {
            e.open = !e.open;
            break;
        }
    }

    // toggle b to a
    for (Edge &e : adj[b]) {
        if (e.to == a) {
            e.open = !e.open;
            break;
        }
    }
}

// returns edge status
string Graph::getEdgeStatus(int a, int b) const {
    if (!edgeExists(a, b)) return "DNE";

    for (const Edge &e : adj.at(a)) {
        if (e.to == b) {
            return e.open ? "open" : "closed";
        }
    }

    // should never happen
    return "DNE";
}

// BFS check ignoring closed edges
bool Graph::isConnected(int start, int goal) {
    // FIXME
    return false;
}

// Dijkstra shortest path ignoring closed edges
int Graph::shortestPath(int start, int goal) {
    // FIXME
    return -1;
}

// return list of nodes along the shortest path
vector<int> Graph::getShortestPathNodes(int start, int goal) {
    // fixme
    return {};
}

// compute MST cost - so the sum of the weights of chosen vertices
int Graph::computeMST(vector<int> nodes, vector<pair<pair<int,int>,int>> edges) {
    // fixme
    return -1;
}
