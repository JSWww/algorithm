#include <string>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

int dx[] = {-1, 1, 0, 0};
int dy[] = {0, 0, -1, 1};

vector<vector<int>> board(4, vector<int>(4));
vector<pair<int, int>> point[7];
vector<int> card;
int minval = 1e9;

int bfs(vector<vector<int>> b, int sx, int sy, int ex, int ey) {
    queue<pair<int, int>> q;
    int dist[4][4];
    int cnt = 0;
    
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            dist[i][j] = 1e9;
        }
    }
        
    q.push({sx, sy});
    dist[sx][sy] = 0;
        
    while (!q.empty()) {
        int x = q.front().first;
        int y = q.front().second;

        q.pop();

        for (int d = 0; d < 4; d++) {
            if (dx[d]) {
                int nx = x;

                while (1) {
                    if (nx + dx[d] < 0 || nx + dx[d] > 3) break;
                    nx += dx[d];         
                    if (b[nx][y]) break;
                }

                if (dist[x][y] + 1 < dist[nx][y]) {
                    q.push({nx, y});
                    dist[nx][y] = dist[x][y] + 1;
                }
            } else {
                int ny = y;

                while (1) {
                    if (ny + dy[d] < 0 || ny + dy[d] > 3) break;
                    ny += dy[d];         
                    if (b[x][ny]) break;
                }
                
                if (dist[x][y] + 1 < dist[x][ny]) {
                    q.push({x, ny});
                    dist[x][ny] = dist[x][y] + 1;
                }
            }
        }

        for (int d = 0; d < 4; d++) {
            int nx = x + dx[d];
            int ny = y + dy[d];

            if (nx < 0 || ny < 0 || nx >= 4 || ny >= 4) {
                continue;
            }

            if (dist[x][y] + 1 < dist[nx][ny]) {
                q.push({nx, ny});
                dist[nx][ny] = dist[x][y] + 1;
            }
        }
    }
    
    return dist[ex][ey];
}

void make_order(vector<pair<int, int>> order, int idx, int r, int c) {
    if (idx == card.size()) {
        int cnt = 0;
        int sx = r;
        int sy = c;
        
        vector<vector<int>> copy_board(4, vector<int>(4));
        
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                copy_board[i][j] = board[i][j];
            }
        }
        
        for (auto e : order) {
            cnt += bfs(copy_board, sx, sy, e.first, e.second) + 1;
            sx = e.first;
            sy = e.second;
            copy_board[sx][sy] = 0;
        }
        
        if (cnt < minval) {
            minval = cnt;
        }
        
        return;
    }
    
    order[idx*2] = point[card[idx]][0];
    order[idx*2+1] = point[card[idx]][1];
    make_order(order, idx + 1, r, c);
    
    order[idx*2] = point[card[idx]][1];
    order[idx*2+1] = point[card[idx]][0];
    make_order(order, idx + 1, r, c);
}

int solution(vector<vector<int>> Board, int r, int c) {
    int answer = 0;
    
    for (int i = 0; i < Board.size(); i++) {
        for (int j = 0; j < Board.size(); j++) {
            board[i][j] = Board[i][j];
            if (!board[i][j]) continue;
            point[board[i][j]].push_back({i, j});
        }
    }
    
    for (int i = 1; i <= 6; i++) {
        if (!point[i].empty()) card.push_back(i);
    }
    
    do {
        vector<pair<int, int>> order(card.size() * 2);
        make_order(order, 0, r, c);
    } while (next_permutation(card.begin(), card.end()));
    
    answer = minval;
    
    return answer;
}
