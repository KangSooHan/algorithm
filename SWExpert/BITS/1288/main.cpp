#include <stdio.h>

int main(){
    freopen("input.txt", "r", stdin);

    int T;
    scanf("%d", &T);

    for(int test=1; test<=T; ++test)
    {
        int v, ans;
        scanf("%d", &v);
        int check = 0;
        for(int i=1; ; ++i){
            int value = v * i;
            while(value){
                check |= (1 << (value % 10));
                value /= 10;
            }
            if(check == (1<<10)-1){
                ans = i;
                break;
            }
        }

        printf("#%d %d\n", test, v*ans);
    }
}
