#include <stdio.h>
#include <string.h>

#define MAX 1000000007

int main(){

    freopen("input.txt", "r", stdin);

    int T;
    char str[10002];
    int cnt[10002][(1<<4)-1];

    scanf("%d", &T);

    for(int test=1; test<=T; ++test)
    {

        for(int i=0; i<10002; ++i){
            for(int j=0; j<(1<<4)-1; ++j)
            {
                cnt[i][j] = 0;
            }
        }
 
        scanf("%s", str);
        int len = strlen(str);
        int ans=0;

        for(int i=0; i<len; ++i)
        {
            int master = 1 << (str[i] - 'A');
            for(int j=1; j<(1<<4); ++j)
            {
                if(i==0)
                {
                    if((j&master)==0 || (j&1)==0) continue;
                    cnt[i][j-1] = 1;
                }

                else
                {
                    if(cnt[i-1][j-1] == 0) continue;
                    for(int k=1; k<(1<<4); ++k)
                    {
                        if((j&k) == 0 || (k&master)==0) continue;
                        cnt[i][k-1] = (cnt[i][k-1] + cnt[i-1][j-1])%MAX;
                    }
                }
            }
        }

        for(int i=1; i<(1<<4); ++i){
            ans = (ans + cnt[len-1][i-1])%MAX;
        }

       printf("#%d %d\n", test, ans);
    }

    return 0;
}
