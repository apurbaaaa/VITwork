#include <iostream>
#include <vector>
using namespace std;

int lcs(string &s1, string &s2, int m, int n, vector<vector<int>> &memo) {


    if (m == 0 || n == 0)
        return 0;

    if (memo[m][n] != -1)
        return memo[m][n];


    if (s1[m - 1] == s2[n - 1])
        return memo[m][n] = 1 + lcs(s1, s2, m - 1, n - 1, memo);

    return memo[m][n] = max(lcs(s1, s2, m, n - 1, memo), lcs(s1, s2, m - 1, n, memo));
}

int main() {
    string s1;
	string s2;

	cout<< "Enter first string: ";
	cin>>s1;
	cout<< "\nEnter second string: ";
	cin>>s2;
	cout<<"\n";
    int m = s1.length();
    int n = s2.length();
    vector<vector<int>> memo(m + 1, vector<int>(n + 1, -1));
    cout << lcs(s1, s2, m, n, memo) << endl;
    return 0;
}
