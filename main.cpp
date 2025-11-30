#include <bits/stdc++.h>
using namespace std;

/*
 Minimum Path Sum (grid) - Dynamic Programming
 Problem: Given an m x n grid of non-negative integers, find a path from top-left
 to bottom-right which minimizes the sum of all numbers along its path.
 You can only move either down or right at any point.

 Two implementations provided:
 1) minPathSumDP    : O(m*n) time, O(m*n) space
 2) minPathSumOpt   : O(m*n) time, O(n) space (space-optimized)

 Input format (stdin):
  r c
  then r lines each with c non-negative integers (space separated)

 Output:
  single integer = minimum path sum
*/

int minPathSumDP(const vector<vector<int>>& grid) {
    int r = grid.size();
    int c = grid[0].size();
    vector<vector<long long>> dp(r, vector<long long>(c, LLONG_MAX));
    dp[0][0] = grid[0][0];

    for (int i = 0; i < r; ++i) {
        for (int j = 0; j < c; ++j) {
            if (i > 0) dp[i][j] = min(dp[i][j], dp[i-1][j] + grid[i][j]);
            if (j > 0) dp[i][j] = min(dp[i][j], dp[i][j-1] + grid[i][j]);
        }
    }
    return static_cast<int>(dp[r-1][c-1]);
}

int minPathSumOpt(const vector<vector<int>>& grid) {
    int r = grid.size();
    int c = grid[0].size();
    vector<long long> dp(c, LLONG_MAX);
    dp[0] = grid[0][0];

    // first row initialization
    for (int j = 1; j < c; ++j) dp[j] = dp[j-1] + grid[0][j];

    for (int i = 1; i < r; ++i) {
        // update dp[0] for current row (only from top)
        dp[0] = dp[0] + grid[i][0];
        for (int j = 1; j < c; ++j) {
            dp[j] = min(dp[j], dp[j-1]) + grid[i][j];
        }
    }
    return static_cast<int>(dp[c-1]);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int r, c;
    if (!(cin >> r >> c)) return 0;
    vector<vector<int>> grid(r, vector<int>(c));
    for (int i = 0; i < r; ++i)
        for (int j = 0; j < c; ++j)
            cin >> grid[i][j];

    // choose the optimized version
    cout << minPathSumOpt(grid) << '\n';
    return 0;
}
