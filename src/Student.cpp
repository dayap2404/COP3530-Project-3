#include "Student.h"
using namespace std;

Student::Student() {}

// constructor
Student::Student(const string& name, const string& ufid, int residence, const vector<string>& classes) {
    this->name = name;
    this->ufid = ufid;
    this->residence = residence;
    this->classes = classes;

}


