#ifndef EDIT_DISTANCE_H
#define EDIT_DISTANCE_H

#include <string>
#include <vector>
#include <algorithm>

using namespace std;

// Calculates minimum edit operations (Insert, Delete, Replace)
inline int calculateEditDistance(const string& s1, const string& s2) {
    int m = s1.length();
    int n = s2.length();
    
    vector<vector<int>> dp(m + 1, vector<int>(n + 1));

    for (int i = 0; i <= m; i++) dp[i][0] = i;
    for (int j = 0; j <= n; j++) dp[0][j] = j;

    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (tolower(s1[i - 1]) == tolower(s2[j - 1])) {
                dp[i][j] = dp[i - 1][j - 1];
            } else {
                dp[i][j] = 1 + min({
                    dp[i - 1][j],    // Deletion
                    dp[i][j - 1],    // Insertion
                    dp[i - 1][j - 1] // Substitution
                });
            }
        }
    }
    return dp[m][n];
}

#endif