#ifndef HELPERS_H
#define HELPERS_H
#include <string>
#include <vector>
using namespace std;

// helpers for command parsing
namespace Helpers {

    // breaks apart the string into separate peices - got this idea from geeksforgeeks
    vector<string> tokenize(const string& line);

    // removes spaces from the front and back of a string
    string trim(const string& s);

    // removes surrounding quotes from a string
    string stripQuotes(const string& s);

}

#endif

//https://www.geeksforgeeks.org/cpp/tokenizing-a-string-cpp/