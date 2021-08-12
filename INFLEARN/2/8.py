n = int(input());
a = [0 for _ in range(n+1)]; 
cnt = 0; 

for i in range(2, n+1): 
    if a[i] == 0:
        cnt += 1; 
        j = 1
        while i * j <= n:
            a[i * j] = 1;
            j += 1;

print(cnt);
