#include <string>
#include <vector>

using namespace std;

int dp[300001][2];
vector<vector<int>> tree;

void dfs(vector<int>& sales, int v) {
    if (tree[v].size() == 0) {
        dp[v][1] = sales[v-1];
        return;
    }
    
    int minval = 1e9;
    dp[v][1] = sales[v-1];
    
    for (auto e : tree[v]) {
        dfs(sales, e);
        
        dp[v][1] += min(dp[e][0], dp[e][1]);
        minval = min(minval, dp[e][1] - dp[e][0]);
    }
    
    dp[v][0] = max(0, minval) + dp[v][1] - sales[v-1];
}

int solution(vector<int> sales, vector<vector<int>> links) {
    int answer = 0;
    
    tree.reserve(sales.size() + 1);
    
    for (auto e : links) {
        tree[e[0]].push_back(e[1]);
    }
    
    dfs(sales, 1);
    
    answer = min(dp[1][0], dp[1][1]);
    
    return answer;
}