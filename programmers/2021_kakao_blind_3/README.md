# [프로그래머스] 순위 검색

[문제 링크](https://programmers.co.kr/learn/courses/30/lessons/72412#)

[코드](https://github.com/JSWww/algorithm/blob/main/programmers/2021_kakao_blind_3/2021_kakao_blind_3.cpp)

## 풀이

자료구조, lower bound 문제

문제에서 나오는 선택 조건들을 2의 지수값들로 설정하고 비트 연산자를 이용해 선택 조건들을 조합하여 하나의 key로 생성하였다.

```cpp
ex)

"-" = 0
"cpp" = 2^0
"java" = 2^1
"python" = 2^2
"backend" = 2^3
"frontend" = 2^4
"junior" = 2^5
"senior" = 2^6
"chicken" = 2^7
"pizza" = 2^8

일 때,

"java backend junior pizza" = 100101010
"cpp frontend senior chicken" = 011010001
```

### 풀이 방법 1

하나의 info에서 "-"를 포함하여 key 조합 16개를 생성할 수 있다.

```cpp
ex)

"cpp backend junior pizza 150" 일 때,

{cpp, backend, junior, pizza}
{-, backend, junior, pizza}
{cpp, -, backend, pizza}
...
{-, -, -, -}
```

결국 하나의 info마다 16개의 vector에 점수를 추가하게 된다. 이렇게 하면 query를 돌 때 모든 key들을 다 확인할 필요 없이 query에서 생성한 특정 key에 대한 vector만 확인하면 된다.

query를 돌면서 각 query 마다 key를 생성하고 key에 해당하는 vector에 lower bound를 이용하여 찾고자하는 점수의 위치를 파악하여 점수의 개수를 구한다.

### 풀이 방법 2

info에서 선택조건을 조합해 특정 key를 생성하고 key에 해당하는 vector에 점수를 추가한다.

이후 query를 돌면서 query에서 생성한 key와 map에 저장된 모든 key들에 대해 & 연산자를 적용했을 때 query에서 생성한 key값이 나온다면 선택 조건이 같다는 것을 확인할 수 있고 해당 벡터에 lower bound를 이용하여 점수의 개수를 구한다.

여기서 "-" 조건을 0으로 설정함으로써 query에서 생성한 key에 "-"가 포함이 되어도 문제없게 처리한다.

## 여담

풀이 방법 2에서 정렬을 위해 multiset을 이용하였고 distance()함수를 사용하여 거리값을 구해 점수의 개수를 계산했었다. 하지만 distance() 함수는 iterator의 type마다 시간복잡도가 다르고 set 자료구조에서는 O(n)이 걸린다는 것을 확인했다. 그래서 시간초과가 났다.

그리고 풀이 방법2에서 query마다 map이 가지고 있는 모든 key(3 * 2 * 2 * 2 = 24개)를 비교하는데 다른 사람의 풀이를 보니 query의 각 선택 조건에 따라 구간을 정의하여 필요한 key들만 반복문을 실행하게 했다.

```cpp
ex)
// 쿼리 조건에 따른 구간 정의
    int ai,bi,aj,bj,ak,bk,al,bl;

    if(v[0]=="cpp") ai=bi=0;
    else if(v[0]=="java") ai=bi=1;
    else if(v[0]=="python") ai=bi=2;
    else {ai=0; bi=2;} // '-'

    if(v[2]=="backend") aj=bj=0;
    else if(v[2]=="frontend") aj=bj=1;
    else {aj=0; bj=1;}; // '-'

    if(v[4]=="junior") ak=bk=0;
    else if(v[4]=="senior") ak=bk=1;
    else {ak=0; bk=1;} // '-'

    if(v[6]=="chicken") al=bl=0;
    else if(v[6]=="pizza") al=bl=1;
    else {al=0; bl=1;} // '-'

    int score = stoi(v[7]);

    // 점수가 X점 이상인 사람의 수 계산
    int ans=0;
    for(int i=ai; i<=bi; i++){
      for(int j=aj; j<=bj; j++){
        for(int k=ak; k<=bk; k++){
          for(int l=al; l<=bl; l++){
            int n = db[i][j][k][l].size();
            if(n==0) continue;

            // 이분 탐색
            auto iter = lower_bound(db[i][j][k][l].begin(),db[i][j][k][l].end(),score);

            if(iter == db[i][j][k][l].end()) continue;
            ans += n-(iter-db[i][j][k][l].begin());
          }
        }
      }
    }
```
