#include "Graph.h"
#include <queue>   // for priority_queue in Dijkstra
#include <climits> // for int max
#include <unordered_set>

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
    // find a path from start to goal w OPEN EDGES ONLY
    //use bfs
    //edge case-same node
    if (start == goal) return true;
    //check that start exists in the graph
    if (!adj.count(start) || !adj.count(goal)) return false;

    queue<int> q;
    unordered_set<int> visited;

    q.push(start);
    visited.insert(start);

    while (!q.empty()) {
        int cur = q.front();
        q.pop();

        //if goal reached return true
        if (cur == goal) return true;
        //look at the neighbors
        for (const Edge &e : adj.at(cur)) {
            if (!e.open) {continue;}    //skip closed
            int neighbor = e.to;
            if (!visited.count(neighbor)) {
                visited.insert(neighbor);
                q.push(neighbor);
            }
        }

    }

    return false;
}

// Dijkstra shortest path ignoring closed edges
int Graph::shortestPath(int start, int goal) {
    //neither are found
    if (!adj.count(start) || !adj.count(goal)) return -1;
    // need a map to use for distance
    //need a pq min heap
    //need a visited set
    unordered_map<int, int> dist;
    //make them to infinity just like the tables from class
    for (auto &pair : adj) {
        dist[pair.first] = INT_MAX;
    }
    //distance to start = 0
    dist[start] = 0;
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;
    unordered_set<int> visited;

    pq.push({0, start});
    while (!pq.empty()) {
        auto top = pq.top();
        pq.pop();
        int cur = top.first;
        int node = top.second;
        //if goal reached, this is the shorted path
        if (node == goal) {
            return cur;
        }
        //node alr visited then skip
        if (visited.count(node)) { continue ;}
        visited.insert(node);
        //do the neighbors
        for (const Edge &e : adj.at(node)) {
            if (!e.open) continue;
            int neighbor = e.to;
            int weight = e.weight;
            //if shorter path found
            if (cur + weight < dist[neighbor]) {
                dist[neighbor] = cur + weight;
                pq.push(make_pair(cur + weight, neighbor));
            }
        }
    }
    return -1;
}

// return list of nodes along the shortest path
vector<int> Graph::getShortestPathNodes(int start, int goal) {
    // if either node doesnt exist, no path possible
    if (!adj.count(start) || !adj.count(goal)) {
        return {};
    }

    // distance table
    unordered_map<int, int> dist;
    // parent table to rebuild the path
    unordered_map<int, int> parent;

    // initialize everything
    for (auto &p : adj) {
        dist[p.first] = INT_MAX;
        parent[p.first] = -1;    // no parent yet
    }

    dist[start] = 0;
    parent[start] = start;       // start is its own parent

    // min-heap for dijkstra
    priority_queue<
        pair<int,int>,
        vector<pair<int,int>>,
        greater<pair<int,int>>
    > pq;

    pq.push({0, start});

    unordered_set<int> visited;

    while (!pq.empty()) {
        auto top = pq.top();
        pq.pop();

        int curDist = top.first;
        int node = top.second;

        // if we reached the goal early, stop here
        if (node == goal) {
            break;
        }

        if (visited.count(node)) continue;
        visited.insert(node);

        // explore neighbors
        for (const Edge &e : adj[node]) {
            if (!e.open) continue;   // ignore closed edges

            int neighbor = e.to;
            int weight = e.weight;

            // normal dijkstra relaxation
            if (curDist + weight < dist[neighbor]) {
                dist[neighbor] = curDist + weight;
                parent[neighbor] = node;    // store where we came from
                pq.push({dist[neighbor], neighbor});
            }
        }
    }

    // distance stays infinity
    if (dist[goal] == INT_MAX) {
        return {};
    }

    // now rebuild the path
    vector<int> path;
    int cur = goal;

    while (cur != start) {
        path.push_back(cur);
        cur = parent[cur];
        if (cur == -1) {

            return {};
        }
    }

    // add start node
    path.push_back(start);

    // path is reversed so fix it
    reverse(path.begin(), path.end());

    return path;
}

// compute MST cost - so the sum of the weights of chosen vertices
int Graph::computeMST(vector<int> nodes, vector<pair<pair<int,int>,int>> edges) {
    // using prims
    // no nodes means cost is 0
    if (nodes.empty()) return 0;

    // make adj list for subgraph
    unordered_map<int, vector<pair<int,int>>> subAdj;
    for (auto &e : edges) {
        int u = e.first.first;
        int v = e.first.second;
        int w = e.second;

        subAdj[u].push_back({v, w});
        subAdj[v].push_back({u, w});
    }

    //prims alg
    unordered_set<int> inMST;         // nodes already in mst
    priority_queue<
        pair<int,int>,
        vector<pair<int,int>>,
        greater<pair<int,int>>
    > pq;   // min heap w weight,node

    // start at first node
    int start = nodes[0];
    pq.push({0, start});

    int mstCost = 0;


    while (!pq.empty()) {
        auto top = pq.top();
        pq.pop();

        int weight = top.first;
        int node = top.second;

        // if we already used this node, skip
        if (inMST.count(node)) continue;

        // include this node
        inMST.insert(node);
        mstCost += weight;

        // push neighbors into pq
        for (auto &p : subAdj[node]) {
            int neighbor = p.first;
            int w = p.second;

            if (!inMST.count(neighbor)) {
                pq.push({w, neighbor});
            }
        }
    }


    return mstCost;
}

//Sources: i got inspo from this for Dijkstras:
//https://www.geeksforgeeks.org/dsa/dijkstras-shortest-path-algorithm-using-priority_queue-stl/
// and this for prims:
// https://www.geeksforgeeks.org/dsa/prims-algorithm-using-priority_queue-stl/