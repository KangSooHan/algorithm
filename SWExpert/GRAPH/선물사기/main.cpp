#include <stdio.h>
#include <vector>

char MaP[21][21];
int check[21][21];
int alpha[26];
int ans, r, c;

using namespace std;

int dx[4] = {0, 1, 0, -1};
int dy[4] = {1, 0, -1, 0};

void solve(int x, int y, int cnt)
{
    
    if(alpha[MaP[x][y] - 'a'] == 1)
    {
        return;
    }
    if(ans < cnt) ans = cnt;
    check[x][y] = 1;
    alpha[MaP[x][y] - 'a'] = 1;

    for(int i=0; i<4; ++i){
        int nx = x+dx[i], ny = y+dy[i];
        if(nx<0 || nx>=r || ny<0 || ny>=c) continue;
        if(check[nx][ny] == 1) continue;
        if(alpha[MaP[nx][ny] - 'a'] == 1) continue;
        solve(nx, ny, cnt+1);
        alpha[MaP[nx][ny] - 'a'] = 0;
        check[nx][ny] = 0;
    }
}


void init(){
    ans = 0;
    for(int i=0; i<26; ++i) alpha[i] = 0;
    for(int i=0; i<21; ++i){
        for(int j=0; j<21; ++j){
            check[i][j] = 0;
        }
    }    
}


int main()
{
    freopen("input.txt", "r", stdin);

    int T;
    scanf("%d", &T);
    for(int t=1; t<=T; ++t)
    {
        init();
        scanf("%d %d", &r, &c);

        for(int i=0; i<r; ++i){
            for(int j=0; j<c; ++j){
                scanf(" %c ", &MaP[i][j]);
            }
        }
        solve(0, 0, 1);
        printf("#%d %d\n", t, ans);
    }


    return 0;
}
