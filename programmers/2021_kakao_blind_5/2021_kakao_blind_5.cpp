#include <string>
#include <vector>

using namespace std;

string numzfill(int num) {
    if (num < 10) return "0" + to_string(num);
    else return to_string(num);
}

int calc_second(string s) {
    int second = 0;
    
    second += stoi(s.substr(0, 2)) * 3600;
    second += stoi(s.substr(3, 2)) * 60;
    second += stoi(s.substr(6));
    
    return second;
}

string calc_time(int second) {
    string result = "";
    
    result += numzfill(second / 3600) + ":";
    second %= 3600;
    
    result += numzfill(second / 60) + ":";
    second %= 60;
    
    result += numzfill(second);
    
    return result;
}

string solution(string play_time, string adv_time, vector<string> logs) {
    string answer = "";
    int second[360001] = {0,};
    int ps = calc_second(play_time);
    int as = calc_second(adv_time);
    
    for (auto e : logs) {
		int start = calc_second(e.substr(0, 8));
		int end = calc_second(e.substr(9));
        
        second[start]++;
        second[end]--;
    }
    
    for (int i = 1; i <= ps; i++) {
        second[i] += second[i-1];
    }
    
    long long curval = 0;
    long long mxval = 0;
    int mxtime = 0;
    
    for (int i = 0; i < as; i++) {
        curval += second[i];
    }
    
    mxval = curval;
    
    for (int i = 1; i <= ps - as; i++) {
        curval = curval - second[i-1] + second[i+as-1];
        
        if (mxval < curval) {
            mxval = curval;
            mxtime = i;
        }
    }
    
    answer = calc_time(mxtime);
    
    return answer;
}
