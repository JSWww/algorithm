#include <iostream>
#include <string>
#include <vector>

using namespace std;

int dp[1001];

int main()
{
    int n;
    vector<int> v;

    cin >> n;

    v.resize(n);

    for (int i = 0; i < n; i++) {
        cin >> v[i];
        dp[i] = 1;
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < i; j++) {
            if (v[i] > v[j]) {
                dp[i] = max(dp[i], dp[j] + 1);
            } 
        }
    }

    int ans = -1;

    for (int i = 0; i < n; i++) {
        if (ans < dp[i]) {
            ans = dp[i];
        }
    }

    cout << ans << '\n';

    return 0;
}
