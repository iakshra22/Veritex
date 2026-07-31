#ifndef TRIE_H
#define TRIE_H

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class TrieNode {
public:
    TrieNode* children[26];
    bool isEndOfWord;
    int frequency;

    TrieNode() {
        isEndOfWord = false;
        frequency = 0;
        for (int i = 0; i < 26; i++) {
            children[i] = nullptr;
        }
    }
};

class DictionaryTrie {
private:
    TrieNode* root;

    // Helper DFS for Prefix Auto-Complete
    void dfsAutocomplete(TrieNode* curr, string currentPrefix, vector<string>& results) {
        if (!curr || results.size() >= 5) return;

        if (curr->isEndOfWord) {
            results.push_back(currentPrefix);
        }

        for (int i = 0; i < 26; i++) {
            if (curr->children[i]) {
                char ch = 'a' + i;
                dfsAutocomplete(curr->children[i], currentPrefix + ch, results);
            }
        }
    }

public:
    DictionaryTrie() {
        root = new TrieNode();
    }

    void insert(const string& word, int freq = 1) {
        TrieNode* curr = root;
        for (char ch : word) {
            int index = tolower(ch) - 'a';
            if (index < 0 || index >= 26) continue;
            if (curr->children[index] == nullptr) {
                curr->children[index] = new TrieNode();
            }
            curr = curr->children[index];
        }
        curr->isEndOfWord = true;
        curr->frequency = freq;
    }

    bool search(const string& word) const {
        TrieNode* curr = root;
        for (char ch : word) {
            int index = tolower(ch) - 'a';
            if (index < 0 || index >= 26) return false;
            if (curr->children[index] == nullptr) return false;
            curr = curr->children[index];
        }
        return curr->isEndOfWord;
    }

    // Prefix Auto-Complete using DFS Recursion
    vector<string> getPrefixCompletions(const string& prefix) {
        vector<string> results;
        TrieNode* curr = root;

        for (char ch : prefix) {
            int index = tolower(ch) - 'a';
            if (index < 0 || index >= 26 || curr->children[index] == nullptr) {
                return results;
            }
            curr = curr->children[index];
        }

        dfsAutocomplete(curr, prefix, results);
        return results;
    }
};

#endif