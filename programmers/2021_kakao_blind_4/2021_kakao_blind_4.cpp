#include <string>
#include <vector>

using namespace std;

int solution(int n, int s, int a, int b, vector<vector<int>> fares) {
    int answer = 1e9;
    int graph[n+1][n+1];
    
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (i == j) graph[i][j] = 0;
            else graph[i][j] = 1e6;
        }
    }
    
    for (auto e : fares) {
        graph[e[0]][e[1]] = e[2];
        graph[e[1]][e[0]] = e[2];
    }
    
    for (int k = 1; k <= n; k++) {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                if (graph[i][j] > graph[i][k] + graph[k][j]) {
                    graph[i][j] = graph[i][k] + graph[k][j];
                }
            }
        }
    }
    
    for (int i = 1; i <= n; i++) {
        int dist = graph[s][i] + graph[i][a] + graph[i][b];
        answer = min(answer, dist);
    }
    
    return answer;
}