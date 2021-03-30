# [프로그래머스] 매칭 점수

[문제 링크](https://programmers.co.kr/learn/courses/30/lessons/42893)

[코드](https://github.com/JSWww/algorithm/blob/main/programmers/2019_kakao_blind_6/2019_kakao_blind_6.cpp)

## 풀이

구현 문제

string으로 주어진 html 문서를 적절히 파싱하여 답을 구하는 문제이다.  
문자열 처리 로직을 적절히 구현하면 된다.  
한 라인씩 split한 다음 url, external link, word를 찾았다.

## 여담

한 라인에 한 개의 외부 링크만 있을 것이라고 착각했다.

`<a href="test1">test1</a><a href="test2">test2</a>`
