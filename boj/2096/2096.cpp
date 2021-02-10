#include <iostream>
#include <vector>

using namespace std;

int n;
int in[3];
int max_dp[2][3];
int min_dp[2][3];

int main()
{
    cin >> n;

    cin >> in[0] >> in[1] >> in[2];

    for (int i = 0; i < 3; i++) {
        max_dp[0][i] = in[i];
        min_dp[0][i] = in[i];
    }

    for (int i = 1; i < n; i++) {
        cin >> in[0] >> in[1] >> in[2];

        int cur = i % 2;
        int pre = (i - 1) % 2;

        min_dp[cur][0] = in[0] + min(min_dp[pre][0], min_dp[pre][1]);
        min_dp[cur][1] = in[1] + min(min_dp[pre][0], min(min_dp[pre][1], min_dp[pre][2]));
        min_dp[cur][2] = in[2] + min(min_dp[pre][1], min_dp[pre][2]);
        max_dp[cur][0] = in[0] + max(max_dp[pre][0], max_dp[pre][1]);
        max_dp[cur][1] = in[1] + max(max_dp[pre][0], max(max_dp[pre][1], max_dp[pre][2]));
        max_dp[cur][2] = in[2] + max(max_dp[pre][1], max_dp[pre][2]);
    }

    int idx = (n - 1) % 2;
    int ans1 = max(max_dp[idx][0], max(max_dp[idx][1], max_dp[idx][2]));
    int ans2 = min(min_dp[idx][0], min(min_dp[idx][1], min_dp[idx][2]));

    cout << ans1 << ' ' << ans2 << '\n';

    return 0;
}
