#include <stdio.h>
#include <vector>

using namespace std;

pair<int, int> object[101];

int val[102][1002];

int main(){
    freopen("input.txt", "r" ,stdin);
    int T;
    scanf("%d", &T);

    for(int test = 1; test<=T; ++test)
    {
        int n, k;
        scanf("%d %d", &n, &k);

        for(int i=0; i<n; ++i){
            scanf("%d %d", &(object[i].first), &(object[i].second));
        }


        for(int i=0; i<=n; ++i) for(int j=0; j<=n; ++j) val[i][j] = 0;

        for(int i=1; i<=n; ++i){
            for(int j=1; j<=k; ++j){
                if(object[i-1].first <= j) val[i][j] = max(object[i-1].second + val[i-1][j-object[i-1].first], val[i-1][j]);
                else val[i][j] = val[i-1][j];
            }
        }

        printf("#%d %d\n", test, val[n][k]);

    }

    return 0;
}
