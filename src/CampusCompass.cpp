#include "CampusCompass.h"
#include "Graph.h"
#include "StudentManager.h"
#include "Helpers.h"
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

CampusCompass::CampusCompass() {
    // initialize your object

}

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
        getline(ss, location_str, ',');
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
        // must be at least 5 tokens
        if (tokens.size() < 6) {
            cout << "unsuccessful" << endl;
            return false;
        }

        string name = Helpers::stripQuotes(tokens[1]);
        string ufid = tokens[2];
        int residence = stoi(tokens[3]);
        int n = stoi(tokens[4]);

        // ensure exactly n classcodes
        if (tokens.size() != 5 + n) {
            cout << "unsuccessful" << endl;
            return false;
        }

        vector<string> classes;
        for (int i = 0; i < n; i++) {
            classes.push_back(tokens[5 + i]);
        }

        bool works = studentManager.insertStudent(name, ufid, residence, classes);
        cout << (works ? "successful" : "unsuccessful") << endl;
        return works;
    }
    //remove
    if (cmd == "remove") {
        if (tokens.size() != 2) {
            cout << "unsuccessful" << endl;
            return false;
        }

        string ufid = tokens[1];
        bool works = studentManager.removeStudent(ufid);
        cout << (works ? "successful" : "unsuccessful") << endl;
        return works;
    }
    //drop class
    if (cmd == "dropClass") {
        if (tokens.size() != 3) {
            cout << "unsuccessful" << endl;
            return false;
        }

        string ufid = tokens[1];
        string classCode = tokens[2];

        bool works = studentManager.dropClass(ufid, classCode);
        cout << (works ? "successful" : "unsuccessful") << endl;
        return works;
    }
    //replace class
    if (cmd == "replaceClass") {
        if (tokens.size() != 4) {
            cout << "unsuccessful" << endl;
            return false;
        }

        string ufid = tokens[1];
        string oldC = tokens[2];
        string newC = tokens[3];

        bool works = studentManager.replaceClass(ufid, oldC, newC);
        cout << (works ? "successful" : "unsuccessful") << endl;
        return works;
    }
    //remove class
    if (cmd == "removeClass") {
        if (tokens.size() != 2) {
            cout << "unsuccessful" << endl;
            return false;
        }

        string classCode = tokens[1];
        int count = studentManager.removeClassFromAll(classCode);
        cout << count << endl;
        return true;
    }

    //unknown command
    cout << "unsuccessful" << endl;
    return false;

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

