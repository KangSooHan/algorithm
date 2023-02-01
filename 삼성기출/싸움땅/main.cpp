#include <stdio.h>
#include <queue>
#include <vector>

using namespace std;

struct info{
    int x, y, d, s, g, score;
};

int n, m, k;
priority_queue<int> MAP[21][21];
vector<info> person;
int pmap[21][21];


int dx[4] = {-1, 0, 1, 0};
int dy[4] = {0, 1, 0, -1};

void move(int idx){
    info per = person[idx];
    int nx = per.x + dx[per.d];
    int ny = per.y + dy[per.d];

    pmap[per.x][per.y] = 0;

    if(nx < 0 || ny < 0 || ny >= n || nx>=n ) person[idx].d = (person[idx].d + 2) % 4;
    person[idx].x += dx[person[idx].d];
    person[idx].y += dy[person[idx].d];
}

void move1(int idx){
    info per = person[idx];

    while(true){
        int nx = per.x + dx[person[idx].d];
        int ny = per.y + dy[person[idx].d];
        if(nx < 0 || ny < 0 || ny >= n || nx>=n || pmap[nx][ny] != 0) person[idx].d = (person[idx].d + 1) % 4;
        else break;
    }

    person[idx].x += dx[person[idx].d];
    person[idx].y += dy[person[idx].d];
    pmap[person[idx].x][person[idx].y] = idx+1;
}

void get(int idx){
    int x = person[idx].x;
    int y = person[idx].y;
    if(MAP[x][y].empty()) return;
    int gun = MAP[x][y].top();

    if(person[idx].g == 0){
        person[idx].g = MAP[x][y].top();
        MAP[x][y].pop();
    }
    else{
        if(person[idx].g < MAP[x][y].top()){
            MAP[x][y].push(person[idx].g);
            person[idx].g = MAP[x][y].top();
            MAP[x][y].pop();
        }
    }
}

void win(int idx){
    get(idx);
    pmap[person[idx].x][person[idx].y] = idx+1;
}

void lose(int idx){
    info per = person[idx];

    if(per.g != 0){
        MAP[per.x][per.y].push(per.g);
        person[idx].g = 0;
    }
    move1(idx);
    get(idx);
}

void fight(int idx){
    int p1 = idx;
    int p2 = pmap[person[idx].x][person[idx].y] - 1;


    int val = person[p1].s + person[p1].g - person[p2].s - person[p2].g;

    if(val > 0){
        person[p1].score += val;
        lose(p2);
        win(p1);
    }
    else if(val < 0){
        person[p2].score -= val;
        lose(p1);
        win(p2);
    }
    else{
        if(person[p1].s > person[p2].s){
            lose(p2);
            win(p1);
        }
        else{
            lose(p1);
            win(p2);
        }
    }
}

int main(){
    freopen("input.txt", "r", stdin);
    
    scanf("%d %d %d", &n, &m, &k);

    for(int i=0; i<n; ++i){
        for(int j=0; j<n; ++j){
            int gun;
            scanf("%d", &gun);
            if(gun==0) continue;
            MAP[i][j].push(gun);
            pmap[i][j] = 0;
        }
    }

    for(int i=1; i<=m; ++i){
        int x, y, d, s;
        scanf("%d %d %d %d", &x, &y, &d, &s);
        x--; y--;
        info data = {x, y, d, s, 0, 0};
        person.emplace_back(data);
        pmap[x][y] = i;
    }

    while(k--){
        for(int i=0; i<person.size(); ++i){
            move(i);
            if(pmap[person[i].x][person[i].y] == 0){
                get(i);
                pmap[person[i].x][person[i].y] = i+1;
            }
            else{
                fight(i);
            }

        }
    }
    for(int i=0; i<person.size(); ++i){
        printf("%d ", person[i].score);
    }
    printf("\n");
}
