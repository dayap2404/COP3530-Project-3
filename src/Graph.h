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
    struct Edge {
        int to;
        int weight;
        bool open;
    };

    unordered_map<int, vector<Edge>> adj;

public:
    // constructor
    Graph();

    // add an edge
    void addEdge(int a, int b, int weight);

    //toggle
    void toggleEdge(int a, int b);

    // is there an edge t/f
    bool edgeExists(int a, int b) const;

    //isopen
    bool isOpen(int a, int b) const;

    //isconnected
    bool isConnected(int start, int end);

    //mst
    int shortestPath(int start, int end);

    //mst cost
    int mstCost(const vector<int>& nodes);

    vector<int> getShortestPathNodes(int start, int goal);

    string getEdgeStatus(int a, int b) const;

    int computeMST(vector<int> nodes, vector<pair<pair<int,int>, int>> edges);
};

#endif
