import sys
import itertools

sys.stdin = open("input.txt", "rt")

N, K = map(int, input().split())

nums = list(map(int, input().split()))

sums = []

T = 3

idxs = [i for i in range(N)]

nPr = itertools.permutations(idxs, T)


sums = []
for idx in nPr:
    val = 0
    for i in idx:
        val += nums[i]
    sums.append(val)


sums = list(set(sums))
sums.sort(reverse=True)

print(sums[K-1])
