#include "CampusCompass.h"
#include "Graph.h"
#include "StudentManager.h"
#include "Helpers.h"
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <unordered_set>

using namespace std;

CampusCompass::CampusCompass() {}

bool CampusCompass::ParseCSV(const string &edges_filepath, const string &classes_filepath) {
    // return boolean based on whether parsing was successful or not

    // going to read edges.csv
    ifstream edges_file(edges_filepath);
    if (!edges_file.is_open()) {
        return false; //cant open file
    }
    string line;

    //skip header
    getline(edges_file, line);
    // build the graph
    while (getline(edges_file, line)) {
        stringstream ss(line);
        string loc1_str, loc2_str, name1, name2, time_str;

        // read five values
        getline(ss, loc1_str, ',');
        getline(ss, loc2_str, ',');
        getline(ss, name1, ',');   // not needed
        getline(ss, name2, ',');   // not needed
        getline(ss, time_str, ',');

        // convert strings to ints
        int loc1 = stoi(loc1_str);
        int loc2 = stoi(loc2_str);
        int time = stoi(time_str);

        // add the edge to the graph
        graph.addEdge(loc1, loc2, time);
    }
    edges_file.close();

    // now for classes.csv
    ifstream classes_file(classes_filepath);
    if (!classes_file.is_open()) {
        return false;
    }
    string line2;
    getline(classes_file, line2);
    while (getline(classes_file, line2)) {
        stringstream ss(line2);
        string class_code, location_str, start, end;
        //read 4 vals
        getline(ss, class_code, ',');
        //quotes issue
        class_code = Helpers::trim(class_code);
        getline(ss, location_str, ',');
        location_str = Helpers::trim(location_str);
        getline(ss, start, ',');    //ignore - can be ec later
        getline(ss, end, ',');  //ignore - can be ec later

        //convert the loc from string to int
        int location = stoi(location_str);

        // store in student manager
        studentManager.addClassLocation(class_code, location);


    }
    classes_file.close();
    return true;
}

bool CampusCompass::ParseCommand(const string &command) {
    vector<string> tokens = Helpers::tokenize(command);
    if (tokens.empty()) {
        cout << "unsuccessful" << endl;
        return false;
    }

    string cmd = tokens[0];
    //insert
    if (cmd == "insert") {
        if (tokens.size() < 6) {
            cout << "unsuccessful" << endl;
            return false;
        }
        int n = stoi(tokens[4]);
        if (tokens.size() != 5+n) {
            cout << "unsuccessful" << endl;
            return false;
        }
        handleInsert(tokens);
        return true;
    }
    //remove
    if (cmd == "remove") {
        if (tokens.size() != 2) {
            cout << "unsuccessful" << endl;
            return false;
        }
        handleRemove(tokens);
        return true;
    }
    //drop class
    if (cmd == "dropClass") {
        if (tokens.size() != 3) {
            cout << "unsuccessful" << endl;
            return false;
        }
        handleDropClass(tokens);
        return true;
    }
    //replace class
    if (cmd == "replaceClass") {
        if (tokens.size() != 4) {
            cout << "unsuccessful" << endl;
            return false;
        }
        handleReplaceClass(tokens);
        return true;
    }
    //remove class
    if (cmd == "removeClass") {
        if (tokens.size() != 2) {
            cout << "unsuccessful" << endl;
            return false;
        }
        handleRemoveClass(tokens);
        return true;
    }

    // toggleEdgesClosure
    if (cmd == "toggleEdgesClosure") {
        if (tokens.size() < 4) {
            cout << "unsuccessful" << endl;
            return false;
        }
        handleToggleEdgesClosure(tokens);
        return true;
    }

    // checkEdgeStatus
    if (cmd == "checkEdgeStatus") {
        if (tokens.size() != 3) {
            cout << "unsuccessful" << endl;
            return false;
        }
        handleCheckEdgeStatus(tokens);
        return true;
    }

    // isConnected
    if (cmd == "isConnected") {
        if (tokens.size() != 3) {
            cout << "unsuccessful" << endl;
            return false;
        }
        handleIsConnected(tokens);
        return true;
    }

    // printShortestEdges
    if (cmd == "printShortestEdges") {
        if (tokens.size() != 2) {
            cout << "unsuccessful" << endl;
            return false;
        }
        handlePrintShortestEdges(tokens);
        return true;
    }

    // printStudentZone
    if (cmd == "printStudentZone") {
        if (tokens.size() != 2) {
            cout << "unsuccessful" << endl;
            return false;
        }
        handlePrintStudentZone(tokens);
        return true;
    }

    //unknown command
    cout << "unsuccessful" << endl;
    return false;

}

void CampusCompass::handleInsert(const vector<string> &tokens) {
    // tokens: insert "Name" UFID residence n class1 class2 ...
    string name = Helpers::stripQuotes(tokens[1]);
    string ufid = tokens[2];
    int residence = stoi(tokens[3]);
    int n = stoi(tokens[4]);

    vector<string> classes;
    for (int i = 0; i < n; i++) {
        classes.push_back(tokens[5 + i]);
    }

    bool works = studentManager.insertStudent(name, ufid, residence, classes);
    cout << (works ? "successful" : "unsuccessful") << endl;
}

void CampusCompass::handleRemove(const vector<string> &tokens) {
    // tokens: remove ufid
    string ufid = tokens[1];

    bool works = studentManager.removeStudent(ufid);
    cout << (works ? "successful" : "unsuccessful") << endl;
}

void CampusCompass::handleDropClass(const vector<string> &tokens) {
    // tokens: dropClass ufid classCode
    string ufid = tokens[1];
    string classCode = tokens[2];

    bool works = studentManager.dropClass(ufid, classCode);
    cout << (works ? "successful" : "unsuccessful") << endl;
}

void CampusCompass::handleReplaceClass(const vector<string> &tokens) {
    // tokens: replaceClass ufid oldClass newClass
    string ufid = tokens[1];
    string oldC = tokens[2];
    string newC = tokens[3];

    bool works = studentManager.replaceClass(ufid, oldC, newC);
    cout << (works ? "successful" : "unsuccessful") << endl;
}

void CampusCompass::handleRemoveClass(const vector<string> &tokens) {
    // tokens: removeClass classCode
    string classCode = tokens[1];

    int count = studentManager.removeClassFromAll(classCode);
    cout << count << endl;   // always print the number dropped
}

void CampusCompass::handleToggleEdgesClosure(const vector<string> &tokens) {
    // tokens: toggleEdgesClosure n a b c d ...
    int n = stoi(tokens[1]);

    // every pair of ids is one edge
    int index = 2;
    for (int i = 0; i < n; i++) {
        int a = stoi(tokens[index]);
        int b = stoi(tokens[index + 1]);
        index += 2;

        graph.toggleEdge(a, b);
    }

    cout << "successful" << endl;
}

void CampusCompass::handleCheckEdgeStatus(const vector<string> &tokens) {
    // tokens: checkEdgeStatus a b
    int a = stoi(tokens[1]);
    int b = stoi(tokens[2]);

    string status = graph.getEdgeStatus(a, b);
    cout << status << endl;
}

void CampusCompass::handleIsConnected(const vector<string> &tokens) {
    // tokens: isConnected a b
    int a = stoi(tokens[1]);
    int b = stoi(tokens[2]);

    bool works = graph.isConnected(a, b);
    cout << (works ? "successful" : "unsuccessful") << endl;
}

void CampusCompass::handlePrintShortestEdges(const vector<string> &tokens) {
    // tokens: printShortestEdges ufid
    string ufid = tokens[1];

    Student* s = studentManager.getStudent(ufid);
    if (!s) {
        cout << "unsuccessful" << endl;
        return;
    }

    cout << "Name: " << s->name << endl;

    // classes must be printed in abc order
    vector<string> sortedClasses = s->classes;
    sort(sortedClasses.begin(), sortedClasses.end());

    for (auto &c : sortedClasses) {
        const auto& classLocs = studentManager.getClassLocations();
        int loc = classLocs.at(c);

        int time = graph.shortestPath(s->residence, loc);

        cout << c << " | Total Time: " << time << endl;
    }
}

void CampusCompass::handlePrintStudentZone(const vector<string> &tokens) {
    // tokens: printStudentZone ufid
    string ufid = tokens[1];

    Student* s = studentManager.getStudent(ufid);
    if (!s) {
        cout << "unsuccessful" << endl;
        return;
    }

    // collect all nodes in every shortest path
    unordered_set<int> zoneNodes;
    vector<pair<pair<int,int>,int>> zoneEdges;

    const auto& classLocs = studentManager.getClassLocations();
    const auto& adj = graph.getAdj();

    for (auto &classCode : s->classes) {
        int loc = classLocs.at(classCode);

        vector<int> path = graph.getShortestPathNodes(s->residence, loc);

        // add nodes to set
        for (int node : path) {
            zoneNodes.insert(node);
        }
    }

    // now build edges belonging to this zone
    vector<int> nodeList(zoneNodes.begin(), zoneNodes.end());
    for (int u : nodeList) {
        if (!adj.count(u)) continue;
        for (auto &e : adj.at(u)) {        // requires adj to be public- FIXME
            int v = e.to;
            int w = e.weight;
            if (zoneNodes.count(v) && e.open) {
                zoneEdges.push_back({ {u, v}, w });
            }
        }
    }

    // compute mst cost
    int cost = graph.computeMST(nodeList, zoneEdges);

    cout << "Student Zone Cost For " << s->name << ": " << cost << endl;
}

