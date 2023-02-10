#include <stdio.h>

long long int arr[101];

bool check(int n, long long int mid, long long int m){
    long long int val = 0;
    for(int i=0; i<n; ++i){
        val += arr[i]/mid;
        if(val >= m) return true;
    }
    return false;
}

int main(){
    freopen("input.txt", "r", stdin);
    int T;
    scanf("%d", &T);

    for(int test=1; test<=T; ++test){
        int n;
        long long int m;
        scanf("%d %lld", &n, &m);

        long long int r=1;
        for(int i=0; i<n; ++i){
            scanf("%lld", &arr[i]);
            r = r<arr[i] ? arr[i] : r;
        }
        long long int l=1;
        if(l==r) printf("#%d 0\n", test);
        else{
            while(l!=r){
                long long int mid = (l+r)/2;
                if(check(n, mid, m)){
                    l = mid+1;
                }
                else{
                    r = mid;
                }
            }
            printf("#%d %lld\n", test, l-1);
        }

    }

}
