#include <stdio.h>

int n, m, k, c;

int MAP[21][21];
int change[21][21];
int dead[21][21];

int dx[4] = {-1, 0, 1, 0};
int dy[4] = {0, -1, 0, 1};

int cx[4] = {-1, -1, 1, 1};
int cy[4] = {-1, 1, -1, 1};

void grow(){
    for(int i=0; i<n; ++i){
        for(int j=0; j<n; ++j){
            if(MAP[i][j] <= 0) continue;
            for(int d=0; d<4; ++d){
                int nx = i+dx[d], ny=j+dy[d];
                if(nx < 0 || ny < 0 || nx >= n || ny >= n) continue;
                if(dead[nx][ny] > 0) continue;
                if(MAP[nx][ny] > 0) MAP[i][j]++;
            }
        }
    }
}

void breed(){
    for(int i=0; i<n; ++i){
        for(int j=0; j<n; ++j){
            if(MAP[i][j] <= 0) continue;
            int cnt=0;
            for(int d=0; d<4; ++d){
                int nx = i+dx[d], ny=j+dy[d];
                if(nx < 0 || ny < 0 || nx >= n || ny >= n) continue;
                if(dead[nx][ny] > 0) continue;
                if(MAP[nx][ny] == 0) cnt++;
            }
            for(int d=0; d<4; ++d){
                int nx = i+dx[d], ny=j+dy[d];
                if(nx < 0 || ny < 0 || nx >= n || ny >= n) continue;
                if(dead[nx][ny] > 0) continue;
                if(MAP[nx][ny] == 0) change[nx][ny] += MAP[i][j]/cnt;
            }
        }
    }

    for(int i=0; i<n; ++i){
        for(int j=0; j<n; ++j){
            MAP[i][j] += change[i][j];
            change[i][j] = 0;
        }
    }
}

int spread(){
    int max = 0;
    int mx=0, my=0;
    for(int i=0; i<n; ++i){
        for(int j=0; j<n; ++j){
            if(MAP[i][j] <= 0) continue;
            int cnt=MAP[i][j];
            for(int d=0; d<4; ++d){
                int nx = i, ny=j;
                for(int l=0; l<k; ++l){
                    nx += cx[d];
                    ny += cy[d];
                    if(nx < 0 || ny < 0 || nx >= n || ny >= n) break;
                    if(MAP[nx][ny] < 0) break;
                    cnt += MAP[nx][ny];
                    if(MAP[nx][ny] == 0) break;
                }
            }
            if(max < cnt){
                max = cnt;
                mx = i, my = j;
            }
        }
    }


    MAP[mx][my] = 0;
    dead[mx][my] = c+1;
    for(int d=0; d<4; ++d){
        int nx = mx, ny = my;
        for(int l=0; l<k; ++l){
            nx += cx[d];
            ny += cy[d];
            if(nx < 0 || ny < 0 || nx >= n || ny >= n) break;
            dead[nx][ny] = c+1;
            if(MAP[nx][ny] <= 0) break;
            MAP[nx][ny] = 0;
        }
    }
    return max;
}

void next(){
    for(int i=0; i<n; ++i){
        for(int j=0; j<n; ++j){
            dead[i][j]--;
        }
    }
}

int main(){
    freopen("input.txt", "r", stdin);
    scanf("%d %d %d %d", &n, &m, &k, &c);

    for(int i=0; i<n; ++i){
        for(int j=0; j<n; ++j){
            scanf("%d", &MAP[i][j]);
        }
    }

    int ans=0;


    while(m--){
        grow();
        breed();
        ans += spread();
        next();
    }
    printf("%d\n", ans);
}
