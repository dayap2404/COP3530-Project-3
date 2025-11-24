#ifndef STUDENT_H
#define STUDENT_H
#include <string>
#include <vector>
using namespace std;

// stores a students basic info and what classes theyre taking
class Student {
public:
    string name;
    string ufid;
    int residence;             // location ID of where they live on campus
    vector<string> classes;    // list of class codes they are enrolled in

    // default constructor
    Student();

    //constructor
    Student(const string& name, const string& ufid, int residence, const vector<string>& classes);


};

#endif
