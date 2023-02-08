#include <stdio.h>
#include <algorithm>

int arr[200001];

int main(){
    freopen("input.txt", "r", stdin);

    int T;
    scanf("%d", &T);

    for(int test=1; test<=T; ++test){
        int n, p, prev;
        scanf("%d %d", &n, &p);

        for(int i=0; i<n; ++i){
            scanf("%d", &arr[i]);
        }

        int max = 0;

        for(int i=0; i<n; ++i){
            int l = i, r = n;
            while(l!=r){
                int m = (l+r)/2;
                (arr[m] - arr[i]) <= ((m-i) + p) ? l = m+1 : r = m;
            }
            if(l-i + p > max) max = l-i+p;
        }
        printf("#%d %d\n", test, max);
    }
}
