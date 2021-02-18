#include <string>
#include <vector>
#include <algorithm>
#include <unordered_map>

using namespace std;

int maxv[11];
unordered_map<string, int> um;

void comb(string order, int cnt) {
    vector<int> ind(order.size(), 1); 

    for (int i = 0; i < cnt; i++) {
        ind[i] = 0;
    }

    do {
        string setmenu = "";

        for (int i = 0; i < order.size(); i++) {
            if (ind[i] == 0) setmenu += order[i];
        }
        
        um[setmenu]++;
        maxv[cnt] = max(maxv[cnt], um[setmenu]);
    } while (next_permutation(ind.begin(), ind.end()));
    
    return;
}

vector<string> solution(vector<string> orders, vector<int> course) {
    vector<string> answer;
    
    for (auto order : orders) {
        sort(order.begin(), order.end());
        
        for (auto cnt : course) {
            if (order.size() < cnt) break;
            comb(order, cnt);
        }
    }
    
    for (auto e : um) {
        if (e.second < 2) continue;
        
        if (maxv[e.first.size()] == e.second) {
            answer.push_back(e.first);
        }
    }
    
    sort(answer.begin(), answer.end());
    
    return answer;
}
