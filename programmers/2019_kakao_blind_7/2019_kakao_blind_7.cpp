#include <string>
#include <vector>
#include <map>

using namespace std;

int dx[] = {0, 0, -1, 1};
int dy[] = {1, -1, 0, 0};
vector<vector<int>> visit;

void dfs(
    int x,
    int y,
    vector<vector<int>>& board,
    vector<pair<int, int>>& points) {
    
    int num = board[points[0].first][points[0].second];
    
    visit[x][y] = true;
    
    for (int d = 0; d < 4; d++) {
        int nx = x + dx[d];
        int ny = y + dy[d];
        
        if (nx < 0 || ny < 0 || nx >= board.size() || ny >= board.size()) continue;
        if (visit[nx][ny] || board[nx][ny] != num) continue;
        
        points.push_back({nx, ny});
        dfs(nx, ny, board, points);
    }
}

bool possible(vector<pair<int, int>>& points) {
    int x = points[0].first;
    int y = points[0].second;
    
    if (points[1].first == x && points[1].second == y + 1) return false;
    if (points[2].first == x + 1 && points[2].second == y - 1 &&
        points[3].first == x + 2 && points[3].second == y) return false;
    if (points[2].first == x + 1 && points[2].second == y + 1 &&
        points[3].first == x + 2 && points[3].second == y) return false;
        
    return true;
}

bool is_clear(vector<vector<int>>& board, vector<pair<int, int>>& points) {
    int sx = 0;
    vector<int> ylist;
    
    for (auto e : points) {
        sx = max(sx, e.first);
    }
    
    ylist.push_back(points[3].second);
    
    if (points[1].second != points[2].second) {
        ylist.push_back(points[2].second);
    }
    
    for (int i = sx; i >= 0; i--) {
        for (auto j : ylist) {
            if (board[i][j] != 0 && board[i][j] != board[sx][ylist[0]]) {
                return false;
            }
        }
    }
    
    return true;
}

int solution(vector<vector<int>> board) {
    int answer = 0;
    
    visit.resize(board.size(), vector<int>(board.size(), 0));
    
    for (int i = 0; i < board.size(); i++) {
        for (int j = 0; j < board.size(); j++) {
            if (board[i][j] == 0 || visit[i][j]) continue;
            
            vector<pair<int, int>> points;
            points.push_back({i, j});
            
            dfs(i, j, board, points);
            
            if (!possible(points)) continue;
            if (!is_clear(board, points)) {
                for (auto e : points) {
                    visit[e.first][e.second] = 0;
                }
                continue;
            } 
            
            for (auto e : points) {
                board[e.first][e.second] = 0;
            }
            
            answer++;
            j = -1;
        }
    }
    
    return answer;
}
