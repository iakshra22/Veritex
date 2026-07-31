#ifndef PHONETIC_H
#define PHONETIC_H

#include <string>
#include <cctype>

using namespace std;

// Soundex Algorithm implementation
inline string getSoundexCode(const string& word) {
    if (word.empty()) return "";

    string code = "";
    code += toupper(word[0]);

    auto getDigit = [](char ch) -> char {
        ch = toupper(ch);
        switch (ch) {
            case 'B': case 'F': case 'P': case 'V': return '1';
            case 'C': case 'G': case 'J': case 'K': case 'Q': case 'S': case 'X': case 'Z': return '2';
            case 'D': case 'T': return '3';
            case 'L': return '4';
            case 'M': case 'N': return '5';
            case 'R': return '6';
            default: return '0';
        }
    };

    char lastDigit = getDigit(word[0]);

    for (size_t i = 1; i < word.length() && code.length() < 4; i++) {
        char currentDigit = getDigit(word[i]);
        if (currentDigit != '0' && currentDigit != lastDigit) {
            code += currentDigit;
            lastDigit = currentDigit;
        } else if (currentDigit == '0') {
            lastDigit = '0';
        }
    }

    while (code.length() < 4) {
        code += '0';
    }

    return code;
}

#endif