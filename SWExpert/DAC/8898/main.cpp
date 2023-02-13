#include <stdio.h>
#include <algorithm>

int cow[500001];

void sort(int start, int end){
    if(start >= end) return;

    int pivot = start;
    int i = pivot + 1;
    int j = end;
    int temp;

    while(i<=j){
        while(i <= end && cow[i] <= cow[pivot]){
            i++;
        }
        while(j > start && cow[j] >= cow[pivot]){
            j--;
        }

        if(i > j){
            temp = cow[j];
            cow[j] = cow[pivot];
            cow[pivot] = temp;
        }
        else{
            temp = cow[i];
            cow[i] = cow[j];
            cow[j] = temp;
        }
    }

    sort(start, j-1);
    sort(j+1, end);
}

int main(){
    freopen("input.txt", "r", stdin);

    int T;
    scanf("%d", &T);

    for(int test=1; test<=T; ++test){
        int N, M;
        scanf("%d %d", &N, &M);

        int c1, c2;
        scanf("%d %d", &c1, &c2);
        for(int i=0; i<N; ++i){
            scanf("%d", &cow[i]);
        }
        std::sort(cow, cow+N);

        int cnt = 1;
        int min = 999999999;
        for(int i=0; i<M; ++i){
            int horse;
            scanf("%d", &horse);
            int l=0;
            int r=N;
            while(l!=r){
                int mid = (r+l)/2;
                if(horse >= cow[mid]){
                    l = mid+1;
                }
                else{
                    r = mid;
                }
            }

            if(l < N){
                int val = horse - cow[l];
                val = val>0 ? val : -val;
                if(min > val){
                    cnt = 1;
                    min = val;
                }
                else if(min == val){
                    cnt++;
                }
            }
            if(l-1 >= 0){
                int val = horse - cow[l-1];
                val = val>0 ? val : -val;

                if(min > val){
                    cnt = 1;
                    min = val;
                }
                else if(min == val){
                    cnt++;
                }
            }
        }
        int len = c1-c2;
        len = len > 0 ? len : -len;
        printf("#%d %d %d\n", test, min + len, cnt);
    }
}
