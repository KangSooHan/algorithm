import sys
import math

sys.stdin = open("input.txt", "rt")

n = int(input())

nums = list(map(int, input().split()))

sums = 0
for i in nums:
    sums += i
avg = round(sums / len(nums))

min_val = 1000000
idx = 0
score = 0
for i, num in enumerate(nums):
    if min_val > abs(avg-num):
        min_val = abs(avg-num)
        idx = i
        score = num

    elif min_val == abs(avg-num):
        if num > score:
            score = num
            idx = i


print(avg, idx+1)

