#include <iostream>
#include "src/Filter.h"

using namespace std;

int main() {
    cout << "Enter words to filter. Press Q to stop..." << endl;
    string line;
    map<string,int> words;
    while (getline(cin, line)) {
        if (line == "Q") {
            break;
        }
        words = split(line);
        if (dirtyList(words)) { // Once dirty words inside, do the filter; if not, print the original line.
            filter(words, line);
        }
        cout << line << endl;
    }
    return 0;
}
