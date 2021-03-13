# [프로그래머스] 합승 택시 요금

[문제 링크](https://programmers.co.kr/learn/courses/30/lessons/72413)

[코드](https://github.com/JSWww/algorithm/blob/main/programmers/2021_kakao_blind_4/2021_kakao_blind_4.cpp)

## 풀이

플로이드 와샬 문제

n값이 최대 200이므로 O(n^3) 시간복잡도로 풀 수 있다.

모든 정점들간의 경로값을 구한 후 중간 지점을 n개의 정점들로 설정하고  
`graph[start][mid] + graph[mid][a] + graph[mid][b]` 의 최소값을 구하면 된다.

## 여담

처음에는 a와 b사이의 최단 경로에 있는 정점으로 mid를 설정해서 좀 헤맸었다. 덕분에 플로이드 와샬을 이용해 두 지점간의 거리를 구하는 방법을 알게 되었다.

#### 경로 구하는 코드

```cpp
// before[i][j] = i 정점에서 j 정점까지의 경로에서 j 정점 직전에 나오는 정점
before[n][n];

// before 배열 초기화
for (int i = 1; i <= n; i++) {
  for (int j = 1; j <= n; j++) {
      before[i][j] = i;
  }
}

void floyd(int n) {
  for (int k = 1; k <= n; k++) {
      for (int i = 1; i <= n; i++) {
          for (int j = 1; j <= n; j++) {
              if (graph[i][j] > graph[i][k] + graph[k][j]) {
                  graph[i][j] = graph[i][k] + graph[k][j];
                  // 직전정점 행렬 최신화
                  before[i][j] = before[k][j];
              }
          }
      }
  }
}
```

#### 경로 구하는 예시

```cpp
before 배열이 다음과 같을 때

- 3 4 5 1
4 - 4 2 1
4 3 - 2 1
4 3 4 - 1
4 3 4 5 -

1 정점에서 3 정점까지의 경로 구하는 법

시작 = 3 (index는 0부터 시작)

before[0][2] = 4이므로 3 정점 직전에 4 추가
4 -> 3

before[0][3] = 5이므로 4 정점 직전에 5 추가
5 -> 4 -> 3

before[0][4] = 1이고 시작 정점과 같으므로 경로 완성
1 -> 5 -> 4 -> 3
```
