#include <iostream>
#include <vector>

using namespace std;

int matrixMultiplication(vector<int> &arr) {
    int n = arr.size();
    vector<vector<int>> dp(n, vector<int>(n, 0));

    for (int len = 2; len < n; len++) {
        for (int i = 0; i < n - len; i++) {
            int j = i + len;
            dp[i][j] = INT_MAX;

            for (int k = i + 1; k < j; k++) {
                int cost = dp[i][k] + dp[k][j] + arr[i] * arr[k] * arr[j];
                dp[i][j] = min(dp[i][j], cost);
            }
        }
    }

    return dp[0][n - 1];
}

int main() {
    int n;
    cout << "Enter the number of matrices: ";
    cin >> n;

    vector<int> arr(n + 1);
    cout << "Enter the " << n + 1 << " dimensions of matrices: ";
    
    for (int i = 0; i <= n; i++) {
        cin >> arr[i];
    }

    cout << "Minimum cost of matrix multiplication: " << matrixMultiplication(arr) << endl;
    return 0;
}
