#include "Graph.h"
#include <queue>   // for priority_queue in Dijkstra
#include <climits> // for int max

using namespace std;

// CAMPUS ROADS

// contructor, FIXME
Graph::Graph() {}

// adds undirected edge between a and b with weight time
void Graph::addEdge(int a, int b, int time) {
    // add b to a's adjacency list
    adj[a].push_back({b, time});

    // add a to b's adjacency list
    adj[b].push_back({a, time});
}

// checks if edge exists in adjacency list
bool Graph::edgeExists(int a, int b) {
    // if a is not in the map at all, edge does not exist
    if (adj.find(a) == adj.end()) return false;

    // check adjacency list of a for neighbor b
    for (auto &p : adj[a]) {
        if (p.first == b) return true;
    }
    return false;
}

// checks if an edge is in closedEdges vector
bool Graph::isEdgeClosed(int a, int b) {
    // check both orders bc undirected
    for (auto &p : closedEdges) {
        if ((p.first == a && p.second == b) ||
            (p.first == b && p.second == a)) {
            return true;
        }
    }
    return false;
}

// toggle edge open/closed
void Graph::toggleEdge(int a, int b) {
    // if edge is already closed reopen it by removing from closedEdges
    for (int i = 0; i < closedEdges.size(); i++) {
        if ((closedEdges[i].first == a && closedEdges[i].second == b) ||
            (closedEdges[i].first == b && closedEdges[i].second == a)) {
            closedEdges.erase(closedEdges.begin() + i);
            return;
        }
    }

    // close it by adding to closedEdges
    closedEdges.push_back({a, b});
}

// returns edge status
string Graph::getEdgeStatus(int a, int b) {
    // if edge does not exist at all
    if (!edgeExists(a, b)) return "DNE";

    // if edge is in closed list
    if (isEdgeClosed(a, b)) return "closed";

    // edge is open
    return "open";
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
