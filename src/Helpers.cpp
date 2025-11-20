#include "Helpers.h"
#include <sstream>
using namespace std;

vector<string> Helpers::tokenize(const string& line) {
    vector<string> tokens;
    string current;
    bool insideQuotes = false;

    for (char c : line) {
        if (c == '"') {
            // whether we are inside quotes
            insideQuotes = !insideQuotes;
            current += c;
        }
        else if (c == ' ' && !insideQuotes) {
            // space outside quotes so split
            if (!current.empty()) {
                tokens.push_back(current);
                current.clear();
            }
        }
        else {
            // normal char so we add it
            current += c;
        }
    }

    // add last bit
    if (!current.empty()) {
        tokens.push_back(current);
    }

    return tokens;
}

// removes leading and trailing spaces
string Helpers::trim(const string& s) {
    int start = 0;
    int end = s.length() - 1;

    while (start <= end && s[start] == ' ') start++;
    while (end >= start && s[end] == ' ') end--;

    return s.substr(start, end - start + 1);
}

// removes surrounding quotes if they exist
string Helpers::stripQuotes(const string& s) {
    if (s.length() >= 2 && s[0] == '"' && s[s.length() - 1] == '"') {
        return s.substr(1, s.length() - 2);
    }
    return s;
}

