# [BOJ 1967] 트리의 지름

[문제 링크](https://www.acmicpc.net/problem/1967)

[코드](https://github.com/JSWww/algorithm/blob/main/boj/1967/1967.cpp)

## 풀이

그래프 탐색 문제

임의의 한 노드에서 가장 먼 거리에 있는 A 노드를 찾고 다시 A 노드에서 가장 먼 거리에 있는 B 노드를 찾게 되면 A - B 노드 사이의 거리가 트리의 지름이 된다.

## 여담

bfs와 다익스트라 두 가지 방식으로 문제를 풀었다.

보통 가중치가 있는 그래프에서는 bfs를 사용하지 못하지만 해당 문제는 트리여서 거리가 갱신되는 과정이 없기 때문에 bfs로 풀이 가능

다익스트라의 경우 한 노드에서 모든 노드 사이의 거리를 구하고 그 중에서 가장 거리가 먼 노드를 찾아 다시 다익스트라를 이용하여 해당 노드에서 가장 거리가 먼 노드를 찾는다.