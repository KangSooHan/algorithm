#include <stdio.h>

int n, m, k;

int MAP[21][21];
int team[21][21];
int visit[21][21];

struct pos{
    int x, y;
};

pos head[6];
pos tail[6];
int score;

struct queue{
    pos pool[401];
    int r, l;

    void init(){r=l=0;}
    void push(pos p){ pool[r++] = p;}
    pos pop(){ return pool[l++];}
    bool empty(){return r==l;}
};

queue q;

int dx[4] = {0, -1, 0, 1};
int dy[4] = {1, 0, -1, 0};

void check_tail(int idx){
    q.init();
    q.push(head[idx]);
    team[head[idx].x][head[idx].y] = idx;

    while(!q.empty()){
        pos cur = q.pop();
        for(int d=0; d<4; ++d){
            int nx = cur.x + dx[d];
            int ny = cur.y + dy[d];
            
            if(nx < 0 || ny < 0 || nx >= n || ny >= n) continue;
            if(MAP[nx][ny] == 0) continue;
            if(team[nx][ny] != -1) continue;
            if(MAP[nx][ny] == 1) continue;
            team[nx][ny] = idx;
            q.push({nx, ny});
            if(MAP[nx][ny] == 3){
                tail[idx] = {nx, ny};
            }
        }
    }
}


void move(){
    for(int i=0; i<m; ++i){
        pos curh = head[i];
        for(int d=0; d<4; ++d){
            int nx = curh.x + dx[d];
            int ny = curh.y + dy[d];

            if(nx < 0 || ny < 0 || nx >= n || ny >= n) continue;
            if(MAP[nx][ny] < 3) continue;
            else{
                head[i] = {nx, ny};
                MAP[curh.x][curh.y] = 2;
                break;
            }
        }

        pos curt = tail[i];
        for(int d=0; d<4; ++d){
            int nx = curt.x + dx[d];
            int ny = curt.y + dy[d];

            if(nx < 0 || ny < 0 || nx >= n || ny >= n) continue;
            if(MAP[nx][ny] != 2) continue;
            if(nx == curh.x && ny == curh.y) continue;
            tail[i] = {nx, ny};
            MAP[curt.x][curt.y] = 4;
            break;
        }
        MAP[head[i].x][head[i].y] = 1;
        MAP[tail[i].x][tail[i].y] = 3;
    }
}

pos arr;

void add_score(pos p){
    for(int i=0; i<n; ++i){
        for(int j=0; j<n; ++j){
            visit[i][j] = 0;
        }
    }
    int idx = team[p.x][p.y];
    q.init();
    q.push(head[idx]);
    visit[head[idx].x][head[idx].y] = 1;

    int cnt = 1;
    while(!q.empty()){
        pos cur = q.pop();
        if(cur.x == p.x && cur.y == p.y){
            score += cnt*cnt;
            pos temp;

            temp = head[idx];
            head[idx] = tail[idx];
            tail[idx] = temp;

            MAP[head[idx].x][head[idx].y] = 1;
            MAP[tail[idx].x][tail[idx].y] = 3;
            return;
        }
        for(int d=0; d<4; ++d){
            int nx = cur.x + dx[d];
            int ny = cur.y + dy[d];
            
            if(nx < 0 || ny < 0 || nx >= n || ny >= n) continue;
            if(MAP[nx][ny] == 0) continue;
            if(MAP[nx][ny] == 4) continue;
            if(visit[nx][ny] == 1) continue;
            if(MAP[nx][ny] == 2) {
                cnt++;
                visit[nx][ny] = 1;
                q.push({nx, ny});
            }
        }
    }

    cnt++;
    score += cnt*cnt;
    pos temp;

    temp = head[idx];
    head[idx] = tail[idx];
    tail[idx] = temp;

    MAP[head[idx].x][head[idx].y] = 1;
    MAP[tail[idx].x][tail[idx].y] = 3;
}

void shoot(int round){
    int dir = ((round / n) + 3)  % 4;

    if(round % n != 0){
        arr = {arr.x + dx[dir], arr.y + dy[dir]};
    }

    int mdir = ((round / n))  % 4;
    int x = arr.x;
    int y = arr.y;
    for(int i=0; i<n; ++i){
        if(MAP[x][y] == 1 || MAP[x][y] == 2 || MAP[x][y] == 3) {
            add_score({x, y});
            break;
        }
        x += dx[mdir];
        y += dy[mdir];
    }
}



int main(){
    freopen("input.txt", "r", stdin);
    scanf("%d %d %d", &n, &m, &k);
    int cnt = 0;
    for(int i=0; i<n; ++i){
        for(int j=0; j<n; ++j){
            scanf("%d", &MAP[i][j]);
            if(MAP[i][j] == 1) head[cnt++] = {i, j};
            team[i][j] = -1;
        }
    }

    score = 0;
    for(int i=0; i<m; ++i){
        check_tail(i);
    }
    int round = 0;
    arr = {0, 0};

    while(round != k){
        move();

        shoot(round);
        round++;
    }
    printf("%d\n", score);

}
