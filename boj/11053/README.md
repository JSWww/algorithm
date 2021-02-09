# [BOJ 11053] 가장 긴 증가하는 부분 수열

[문제 링크](https://www.acmicpc.net/problem/11053)

[코드](https://github.com/JSWww/algorithm/blob/main/boj/11053/11053.cpp)

## 풀이

dp 문제

dp[i] = 수열의 i번째 값을 마지막으로 하는 가장 긴 증가하는 부분 수열 (dp 배열은 1로 초기화)

i는 현재, j는 0 ~ i - 1번째 라고 할 때

1. arr[j] < arr[i] (증가하는 수열이여야 함)
2. dp[i] <= dp[j] (가장 긴 수열을 찾아야 함)

  위의 두 조건을 만족하게 되면 dp[i] = dp[j] + 1

## 여담

2년 전에 풀었던 문제였는데 다시 푸니까 헷갈렸다.
