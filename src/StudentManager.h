#ifndef STUDENT_MANAGER_H
#define STUDENT_MANAGER_H
#include <unordered_map>
#include <string>
#include <vector>
#include "Student.h"
using namespace std;

// keep track of all the students
class StudentManager {
private:
    unordered_map<string, Student> students;
    // key is class cofe
    // value is location id
    unordered_map<string, int> classLocations;

public:
    StudentManager();

    // validation helpers
    bool validateName(const string& name) const;       // names can only have letters/spaces
    bool validateUFID(const string& ufid) const;       // UFIDs must be exactly 8 digits
    bool validateClassCode(const string& code) const;  // must be 3 uppercase letters + 4 digits

    // add a student into the system
    bool insertStudent(const string& name, const string& ufid, int residence, const vector<string>& classes);

    // delete student using ufid
    bool removeStudent(const string& ufid);

    // delete a class from a student using id
    bool dropClass(const string& ufid, const string& classCode);

    // replace class
    bool replaceClass(const string& ufid, const string& oldClass, const string& newClass);

    // removes a class from every student and returns how many students had it
    int removeClassFromAll(const string& classCode);

    // pointer to student
    Student* getStudent(const string& ufid);

    void addClassLocation(const string &classCode, int locationID);

    //getter

    const unordered_map<string,int>& getClassLocations() const {
        return classLocations;
    }

};

#endif
