
#include "TimeCode.h"

#include <iostream>
#include <fstream> //file stream 
#include <vector>
#include <string>

using namespace std;

vector<string> split(const string& s, char delim) { 
    // ampersand to avoid copying a potentially large string
    vector<string> pieces;
    string current;

    for (char c : s) {
        if (c == delim) {
            pieces.push_back(current);
            current.clear();
            // https://www.geeksforgeeks.org/cpp/stdstringclear-in-cpp/
        } 
        
        else {
            current += c;
        }
    }

    pieces.push_back(current);
    // The loop only saves a piece when it hits a delimiter. 
    // So the very last piece never gets saved by the loop. 
    // That's why we have to add it here.

    return pieces;
}

// This works if the line actually has a time in it.
// So we have to check that in main function.
TimeCode parse_line(const string& line) {
    vector<string> parts = split(line, '"');
    string datum = parts[1];

    vector<string> words = split(datum, ' ');
    string timeS = words[words.size() - 2];

    vector<string> hm = split(timeS, ':');
    int hr = stoi(hm[0]);
    int min = stoi(hm[1]);

    return TimeCode(hr, min, 0);
}


int main() {
    ifstream file("Space_Corrected.csv");

    if (!file.is_open()) {
        // https://www.geeksforgeeks.org/cpp/std-ifstream-isopen-in-cpp/
        cout << "Failed to open file." << endl;
        return 1;
    }

    string line;
    getline(file, line);
    vector<TimeCode> times;

    while (getline(file, line)) {
        // Some rows only have a day, no exact time.
        // We are ignoring those per the assignment.
        // UTC only ever appears inside the quoted Datum field on a line that actually has a time.

        if (line.find("UTC") != string::npos) {
            // https://www.geeksforgeeks.org/cpp/stringnpos-in-c-with-examples/
            times.push_back(parse_line(line));
            //
        }
    }

    TimeCode sum;

    for (const TimeCode& t : times) {
        sum = sum + t;
    }

    TimeCode average = sum / static_cast<double>(times.size());
    // times.size() returns size_t. That's why I did casting here.

    cout << times.size() << " data points." << endl;
    cout << "AVERAGE: " << average.ToString() << endl;

    return 0;
}


// I read the notes in the assignment instructions :)