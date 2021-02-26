#include <string>
#include <vector>
#include <map>
#include <sstream>
#include <algorithm>

using namespace std;

map<string, int> item;
map<int, vector<int>> m;
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

void make_key(vector<string> v, int key, int i) {
    if (i == 4) {
        m[key].push_back(stoi(v[4]));
        return;
    }

    key |= item[v[i]];
    make_key(v, key, i + 1);
    key ^= item[v[i]];
    key |= item["-"];
    make_key(v, key, i + 1);
}

vector<int> solution(vector<string> info, vector<string> query) {
    vector<int> answer;

    for (int i = 0; i < keyword.size(); i++) {
        item[keyword[i]] = 1 << i;
    }

    for (auto e : info) {
        stringstream ss(e);
        vector<string> v;
        string s;

        while (ss >> s) {
            v.push_back(s);
        }

        make_key(v, 0, 0);
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

        cnt = m[key].end() - lower_bound(m[key].begin(), m[key].end(), score);
        answer.push_back(cnt);
    }

    return answer;
}