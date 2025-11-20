#pragma once
#include "Graph.h"
#include "Student.h"
#include "StudentManager.h"
#include <string>

using namespace std;

class CampusCompass {
private:
    // Think about what member variables you need to initialize
    // perhaps some graph representation?
    //graph object
    Graph graph;
    StudentManager student;

public:
    // Think about what helper functions you will need in the algorithm
    CampusCompass(); // constructor

    bool ParseCSV(const string &edges_filepath, const string &classes_filepath);

    bool ParseCommand(const string &command);

    void handleInsert(const vector<string> &tokens);

    void handleRemove(const vector<string> &token);

    void handleDropClass(const vector<string> &token);

    void handleReplaceClass(const vector<string> &token);

    void handleRemoveClass(const vector<string> &token);

    void handleToggleEdgesClosure(const vector<string> &token);

    void handleCheckEdgeStatus(const vector<string> &token);

    void handleIsConnected(const vector<string> &token);

    void handlePrintShortestEdges(const vector<string> &token);

    void handlePrintStudentZone(const vector<string> &token);

};
