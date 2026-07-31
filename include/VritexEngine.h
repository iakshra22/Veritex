#ifndef VRITEX_ENGINE_H
#define VRITEX_ENGINE_H

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include <unordered_map>

#include "Trie.h"
#include "EditDistance.h"
#include "Phonetic.h"

using namespace std;

struct WordMetadata {
    string word;
    int frequency;
    string soundexCode;
};

struct Suggestion {
    string word;
    int editDistance;
    int frequency;
    bool phoneticMatch;
};

// Ranking Comparator (Edit Distance > Phonetic > Frequency)
inline bool compareSuggestions(const Suggestion& a, const Suggestion& b) {
    if (a.editDistance != b.editDistance)
        return a.editDistance < b.editDistance;
    if (a.phoneticMatch != b.phoneticMatch)
        return a.phoneticMatch > b.phoneticMatch; 
    return a.frequency > b.frequency;
}

class VritexEngine {
private:
    DictionaryTrie dictionary;
    vector<WordMetadata> wordDataset;
    unordered_map<string, vector<string>> bigramGraph;

    int totalWordsChecked = 0;
    int correctWordsCount = 0;

public:
    bool loadDataset(const string& filepath) {
        ifstream file(filepath);
        if (!file.is_open()) return false;

        string word;
        int freq;
        while (file >> word >> freq) {
            dictionary.insert(word, freq);
            wordDataset.push_back({word, freq, getSoundexCode(word)});
        }
        file.close();

        bigramGraph["going"] = {"to", "there", "home"};
        bigramGraph["too"] = {"much", "late", "fast"};

        return true;
    }

    void addToUserDictionary(const string& newWord, const string& userDictPath = "data/user_dict.txt") {
        dictionary.insert(newWord, 100);
        wordDataset.push_back({newWord, 100, getSoundexCode(newWord)});

        ofstream file(userDictPath, ios::app);
        if (file.is_open()) {
            file << newWord << " 100\n";
            file.close();
        }
    }

    bool isValidWord(const string& word) const {
        return dictionary.search(word);
    }

    vector<string> autoComplete(const string& prefix) {
        return dictionary.getPrefixCompletions(prefix);
    }

    string getContextCorrection(const string& prevWord, const string& currWord) {
        if (bigramGraph.find(prevWord) != bigramGraph.end()) {
            for (const string& nextWord : bigramGraph[prevWord]) {
                if (calculateEditDistance(currWord, nextWord) <= 1) {
                    return nextWord;
                }
            }
        }
        return "";
    }

    vector<string> getSuggestions(const string& wrongWord, int limit = 3) {
        vector<Suggestion> candidates;
        string inputSoundex = getSoundexCode(wrongWord);

        for (const auto& item : wordDataset) {
            if (abs((int)item.word.length() - (int)wrongWord.length()) > 3) continue;

            int dist = calculateEditDistance(wrongWord, item.word);
            bool isPhonetic = (inputSoundex == item.soundexCode);

            candidates.push_back({item.word, dist, item.frequency, isPhonetic});
        }

        sort(candidates.begin(), candidates.end(), compareSuggestions);

        vector<string> topSuggestions;
        for (int i = 0; i < min((int)candidates.size(), limit); i++) {
            topSuggestions.push_back(candidates[i].word);
        }
        return topSuggestions;
    }

    void recordCheck(bool isCorrect) {
        totalWordsChecked++;
        if (isCorrect) correctWordsCount++;
    }

    double getAccuracyPercentage() const {
        if (totalWordsChecked == 0) return 100.0;
        return ((double)correctWordsCount / totalWordsChecked) * 100.0;
    }

    int getTotalWordsChecked() const { return totalWordsChecked; }
    size_t getDatasetSize() const { return wordDataset.size(); }
};

#endif