#include <stdio.h>
#include <string.h>
#include <algorithm>

char a[1001], b[1001];
int DP[1001][1001];

int main(){
    freopen("input.txt", "r", stdin);

    int T;
    scanf("%d", &T);

    memset(DP, 0, sizeof(DP));

    for(int test=1; test<=T; ++test)
    {
        scanf("%s %s", a, b);

        int asize = strlen(a);
        int bsize = strlen(b);

        for(int i=1; i<=asize; ++i)
        {
            for(int j=1; j<=asize; ++j)
            {
                if(a[i-1] == b[j-1])
                    DP[i][j] = DP[i-1][j-1] + 1;

                else
                    DP[i][j] = std::max(DP[i-1][j], DP[i][j-1]);
            }
        }

        printf("%d\n", DP[asize][bsize]);
    }

    return 0;
}
