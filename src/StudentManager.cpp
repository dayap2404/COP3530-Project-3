#include "StudentManager.h"
#include <iostream>
using namespace std;

//FIXME - literally everything, this is just skeleton


// consturctor
StudentManager::StudentManager() {}

// loading csv
void StudentManager::loadClassesCSV(const string &filename) {
}

// validation helpers
bool StudentManager::validateName(const string &name) const {
    return true;
}

bool StudentManager::validateUFID(const string &ufid) const {
    return true;
}

bool StudentManager::validateClassCode(const string &code) const {
    return true;
}

// adding a student
bool StudentManager::insertStudent(const string &name, const string &ufid, int residence, const vector<string> &classes) {
    return true;
}

// deleting a student
bool StudentManager::removeStudent(const string &ufid) {
    return true;
}

//deleting a class
bool StudentManager::dropClass(const string &ufid, const string &classCode) {
    return true;
}

//replacing a class
bool StudentManager::replaceClass(const string &ufid, const string &oldClass, const string &newClass) {
    return true;
}

// removing a class from every student
int StudentManager::removeClassFromAll(const string &classCode) {
    return 1;
}

// ptr to student
Student* StudentManager::getStudent(const string &ufid) {
    return nullptr;
}







