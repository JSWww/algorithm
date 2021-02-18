# [프로그래머스] 메뉴 리뉴얼

[문제 링크](https://programmers.co.kr/learn/courses/30/lessons/72411#)

[코드](https://github.com/JSWww/algorithm/blob/main/programmers/2021_kakao_blind_2/2021_kakao_blind_2.cpp)

## 풀이

브루트 포스 문제

입력 제한사항이 크지 않기 때문에 완전탐색으로 풀 수 있다.

각 주문으로부터 모든 조합을 구한다. 그리고 각 조합의 개수를 세어 문자열의 길이가 같은 조합 중 가장 큰 값을 찾으면 된다.

이때 "ABC" 와 "CBA"를 같은 조합으로 세지 않게 order를 정렬 후 조합을 구한다.

조합은 next_permutation() 함수를 이용하였다. next_permutation() 함수는 중복인 경우를 제외하고 순열을 생성하므로 벡터에 0과 1을 넣어 순열을 생성하고 값이 1인 인덱스만 취함으로써 중복인 경우를 배제하였다.

## 여담

시간이 매우 오래 걸려서 다른사람의 풀이를 보고 다시 풀어봤다.

첫 코드는 알파벳 벡터를 만들고 이 벡터를 통해 모든 조합을 만들어서 각 주문들에 대해 해당 조합이 있나 없나 체크하는 과정이 있었는데 현재 코드는 주문에서 조합을 만들기 때문에 체크 과정이 불필요하게 된다.

그리고 값을 구하는 과정에서 값이 갱신될 때 벡터를 clear() 했었다.
현재 코드는 길이가 i인 조합 중 최대 주문 횟수를 저장하는 maxv 배열과 조합과 주문 횟수를 저장하는 map을 이용하여 값을 구하는 과정을 최적화하였다.

어떻게 하면 좀 더 효율적으로 문제를 풀 수 있을지 고민하면서 풀어야할 것 같다.

첫 코드

```c++
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

vector<string> solution(vector<string> orders, vector<int> course) {
    vector<string> answer;
    vector<char> alpha(26);
    
    for (int i = 0; i < 26; i++) {
        alpha[i] = 65 + i;
    }
    
    for (auto cnt : course) {
        vector<int> ind(26, 1); 
        vector<string> arr;
        int maxV = 1;
        
        for (int i = 0; i < cnt; i++) {
            ind[i] = 0;
        }
        
        do {
            string setmenu = "";
            int count = 0;
            
            for (int i = 0; i < 26; i++) {
                if (ind[i] == 0) setmenu += alpha[i];
            }
            
            for (auto order : orders) {
                bool check = true;
                
                for (auto single : setmenu) {
                    if (order.find(single) == string::npos) {
                        check = false;
                        break;
                    }
                }
                
                if (check) count++; 
            }
            
            if (maxV < count) {
                maxV = count;
                arr.clear();
                arr.push_back(setmenu);
            } else if (maxV == count && maxV > 1) {
                arr.push_back(setmenu);
            }
        } while (next_permutation(ind.begin(), ind.end()));
        for (auto e : arr) {
            answer.push_back(e);
        }
    }
    
    sort(answer.begin(), answer.end());
    
    return answer;
}
```
