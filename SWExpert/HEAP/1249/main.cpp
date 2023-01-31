#include <stdio.h>
#include <vector>

typedef std::pair<int, int> cord;

int N;
int MAP[101][101];
int visit[101][101];

int res = 9999999;

int dx[4] = {0, 1, 0, -1};
int dy[4] = {1, 0, -1, 0};

struct queue{
    cord pool[100001];
    int r, l;

    void init(){
        r = l = 0 ;
    }

    void push(cord data){
        pool[r++] = data;
    }
    
    cord pop(){
        return pool[l++];
    }

    bool empty(){
        return r==l;
    }
};
queue q;

int main(){
    freopen("input.txt", "r", stdin);

    int T;
    scanf("%d", &T);
    for(int test = 1; test<=T; ++test){
        q.init();
        scanf("%d", &N);
        for(int i=0; i<N; ++i){
            for(int j=0; j<N; ++j){
                char c;
                scanf(" %c", &c);
                MAP[i][j] = c - '0';
                visit[i][j] = 9999999;
            }
        }
        visit[0][0] = 0;
        q.push(std::make_pair(0, 0));
        while(!q.empty()){
            cord cur = q.pop();

            for(int d=0; d<4; ++d){
                int nx = cur.first + dx[d];
                int ny = cur.second + dy[d];
                if(nx < 0 || ny < 0 || nx >= N || ny >= N) continue;
                
                if(visit[nx][ny] > visit[cur.first][cur.second] + MAP[nx][ny]){
                    visit[nx][ny] = visit[cur.first][cur.second] + MAP[nx][ny];
                    q.push(std::make_pair(nx, ny));
                }
            }
        }
        printf("#%d %d\n", test, visit[N-1][N-1]);
    }
}