#include <string>
#include <vector>
#include <map>
#include <sstream>
#include <algorithm>

using namespace std;

vector<string> keyword {
    "cpp",
    "java",
    "python",
    "backend",
    "frontend",
    "junior",
    "senior",
    "chicken",
    "pizza",
    "-"
};

vector<int> solution(vector<string> info, vector<string> query) {
    vector<int> answer;
    map<string, int> item;
    map<int, vector<int>> m;

    for (int i = 0; i < keyword.size(); i++) {
        item[keyword[i]] = 1 << i;
    }

    item["-"] = 0;

    for (auto e : info) {
        stringstream ss(e);
        vector<string> v;
        string s;

        while (ss >> s) {
            v.push_back(s);
        }

        int key = 0;

        for (int i = 0; i < 4; i++) {
            key |= item[v[i]];
        }

        m[key].push_back(stoi(v[4]));
    }
    
    for (auto e : m) {
        sort(m[e.first].begin(), m[e.first].end());
    }
    
    for (auto e : query) {
        stringstream ss(e);
        vector<string> v;
        string s;

        while (ss >> s) {
            if (s.compare("and") == 0) continue;
            v.push_back(s);
        }

        int key = 0;
        int cnt = 0;
        int score = stoi(v[4]);

        for (int i = 0; i < 4; i++) {
            key |= item[v[i]];
        }

        for (auto e2 : m) {
            if ((e2.first & key) == key) {
                cnt += m[e2.first].end() - lower_bound(m[e2.first].begin(), m[e2.first].end(), score);
            }
        }

        answer.push_back(cnt);
    }
    
    return answer;
}