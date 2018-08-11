#include <iostream>
#include "src/Filter.h"

using namespace std;

int main() {
    cout << "Press Q to stop..." << endl;
    string line;
    map<string,int> words;
    while (getline(cin, line)) {
        if (line == "Q") {
            break;
        }
        words = split(line);
        if (isPureUpper(words) || dirtyList(words)) { // Once dirty words inside, or all the words are uppercase, do the filter; if not, print the original line.
            filter(words, line);
        }
        cout << line << endl;
    }
    return 0;
}
