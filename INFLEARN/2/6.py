n = int(input());     
a = list(map(int, input().split()));

def digit_sum(x):
    x = str(x);
    b = [];   
    for i in x:
        i = int(i);
        b.append(i)
    return sum(b);

max = 0
maxIndex = 0

for index, value in enumerate(a):
    if max < digit_sum(value):
        max = digit_sum(value);
        maxIndex = index;

print(a[maxIndex]);
