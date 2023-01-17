#include <stdio.h>

int main(){
    freopen("input.txt", "r", stdin);
    int T;
    scanf("%d", &T);

    for(int test=1; test<=T; ++test)
    {
    int ans, n, m;
    int cnt = 0;
    scanf("%d %d", &n, &m);

    bool flag=true;
    for(int i=0; i<n; ++i){
        flag &= (m%2)==1 ? true : false;
        m >>= 1;
        if(!flag) break;
    }

    if(flag) printf("#%d ON\n", test);
    else printf("#%d OFF\n", test);
    }
    return 0;
}
