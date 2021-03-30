#include <string>
#include <vector>
#include <map>
#include <sstream>

using namespace std;

struct Page {
    int idx;
    double base_score;
    double link_score;
    vector<string> external_link;
    
    Page() {
        this->base_score = 0;
        this->link_score = 0;
    }
    
    double match_score() {
        return this->base_score + this->link_score;
    }
    
    double calc_link_score() {
        return this->base_score / this->external_link.size();
    }
};

string get_url(string& line, int idx) {
    string result = "";
    int cnt = 0;
    
    for (int i = idx; i < line.size(); i++) {
        if (line[i] == '\"') {
            cnt++;
            continue;
        }
        
        if (cnt == 4) break;
        if (cnt == 3) result += line[i];
    }
    
    return result;
}

string get_link(string& line, int idx) {
    string result = "";
    int cnt = 0;
    
    for (int i = idx; i < line.size(); i++) {
        if (line[i] == '\"') {
            cnt++;
            continue;
        }
        
        if (cnt == 2) break;
        if (cnt == 1) result += line[i];
    }
    
    return result;
}

int find_word(string& line, string& word) {
    int cnt = 0;
    string s = "";
    
    for (auto& e : word) {
        e = tolower(e);
    }
    
    for (int i = 0; i < line.size(); i++) {
        if ('a' <= line[i] && line[i] <= 'z' ||
            'A' <= line[i] && line[i] <= 'Z') {
            s += tolower(line[i]);
        } else {
            if (s.compare(word) == 0) cnt++;
            s = "";
        }
    }
    
    if (s.compare(word) == 0) cnt++;
    
    return cnt;
}

void parse_page(map<string, Page>& pageInfo, string& s, string& word) {
    stringstream ss(s);
    string line;
    string url = "";
    
    while (getline(ss, line, '\n')) {
        int idx = 0;
        
   		if ((idx = line.find("<meta property=\"og:url\" content=\"https://")) != string::npos) {
            url = get_url(line, idx);
            continue;
        }
        if (url.size() == 0) continue;

        idx = 0;

        while (idx < line.size() && idx != string::npos) {
            idx = line.find("<a href=\"https://", idx);
            
            if (idx != string::npos) {
                string link = get_link(line, idx);
                pageInfo[url].external_link.push_back(link);
                idx++;
            }
        }
        
        int cnt = find_word(line, word);
        pageInfo[url].base_score += cnt;
    }
    
    pageInfo[url].idx = pageInfo.size() - 1;
}

int solution(string word, vector<string> pages) {
    int answer = 0;
    map<string, Page> pageInfo;
    
    for (auto p : pages) {
   		parse_page(pageInfo, p, word);     
    }
    
    for (auto p : pageInfo) {
        for (auto link : p.second.external_link) {
            if (pageInfo.find(link) == pageInfo.end()) continue;
            pageInfo[link].link_score += p.second.calc_link_score();
        }
    }
    
    double maxval = -1;
    
    for (auto p : pageInfo) {
        double diff = maxval - p.second.match_score();
        
        if (diff < 0) {
            maxval = p.second.match_score();
            answer = p.second.idx;
        } else if (diff == 0) {
            if (answer > p.second.idx) {
                answer = p.second.idx;
            }
        }
    }
    
    return answer;
}
