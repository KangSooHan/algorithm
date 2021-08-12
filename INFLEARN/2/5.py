n, m = map(int, input().split());

arr = [0]*(m + n + 1);
for i in range(1, n+1):
    for j in range(1, m+1):
        arr[i + j] += 1;
maxCnt = 0;

for sum, cnt in enumerate(arr):
    if maxCnt < cnt:
        maxCnt = cnt;

for sum, cnt in enumerate(arr):
    if maxCnt == cnt:
        print(sum, end=" ");
