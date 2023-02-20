#include <stdio.h>

struct person{
    int x, y, d;
};

person runner[10011];
person catcher;

int MAP[100][100];
int dir[20001];
int n, m, h, k;

bool flag[10001];

int dx[4] = {1, 0, -1, 0};
int dy[4] = {0, 1, 0, -1};

int move(int cnt){
    cnt = cnt%((n-1)*2);
    catcher.d = dir[cnt];

    catcher.x = catcher.x + dx[catcher.d];
    catcher.y = catcher.y + dy[catcher.d];

    int cat = 0;
    int nx = catcher.x;
    int ny = catcher.y;
    for(int i=0; i<3; ++i){
        nx += dx[catcher.d];
        ny +=  dy[catcher.d];
        if(nx< 0 || ny < 0 || nx >= n || ny >= n) continue;

        if(MAP[nx][ny] >0 ){
            cat++;
            flag[MAP[nx][ny]] = false;
            MAP[nx][ny] = 0;
        }
    }

    return cat;
}

void run(){
    for(int i=1; i<=m; ++i){
        if(!flag[i]) continue;
        int lenx = runner[i].x - catcher.x;
        int leny = runner[i].y - catcher.y;
        lenx = lenx > 0 ? lenx : -lenx;
        leny = leny > 0 ? leny : -leny;
        int len = lenx+leny;
        if(len > 3) continue;

        int nx = runner[i].x + dx[runner[i].d];
        int ny = runner[i].y + dy[runner[i].d];
        if(nx == catcher.x && ny == catcher.y) continue;
        if(MAP[runner[i].x][runner[i].y] == i){
            MAP[runner[i].x][runner[i].y] = 0;
        }
        if(nx < 0 || ny < 0 || nx >= n || ny >= n){
            runner[i].d = (runner[i].d + 2) % 4;
            runner[i].x = runner[i].x + dx[runner[i].d];
            runner[i].y = runner[i].y + dy[runner[i].d];
        }
        else{
            runner[i].x = nx;
            runner[i].y = ny;
        }

        if(MAP[runner[i].x][runner[i].y] == 0){
            MAP[runner[i].x][runner[i].y] = i;
        }

    }
}

void tornado(){
    int idx = 0;
    int d = 0;
    for(int i=1; i<=n-1; ++i){
        for(int j=0; j<2; ++j){
            for(int k=0; k<i; ++k){
                dir[idx++] = d;
            }
            d = (d+1) % 4;
        }
    }
    for(int i=1; i<=n-1; ++i){
        dir[idx++] = d;
    }
    d = 2;
    for(int i=1; i<=n-1; ++i){
        dir[idx++] = d;
    }
    d = 1;
    for(int i=n-1; i>=1; --i){
        for(int j=0; j<2; ++j){
            for(int k=0; k<i; ++k){
                dir[idx++] = d;
            }
            d = (d+3) % 4;
        }
    }
}

int main(){
    freopen("input.txt", "r", stdin);

    scanf("%d %d %d %d", &n, &m, &h, &k);

    for(int i=0; i<n; ++i)for(int j=0; j<n; ++j){
        MAP[i][j] = 0;
    }

    catcher.x = n/2;
    catcher.y = n/2;

    for(int i=1; i<=m; ++i){
        int x, y, d;
        scanf("%d %d %d", &x, &y, &d);
        x--, y--, d--;
        MAP[x][y] = i;
        runner[i].x = x;
        runner[i].y = y;
        runner[i].d = d;
        flag[i] = true;
    }

    for(int i=0; i<h; ++i){
        int x, y;
        scanf("%d %d", &x, &y);
        x--, y--;
        MAP[x][y] = -1;
    }

    tornado();

    int cnt = 0;
    while(k--){
        run();
        int val = move(cnt);
        cnt++;
        printf("%d", val * cnt);
    }
}
