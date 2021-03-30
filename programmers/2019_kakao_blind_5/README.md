# [프로그래머스] 길 찾기 게임

[문제 링크](https://programmers.co.kr/learn/courses/30/lessons/42892)

[코드](https://github.com/JSWww/algorithm/blob/main/programmers/2019_kakao_blind_5/2019_kakao_blind_5.cpp)

## 풀이

트리 문제

트리의 순회보다는 트리 구성에 중점을 맞춘 문제이다.  
트리 노드에 대한 구조체를 정의하고 y좌표가 트리의 레벨이기 때문에 y좌표를 기준으로 노드들을 내림차순으로 정렬한다. 그러면 nodes[0]은 트리의 root가 된다.  
이후 모든 노드들을 root부터 시작해서 x좌표를 비교해가며 트리의 왼쪽이나 오른쪽 자식 노드로 이동한다. 만약 자식 노드가 없다면 현재 노드를 자식 노드에 삽입하면 된다.  
마지막으로 preorder와 postorder를 구현하면 된다.

## 여담

없음
