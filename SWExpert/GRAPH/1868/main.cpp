#include <stdio.h>
#include <vector>

int N;
char MAP[301][301];
int nei[301][301];
int vis[301][301];

struct stack{
    std::pair<int, int> pool[90001];
    int r;

    void init(){
        r=0;
    }

    void push(std::pair<int, int> data){
        pool[r++] = data;
    }

    std::pair<int, int> pop(){
        return pool[--r];
    }

    bool empty(){
        return r==0;
    }
};

stack s;

int dx[8] = {0, 1, 0, -1, 1, 1, -1, -1};
int dy[8] = {1, 0, -1, 0, 1, -1, -1, 1};

int check(int x, int y)
{
    int cnt = 0;
    for(int d=0; d<8; ++d)
    {
        if(MAP[x+dx[d]][y+dy[d]] == '*') cnt++;
    }
    return cnt;
}

void dfs(int x, int y)
{
    s.push(std::make_pair(x, y));

    while(!s.empty()){
        std::pair<int, int> cur = s.pop();
        vis[cur.first][cur.second] = 1;

        if(nei[cur.first][cur.second] == 0)
        {
            for(int d=0; d<8; ++d)
            {
                int nx = cur.first + dx[d];
                int ny = cur.second + dy[d];
                if(nx < 0 || nx>= N || ny < 0 || ny >= N) continue;
                if(nei[nx][ny] == -1) continue;
                if(vis[nx][ny] == 1) continue;
                s.push(std::make_pair(nx, ny));
            }
        }
    }
}

int main(){
    freopen("sinput.txt", "r", stdin);

    int T;
    scanf("%d", &T);

    for(int test=1; test<=T; ++test)
    {
        scanf("%d", &N);

        for(int i=0; i<N; ++i){
            for(int j=0; j<N; ++j){
                scanf(" %c", &MAP[i][j]);
                nei[i][j] = -1;
                vis[i][j] = 0;
            }
        }

        for(int i=0; i<N; ++i){
            for(int j=0; j<N; ++j){
                if(MAP[i][j] != '*'){
                    nei[i][j] = check(i, j);
                }
            }
        }

        int ans = 0;
        for(int i=0; i<N; ++i){
            for(int j=0; j<N; ++j){
                if(nei[i][j] == 0){
                    if(vis[i][j] == 1) continue;
                    dfs(i, j);
                    ans++;
                }
            }
        }

        for(int i=0; i<N; ++i){
            for(int j=0; j<N; ++j){
                if(nei[i][j] <= 0) continue;
                if(vis[i][j] == 1) continue;
                ans++;
            }
        }

        printf("#%d %d\n",test, ans);
    }
    return 0;
}
