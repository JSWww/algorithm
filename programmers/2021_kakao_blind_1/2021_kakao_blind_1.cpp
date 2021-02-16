#include <string>
#include <vector>
#include <iostream>

using namespace std;

string lowercase(string id) {
    string result = "";
    
    for (auto e : id) {
        if ('A' <= e && e <= 'Z') {
            e = tolower(e);
        }
        
        result += e;
    }
    
    return result;
}

string deleteExtra(string id) {
    string result = "";
    
    for (auto e : id) {
        if ('a' <= e && e <= 'z') {
            result += e;
        } else if ('0' <= e && e <= '9') {
            result += e;
        } else if (e == '-' || e == '_' || e == '.') {
            result += e;
        }
    }
    
    return result;
}

string replaceTwoDot(string id) {
    string result = "";
    bool isDot = false;
    
    for (auto e : id) {
        if (isDot && e == '.') continue;
        
        if (e == '.') isDot = true;
        else isDot = false;
        
        result += e;
    }
    
    return result;
}

string trimDot(string id) {
    if (id.size() == 0) return id;
    
    int isFirstDot = 0;
    int isLastDot = 0;
    
    if (id[0] == '.') isFirstDot = 1;
    if (id[id.size()-1] == '.') isLastDot = 1;
    
    return id.substr(isFirstDot, id.size() - isFirstDot - isLastDot);
}

string solution(string new_id) {
    string answer = "";
    
    new_id = lowercase(new_id);
    new_id = deleteExtra(new_id);
   	new_id = replaceTwoDot(new_id);
   	new_id = trimDot(new_id);
    
    if (new_id.size() == 0) {
        new_id = "a";
    }
    
    if (new_id.size() >= 16) {
        new_id = new_id.substr(0, 15);
        new_id = trimDot(new_id);
    }
    
    if (new_id.size() <= 2) {
        char lastChar = new_id[new_id.size()-1];
        
        while (new_id.size() < 3) {
            new_id += lastChar;
        }
    }
    
    answer = new_id;
    
    return answer;
}
