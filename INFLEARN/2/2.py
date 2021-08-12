import sys

sys.stdin = open("input.txt", "rt")

T = int(input())

for i in range(T):
    n, s, e, k = map(int, input().split())

    nums = list(map(int, input().split()))

    nums.sort()

    print("#{} {}".format(i+1, nums[k]))


