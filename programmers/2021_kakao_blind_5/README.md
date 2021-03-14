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

// 내용 추가 예정

## 여담

없음
