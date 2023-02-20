#include <stdio.h>
#include <vector>

using namespace std;

int N;
int ans;

int MAP[30][30];
int gMAP[30][30];

vector<pair<int, int>> ginfo;

int dx[4] = {-1, 0, 1, 0};
int dy[4] = {0, -1, 0, 1};

struct pos{
    int x, y;
};

struct queue{
    pos pool[901];  
    int r, l;
    void init(){r=l=0;}
    void push(pos data){pool[r++] = data;}
    pos pop(){return pool[l++];}
    bool empty(){return r==l;}
};

queue q;

int DFS(int x, int y, int idx){
    q.init();
    q.push({x, y});
    gMAP[x][y] = idx;

    int behind[900];
    for(int i=0; i<900; ++i){
        behind[i] = 0;
    }

    int cnt = 0;
    while(!q.empty()){
        pos cur = q.pop();
        cnt++;
        for(int d=0; d<4; ++d){
            int nx = cur.x + dx[d];
            int ny = cur.y + dy[d];
            if(nx < 0 || nx>= N || ny < 0 || ny >= N) continue;
            if(gMAP[nx][ny] == 0 ){
                if(MAP[x][y] == MAP[nx][ny]){
                    gMAP[nx][ny] = idx;
                    q.push({nx, ny});
                }
            }
            else{
                if(MAP[x][y] == MAP[nx][ny]) continue;
                behind[gMAP[nx][ny]]++;
            }
        }
    }

    int ret = 0;
    for(int i=0; i<ginfo.size(); ++i){
        ret += (cnt + ginfo[i].first) * MAP[x][y] * ginfo[i].second * behind[i+1];
    }
    ginfo.emplace_back(make_pair(cnt, MAP[x][y]));
    return ret;
}

void group(){
    ginfo.clear();
    for(int i=0; i<N; ++i){
        for(int j=0; j<N; ++j){
            gMAP[i][j] = 0;
        }
    }

    int idx = 1;
    for(int i=0; i<N; ++i){
        for(int j=0; j<N; ++j){
            if(gMAP[i][j] == 0) {
                ans += DFS(i, j, idx);
                idx++;
            }
        }
    }
}

void swap(int &a, int &b){ int temp = a; a = b; b = temp;}



/*
05  06  07  08

15  16  17  18

25  26  27  28

35  36  37  38


05  15  25  35

06  16  26  36

07  17  27  37

08  18  28  38


35  25  15  05

31  21  11  01

32  22  12  02

33  23  13  03
*/

void print(){
    for(int i=0; i<N; ++i){
        for(int j=0; j<N; ++j){
        printf("%d ", MAP[i][j]);
        }
        printf("\n");
    }
        printf("\n");

}



void rot90(int x, int y){
    int temp[14][14];
    for(int i=0; i<N/2; ++i){
        for(int j=0; j<N/2; ++j){
            temp[i][j] = MAP[x+i][y+j];
        }
    }

    for(int i=0; i<N/2; ++i){
        for(int j=i+1; j<N/2; ++j){
            swap(temp[i][j], temp[j][i]);
        }
    }

    for(int i=0; i<N/2; ++i){
        for(int j=0; j<N/4; ++j){
            swap(temp[i][N/2-1-j], temp[i][j]);
        }
    }
    for(int i=0; i<N/2; ++i){
        for(int j=0; j<N/2; ++j){
            MAP[x+i][y+j] = temp[i][j];
        }
    }
}

void rotate(){
    //NEED
    int temp[30];
    for(int i=0; i<N; ++i){
        temp[i] = MAP[N/2][i];
        MAP[N/2][i] = MAP[i][N/2];
    }
    for(int i=0; i<N; ++i){
        MAP[N-i-1][N/2] = temp[i];
    }

    rot90(0, 0);
    rot90(0, N/2+1);
    rot90(N/2+1, 0);
    rot90(N/2+1, N/2+1);
}

int main(){
    freopen("input.txt", "r", stdin);
    scanf("%d", &N);

    ans = 0;
    for(int i=0; i<N; ++i)for(int j=0; j<N; ++j) scanf("%d", &MAP[i][j]);
    for(int i=0; i<1; ++i){
        group();
        if(i==3) break;
        rotate();
    }
    printf("%d\n", ans);
}
