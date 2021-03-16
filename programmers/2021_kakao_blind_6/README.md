# [프로그래머스] 카드 짝 맞추기

[문제 링크](https://programmers.co.kr/learn/courses/30/lessons/72415)

[코드](https://github.com/JSWww/algorithm/blob/main/programmers/2021_kakao_blind_6/2021_kakao_blind_6.cpp)

## 풀이

bfs, 시뮬레이션, brute force 문제

우선 찾고자 하는 카드의 순서를 정한다. 카드 종류는 6개이므로 6!의 순서를 가질 수 있다.  
그리고 같은 종류의 카드가 2장씩 있기 때문에 만약 카드가 1, 1', 2, 2', 3, 3'이 있을 경우 1 -> 1'으로 찾는 경우와 1' -> 1으로 찾는 경우를 따져야 한다. 카드 종류가 6가지 일 때 2^6가지의 순서가 있으므로 최종적으로 카드를 방문하는 경우의 수는 6! * 2^6개가 된다.  
현재 위치에서 다음 카드가 있는 최단 경로는 bfs를 이용하여 구하고 한 경로마다 12개의 카드가 존재하므로 시간복잡도는 O(6! * 2^6 * 12 * 4^2)이 된다.

## 여담

dp를 이용해서 최적화시킬 수 있다. (카드 종류를 L, R이라 가정)  
(dp 배열의 크기는 12이므로 시간복잡도는 (6! * 12 * 12 * 4^2))

```cpp
dp[i][0] = i번째 카드까지 지웠을 때의 최소 거리 (i번째 카드는 L을 먼저 방문하고 R을 방문)
dp[i][1] = i번째 카드까지 지웠을 때의 최소 거리 (i번째 카드는 R을 먼저 방문하고 L을 방문)

dp[i][0] = min(dp[i-1][0] + dist({i-1}R, {i}L), dp[i-1][1] + dist({i-1}L, {i}L)) + dist({i}L, {i}R);
dp[i][1] = min(dp[i-1][0] + dist({i-1}R, {i}R), dp[i-1][1] + dist({i-1}L, {i}R)) + dist({i}R, {i}L);
```