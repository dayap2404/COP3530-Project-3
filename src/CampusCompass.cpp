#include "CampusCompass.h"
#include "Graph.h"
#include "StudentManager.h"
#include "Helpers.h"
#include <string>

using namespace std;

CampusCompass::CampusCompass() {
    // initialize your object
}

bool CampusCompass::ParseCSV(const string &edges_filepath, const string &classes_filepath) {
    // return boolean based on whether parsing was successful or not

    // going to read edges.csv
    // build the graph by calling Graph.addEdge
    // read classes.csv
    // send class to location data into student manager
    return true;
}

bool CampusCompass::ParseCommand(const string &command) {
    // do whatever regex you need to parse validity
    // hint: return a boolean for validation when testing. For example:
    bool is_valid = true; // replace with your actual validity checking

    //tokenize w helpers::tokenize
    // trim tokens
    // identify what command it is
    // call the correct function
    // return true or false for validation if it works

    return is_valid;
}

void CampusCompass::handleInsert(const vector<string> &tokens) {
    //fixme
}

void CampusCompass::handleRemove(const vector<string> &token) {
    //fixme
}

void CampusCompass::handleDropClass(const vector<string> &token) {
    //fixme
}

void CampusCompass::handleReplaceClass(const vector<string> &token) {
    //fixme
}

void CampusCompass::handleRemoveClass(const vector<string> &token) {
    //fixme
}

void CampusCompass::handleToggleEdgesClosure(const vector<string> &token) {
    //fixme
}

void CampusCompass::handleCheckEdgeStatus(const vector<string> &token) {
    //fixme
}

void CampusCompass::handleIsConnected(const vector<string> &token) {
    //fixme
}

void CampusCompass::handlePrintShortestEdges(const vector<string> &token) {
    //fixme
}

void CampusCompass::handlePrintStudentZone(const vector<string> &token) {
    //fixme
}

