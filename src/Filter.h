//
// Created by desvl on 8/7/18.
//

#include <map>
#include <vector>
#include <fstream>
#include <algorithm>

#ifndef FILTER_FILTER_H
#define FILTER_FILTER_H

std::map<std::string,int>split(std::string line){ // Split the line into several words.
    std::string tmp_word;
    line.push_back('.');
    // Why add a '.' at the end of the line?
    // If the last word is dirty, and there is no punctuation afterwards,
    // then the last word won't be filtered.
    // On the other hand, this '.' won't be added into anywhere. (See line 20)
    std::map<std::string,int> result;
    for (unsigned i = 0; i < line.length(); i++) {
        if ((line[i] >= 97 && line[i] <= 122) || (line[i] >= 48 && line[i] <= 57) || (line[i] >= 65 && line[i] <= 90) ||
            line[i] == 45 || line[i] == 39) {
            tmp_word.push_back(line[i]); // If the i_th character of line is number/letter/'-'/"'", then make it a word.
        } else {
            if (!tmp_word.empty())
                // A useless character encountered. If a word has been built, then add the word to the map.
                result.insert(std::pair<std::string, int>(tmp_word, static_cast<const int &>(i - tmp_word.length())));
                // pair.right is the beginning position of each word.
            tmp_word.clear(); // Prepared for a new word.
        }
    }
    return result;
}

bool isDirty(const std::pair<std::string,int> &words){
    std::string str = words.first;
    std::string dir = "src/Dirty_Libraries/en/";
    std::string word;
    std::transform(str.begin(), str.end(), str.begin(), ::tolower);
    // All the dirty words stored in library are lowercase, so transform words inputted into lowercase first of all.
    if (str[0] >= 'a' && str[0] <= 'z') {
        dir.push_back(str[0]); // Words will be checked in the respective file with same first letter.
        std::ifstream iFile;
        iFile.open(dir);
        while (iFile) {
            getline(iFile, word);
            if (word == str) {
                return true; // Once found, the word to be checked is dirty confirmed. return true to terminate.
            }
        }
    }
    return false;
}

bool dirtyList(std::map<std::string,int> &words){
    for (const auto &pair : words) {
        if (!isDirty(pair)) {
            words.erase(pair.first); // If the words is not dirty, remove it.
        }
    }
    //Only dirty words remain. If the list is empty, then there is no dirty word in the line.
    return !words.empty();
}

void filter(const std::map<std::string,int> &words,std::string &line){
    for (const auto &pair:words) {
        // pair.second is the position of each words. Since all the words remaining is dirty,
        // we transform them into asterisks one by one.
        for (auto i = pair.second; i < pair.second + pair.first.length(); i++) {
            line[i] = '*';
        }
    }
}
bool isPureUpper(const std::map<std::string,int> &words){
    for(const auto &pair : words){
        for(const auto &i : pair.first){
            if(!(isupper(i) || i == 39 || i == 45)) // If any character is not uppercase/'''/'-', return false.
                return false;
        }
    }
    return true;
}
#endif //FILTER_FILTER_H
