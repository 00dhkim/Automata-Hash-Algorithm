# Automata-Hash-Algorithm
### 요약
--1. 구조 개선하기--
2. 규칙 개선하기
3. 규칙찾는 프로그램 구현하기
4. rainbow table 회피 확인
5. 충돌여부 판단

**binary string to decimal 함수 만들기**

### rule test
HEIGHT: 32, WIDTH: 23, input char: 1
이렇게 실행했을 경우 출돌쌍이 다수 발견되었음. 환경변수(가로, 세로)를 수정하여 다른 경우에도 충돌하는지 확인하자.
만약 다른 경우에도 충돌이 많다면 규칙을 수정해야 할 것.

### 현재 가장 필요한 연구
적은 input data의 경우 눈덩이 효과 없음 -> 이부분 개선
이 알고리즘이 해시에 쓰일 수 있는지에 대한 연구 -> 정말로 랜덤한가?
_①rainbow table 회피, ②충돌이 일어나는지 판단하기_

### 해야할 일
적은 input으로도 복잡한 결과를 내려면 **규칙을 개선**해야 한다.
만약 input이 적을 경우 초기 matrix가 규칙적인 모양새가 나와, 적절한 규칙으로 이를 잘 섞어야 한다. 
-> 랜덤 규칙을 대입해 가장 좋은 규칙을 찾는 프로그램 만들자.

### follow-up research goal
--INPUT, OUTPUT Matrix Format 개선 (salt 배치법 등)--
최적의 playtime 연구
최적의 규칙 연구 (2^20가지 경우의 수)
규칙의 적합도 판단 함수 개선 (타당한 이유를 들어)
crash 확률 실제로 계산하기, crash 사례 찾기
단순 input의 단순 output 문제 해결

### report
- setting report
Matrix Size = [24, 32] = 768 bit
Input Size = [6, 32]*3 = 576 bit (96 characters)
Salt Size = [2, 32]*3 = 192 bit (32 characters)
※1 character = 6 bits
hash size : 128 characters
PLAYTIME = 100

- speed
10000 times executing in 107.1 seconds
10.71ms/execute

### 참고 링크
https://softwareengineering.stackexchange.com/questions/49550/which-hashing-algorithm-is-best-for-uniqueness-and-speed
https://en.wikipedia.org/wiki/Hash_function_security_summary







