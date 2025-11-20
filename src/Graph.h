#ifndef GRAPH_H
#define GRAPH_H
#include <vector>
#include <unordered_map> // for adjacency list
#include <string>
#include <utility>     // for pairs
using namespace std;

// basically CAMPUS ROADS

// graph class stores all edges on campus and handles shortest path + mst
class Graph {
private:
    // make adjacency list
    // each int (node) maps to a vector of pairs (neighbor, travel time)
    unordered_map<int, vector<pair<int,int>>> adj;

    // stores closed edges as pairs inside a vector
    vector<pair<int,int>> closedEdges;

public:
    // constructor
    Graph();

    // adds an undirected edge between two locations with the weight being a travel time
    void addEdge(int a, int b, int time);

    // Checks if an edge exists in the adjacency list
    bool edgeExists(int a, int b);

    // checks if an edge is marked as closed
    bool isEdgeClosed(int a, int b);

    // if open, close
    // if closed, open
    void toggleEdge(int a, int b);

    // returns whether open closed or dne for an edge
    string getEdgeStatus(int a, int b);

    // returns true if a path exists ignoring closed edges
    bool isConnected(int start, int goal);

    // returns the shortest path travel time using Dijkstra or -1 if no path exist
    int shortestPath(int start, int goal);

    // returns a list of nodes used in the shortest path
    vector<int> getShortestPathNodes(int start, int goal);

    // computes MST cost of the student zone
    int computeMST(vector<int> nodes, vector<pair<pair<int,int>,int>> edges);
};

#endif
