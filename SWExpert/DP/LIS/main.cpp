#include <stdio.h>
#include <algorithm>

int arr[1002];
int dp[1002];
int box[1002];
int ans[1002];

int main(){
    freopen("input.txt", "r", stdin);
    int N;
    scanf("%d", &N);

    for(int i=0; i<N; ++i){
        scanf("%d", &arr[i]);
    }
    
    int idx = 0;
    dp[idx++] = arr[0];
    box[0] = 0;

    for(int i=1; i<N; ++i){
        if(dp[idx-1] < arr[i])
        {
            box[i] = idx;
            dp[idx++] = arr[i];
        }
        else{
            box[i] = std::lower_bound(dp, dp+idx, arr[i]) - dp;
            dp[box[i]] = arr[i];
        }
    }

    int t = 0;
    for(int i=N-1; i>=0; --i)
    {
        if(idx-1 == box[i]){
            ans[t++] = arr[i];
            idx--;
        }
    }

    printf("%d\n", t);
    for(int i=t-1; i>0; --i){
        printf("%d ", ans[i]);
    }   
    printf("%d\n", ans[0]);
    return 0;
}
