#include <stdio.h>
#include <vector>

using namespace std;

struct queue{
    pair<int, pair<int, int>> pool[250];
    int r, l;
    
    void init(){r=l=0;}
    void push(pair<int, pair<int, int>> data){ pool[r++] = data;}
    pair<int, pair<int, int>> pop(){return pool[l++];}
    bool empty(){return r==l;}
};

queue q;

int n, m;
int MAP[16][16];
int visit[16][16];

int dx[4] = {-1, 0, 0, 1};
int dy[4] = {0, -1, 1, 0};

vector<pair<int, int>> conv;
vector<pair<int, int>> per;

bool flag[31];
void move(int idx){
    if(flag[idx]) return;
    for(int i=0; i<16; ++i){
        for(int j=0; j<16; ++j){
            visit[i][j] = 0;
        }
    }
    q.init();

    for(int d=0; d<4; ++d){
        int nx = per[idx].first + dx[d];
        int ny = per[idx].second + dy[d];
        if(nx < 0 || ny < 0 || nx>=n || ny >=n) continue;
        q.push(make_pair(d, make_pair(nx, ny)));
        visit[nx][ny] = 1;
    }

    while(!q.empty()){
        pair<int, pair<int, int>> cur = q.pop();
        if(conv[idx].first == cur.second.first && conv[idx].second == cur.second.second){
            per[idx].first += dx[cur.first];
            per[idx].second += dy[cur.first];
            if(per[idx].first == conv[idx].first && per[idx].second == conv[idx].second){
                flag[idx] = true;
                MAP[per[idx].first][per[idx].second] = -1;
                return;
            }
        }

        for(int d=0; d<4; ++d){
            int nx = cur.second.first + dx[d];
            int ny = cur.second.second + dy[d];
            if(nx < 0 || ny < 0 || nx>=n || ny >=n) continue;
            if(visit[nx][ny]==1) continue;
            visit[nx][ny] = 1;
            q.push(make_pair(cur.first, make_pair(nx, ny)));
        }
    }
}

void alloc(int time){
    int max = 250;
    for(int i=0; i<16; ++i){
        for(int j=0; j<16; ++j){
            visit[i][j] = 0;
        }
    }
    q.init();
    visit[conv[time].first][conv[time].second] = 1;
    q.push(make_pair(0, conv[time]));
    int cnt = -1;
    int x = 16, y = 16;
    while(!q.empty()){
        pair<int, pair<int, int>> cur = q.pop();
        if(MAP[cur.second.first][cur.second.second] == 1){
            if (x > cur.second.first) {
                x = cur.second.first;
                y = cur.second.second;
            }
            else if(x == cur.second.first){
                if(y > cur.second.second){
                    x = cur.second.first;
                    y = cur.second.second;
                }
            }
        }
        for(int d=0; d<4; ++d){
            int nx = cur.second.first + dx[d];
            int ny = cur.second.second + dy[d];

            if(nx < 0 || ny < 0 || nx>=n || ny >= n) continue;
            if(visit[nx][ny] == 1) continue;
            if(MAP[nx][ny] == 1){
                if(cnt == -1) cnt = cur.first+1;
                if(cnt != cur.first+1) break;
            }
            visit[nx][ny] = 1;
            q.push(make_pair(cur.first+1, make_pair(nx, ny)));
        }
    }
    MAP[x][y] = -1;
    per.emplace_back(make_pair(x, y));
}

int main(){
    freopen("input.txt", "r", stdin);

    scanf("%d %d", &n, &m);

    for(int i=0; i<n; ++i){
        for(int j=0; j<n; ++j){
            scanf("%d", &MAP[i][j]);
        }
    }

    for(int i=0; i<m; ++i){
        int x, y;
        scanf("%d %d", &x, &y);
        x--; y--;
        conv.emplace_back(make_pair(x, y));
        flag[i] = false;
    }

    int time = 1;
    while(true){
        for(int t=0; t<per.size(); ++t){
            move(t);
        }
        if(time <= m){
            alloc(time-1);
        }
        else{
            bool bflag = true;
            for(int i=0; i<per.size(); ++i){
                bflag *= flag[i];
            }
            if(bflag) break;
        }
        time++;
    }
    printf("%d\n", time);
} 
