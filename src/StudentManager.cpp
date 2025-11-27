#include "StudentManager.h"
#include <iostream>
#include <cctype>
using namespace std;


// consturctor
StudentManager::StudentManager() {}


// validation helpers
bool StudentManager::validateName(const string &name) const {
    //must be at least 1 char
    if (name.size() < 1) {
        return false;
    }
    //at least one letter
    bool letter = false;

    //must be letter or space
    for (char c : name) {
        if (!isalpha(c) && c != ' ') {
            return false;
        }
        if (isalpha(c)) {
            letter = true;
        }
    }
    if (!letter) {
        return false;
    }
    return true;
}

bool StudentManager::validateUFID(const string &ufid) const {
    //must be exactly 8 chars
    if (ufid.size() != 8 ) {
        return false;
    }

    //must be all numbers
    for (char c : ufid) {
        if (!isdigit(c)) {
            return false;
        }
    }

    return true;
}

bool StudentManager::validateClassCode(const string &code) const {
    //must match pattern of first 3 chars upper case letter
    //and last 4 are numbers
    //so must be exactly 7 chars long
    if (code.size() != 7) {
        return false;
    }
    for (int i=0; i < 7; i++) {
        if (i < 3) {
            if (!isupper(code[i])) {
                return false;
            }
        }
        else if (i >= 3) {
            if (!isdigit(code[i])) {
                return false;
            }
        }
    }
    return true;
}

// adding a student
bool StudentManager::insertStudent(const string &name, const string &ufid, int residence, const vector<string> &classes) {
    //validate name
    if (!validateName(name)) {
        return false;
    }
    //validate id + uniqueness (isnt already in here)
    if (!validateUFID(ufid) || getStudent(ufid) != nullptr) {
        return false;
    }
    //validate classes
    if (classes.size() > 6 || classes.size() < 1) {
        return false;
    }
    for (int i=0; i < classes.size(); i++) {
        if (!validateClassCode(classes[i])) {
            return false;
        }
        //class existence in class locations
        if (!classLocations.count(classes[i])) {
            return false;
        }
    }

    //create student
    Student student = Student(name, ufid, residence, classes);
    students[ufid] = student;

    return true;
}

// deleting a student
bool StudentManager::removeStudent(const string &ufid) {
    //check if student exists
    if (!students.count(ufid)) {
        return false;
    }
    //delete
    students.erase(ufid);
    return true;
}

//deleting a class
bool StudentManager::dropClass(const string &ufid, const string &classCode) {
    //check if student exists
    if (!students.count(ufid)) {
        return false;
    }
    //check if class exists
    if (!classLocations.count(classCode)) {
        return false;
    }

    //check if student takes this class
    bool enrolled = false;
    Student &student = students[ufid];
    for (const string &c : student.classes) {
        if (c == classCode) {
            enrolled = true;
            break;
        }
    }
    if (!enrolled) {
        return false;
    }
    //drop class
    for (int i=0; i < student.classes.size(); i++) {
        if (student.classes[i] == classCode) {
            student.classes.erase(student.classes.begin() + i);
            break;
        }
    }

    //remove student if now they have no classes
    if (student.classes.empty()) {
        students.erase(ufid);
    }


    return true;
}

//replacing a class
bool StudentManager::replaceClass(const string &ufid, const string &oldClass, const string &newClass) {
    //check if student exists
    Student &student = students[ufid];

    if (!students.count(ufid)) {
        return false;
    }


    //validate the codes

    if (!validateClassCode(oldClass)) return false;
    if (!validateClassCode(newClass)) return false;

    //check if classes exists
    if (!classLocations.count(oldClass) || !classLocations.count(newClass)) {
        return false;
    }

    //check if student takes this class
    bool enrolled = false;

    for (const string &c : student.classes) {
        if (c == oldClass) {
            enrolled = true;
            break;
        }
    }
    if (!enrolled) {
        return false;
    }

    bool enrolled_new = false;
    for (const string &c : student.classes) {
        if (c == newClass) {
            enrolled_new = true;
            break;
        }
    }
    if (enrolled_new) {
        return false;
    }


    //replace class
    for (int i=0; i < student.classes.size(); i++) {
        if (student.classes[i] == oldClass) {
            student.classes[i] = newClass;
            break;
        }
    }



    return true;
}

// removing a class from every student
int StudentManager::removeClassFromAll(const string &classCode) {
    //this does not delete from class locations only from studnt schedules
    if (!classLocations.count(classCode)) {
        return 0;
    }
    //loop thru students
    int count = 0;
    vector<string> toDelete;

    for (auto &pair : students) {
        //drop class
        for (int i=0; i < pair.second.classes.size(); i++) {
            if (pair.second.classes[i] == classCode) {
                pair.second.classes.erase(pair.second.classes.begin() + i);
                //if student is now empty add to vector
                if (pair.second.classes.empty()) {
                    toDelete.push_back(pair.first);
                }
                count++;
                break;
            }
        }
    }
    //delete all students in to delete
    for (int i=0; i < toDelete.size(); i++) {
        students.erase(toDelete[i]);
    }
    return count;

}

// ptr to student
Student* StudentManager::getStudent(const string &ufid) {
    // if no student with this UFID exists, return nullptr
    if (!students.count(ufid)) {
        return nullptr;
    }

    // return a pointer to the Student stored in the map
    return &students[ufid];
}

void StudentManager::addClassLocation(const string &classCode, int locationID) {
    classLocations[classCode] = locationID;
}









