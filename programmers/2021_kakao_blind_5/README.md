# [프로그래머스] 광고 삽입

[문제 링크](https://programmers.co.kr/learn/courses/30/lessons/72414#)

[코드](https://github.com/JSWww/algorithm/blob/main/programmers/2021_kakao_blind_5/2021_kakao_blind_5.cpp)

## 풀이

prefix sum, two pointer 문제

광고 구간을 동영상의 임의의 위치에 삽입하여 광고 구간합이 가장 큰 값을 찾는 문제이다.

### 풀이 방법 1

단순히 완전탐색으로 구간 합을 구현할 경우 동영상 전체 구간을 N, 광고 길이를 M이라고 할 때 O(N*M)의 시간복잡도가 걸린다. 그래서 prefix sum을 이용해야 한다.

우선 동영상의 최대 길이가 99:59:59초 = 360000초 이므로 배열로 나타낼 수 있다.

second[i] = i초에 동영상을 시청하는 시청자의 수

logs 배열을 돌면서 시청자들의 재생 구간을 초로 변환해 second[i] 값을 증가시키면 된다. 여기서 구간을 일일이 돌며 second[i] 값을 증가시키기 보다는 second[start] += 1, second[end] -= 1로 처리하게 되면 second[i] 는 second[i-1] 보다 몇 명이 더 동영상을 시청했는지의 변화량이 된다. 다시 second[i] += second[i-1] 하게 되면 i초에 동영상을 시청하는 시청자의 수를 구할 수 있다.

여기서 한 번 더 second[i] += second[i-1] 하게 되면 second[i] = 0 ~ i초까지 동영상을 시청하는 시청자 수의 부분 합이 되고 a ~ b초까지 동영상을 시청하는 시청자 수 = second[b] - second[a-1]로 O(N)의 전처리를 통해 구간 합을 O(1) 만에 구할 수 있게 된다. 이것이 prefix sum이다.

이제 동영상의 시작부터 1초씩 늘리며 광고 구간을 설정하고 second 배열을 이용해서 광고 구간에 몇 명의 시청자가 동영상을 재생하는지 구할 수 있게 된다.

### 풀이 방법 2

만약 동영상의 최대 길이가 10^9초라면 배열로 나타내기 어렵다.  
이 문제는 배열을 쓰지 않고 two pointer 알고리즘을 이용하여 해결할 수 있다.

```cpp
string numzfill(int num) ...

int calc_second(string s) ...

string calc_time(int second) ...

string solution(string play_time, string adv_time, vector<string> logs) {
    string answer = "";
    vector<pair<int, int>> event;
    int ps = calc_second(play_time);
    int as = calc_second(adv_time);
    
    for (auto e : logs) {
        int start = calc_second(e.substr(0, 8));
        int end = calc_second(e.substr(9));
        
        // 사용자의 시작 시간과 끝 시간 저장
        event.push_back({start, 1});
        event.push_back({end, -1});
    }
    
    // 시작 시간을 기준으로 오름차순으로 정렬
    event.push_back({0, 0});
    sort(event.begin(), event.end());
    
    int idx1 = 0, idx2 = 0; // 광고의 시작과 끝 인덱스
    int cnt1 = 0, cnt2 = 0; // 광고 시작 부분의 인원 수와 끝 부분의 인원 수
    int curtime = 0, maxtime = 0;
    long long curval = 0, maxval = 0;
    
    // 광고 시작 시간 0초일 때의 값 계산
    while (idx2 + 1 < event.size() && event[idx2+1].first <= as) {
        curval += (event[idx2+1].first - event[idx2].first) * cnt2;
        cnt2 += event[idx2+1].second;
        idx2++;
    }
    
    curval += (as - event[idx2].first) * cnt2;
    maxval = curval;
    
    // idx1, idx2를 이동시키며 최적값 계산
    while (idx2 + 1 < event.size() && curtime <= ps - as) {
        // 다음 event 까지의 거리 계산
        int delta1 = event[idx1+1].first - curtime;
        int delta2 = event[idx2+1].first - (curtime + as);
        
        if (delta1 <= delta2) { // 시작 부분이 다음 event에 더 가까울 경우
            curval += (cnt2 - cnt1) * delta1 * 1LL;
            cnt1 += event[idx1+1].second;
            idx1++;
            curtime += delta1;
        } else { // 끝 부분이 다음 event에 더 가까울 경우
            curval += (cnt2 - cnt1) * delta2 * 1LL;
            cnt2 += event[idx2+1].second;
            idx2++;
            curtime += delta2;
        }
        
        if (maxval < curval) {
            maxval = curval;
            maxtime = curtime;
        }
    }
   
    answer = calc_time(maxtime);
    
    return answer;
}
```

## 여담

없음
