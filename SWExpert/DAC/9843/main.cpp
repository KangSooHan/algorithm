#include <stdio.h>

unsigned long long int calc(unsigned long long int val){
    if(val %2 == 0) return val/2*(val+1);
    else return (val+1)/2*val;
}

long long int sqrt(unsigned long long int x){
    if(x==1) return 1;
    unsigned long long int start = 0;
    unsigned long long int end = x;
    unsigned long long int ans;
    while(start !=  end){
        if(end >= 2000000000) end = 2000000000;
        unsigned long long int middle = (start+end)/2;
        unsigned long long int val = calc(middle);
        if(val > x){
            end = middle;
        }
        else if(val < x){
            start = middle+1;
        }
        else return middle;
    }
    return -1;
}

int main(){
   // freopen("input.txt", "r", stdin);
    int T;
    scanf("%d", &T);

    for(int test=1; test<=T; ++test){
        unsigned long long int N;
        scanf("%llu", &N);

        printf("#%d %lld\n",test, sqrt(N));
    }
}
