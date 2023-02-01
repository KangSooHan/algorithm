#include <stdio.h>
#include <vector>
#include <queue>

using namespace std;

struct cmp{
    bool operator()(pair<int, int> const &a,pair<int, int> const &b){
        if(a.second != b.second) return a.second < b.second;
        else return a.first < b.first;
    }
};

priority_queue<pair<int, int>, vector<pair<int, int>>, cmp> pq;


int N, M;
int MAP[16][16];
int visit[16][16];

typedef pair<int, pair<int, int>> info;
vector<info> per;

struct Q{
    info pool[300];
    int r, l;

    void init(){
        r=l=0;
    }

    void push(info data){
        pool[r++] = data;
    }

    info pop(){
        return pool[l++];
    }

    bool empty(){
        return r==l;
    }
};

Q q;

int dx[4] = {-1, 0, 0, 1};
int dy[4] = {0, -1, 1, 0};


int move(int idx){
    for(int i=0; i<N; ++i) for(int j=0; j<N; ++j) visit[i][j] = 0;
    q.init();
    for(int d=0; d<4; ++d){
        int nx = per[idx].second.first + dx[d];
        int ny = per[idx].second.second + dy[d];
        q.push(make_pair(d, make_pair(nx, ny)));
    }

    while(!q.empty()){
        info cur = q.pop();
        
        for(int d=0; d<4; ++d){
            int nx = cur.second.first + dx[d];
            int ny = cur.second.second + dy[d];

            if(nx < 0 || ny < 0 || nx>=N || ny >= N) continue;
            if(visit[nx][ny]==1) continue;
            if(MAP[nx][ny]==-1) continue;
            if(MAP[nx][ny]==1){
                return cur.first;
            }
            visit[nx][ny] = 1;
            q.push(info(cur.first, make_pair(nx, ny)));
        }
        return -1;
    }
}

void alloc(int t){
    for(int i=0; i<N; ++i)for(int j=0; j<N; ++j) visit[i][j] = 0;
    q.init();
    visit[per[t].second.first][per[t].second.second] = 1;
    q.push(make_pair(0, per[t].second));
    int len = -2;
    while(!q.empty())
    {
        info cur = q.pop();

        if(cur.first == len+1) break;

        for(int d=0; d<4; ++d)
        {
            int nx = cur.second.first + dx[d];
            int ny = cur.second.second + dy[d];
            if(nx < 0 || ny < 0 || nx>=N || ny >= N) continue;
            if(visit[nx][ny]==1) continue;
            if(MAP[nx][ny]==-1) continue;
            if(MAP[nx][ny]==1){
                len = cur.first+1;
                pq.push(cur.second);
            }
            visit[nx][ny] = 1;
            q.push(info(cur.first+1, make_pair(nx, ny)));
        }
    }
    MAP[pq.top().first][pq.top().second] = -1;
    while(!pq.empty()){
        pq.pop();
    }
    printf("%d %d", pq.top().first, pq.top().second);
}

int main(){
    freopen("input.txt", "r", stdin);
    scanf("%d %d", &N, &M);

    for(int i=0; i<N; ++i){
        for(int j=0; j<N; ++j){
            scanf("%d", &MAP[i][j]);
        }
    }


    for(int i=0; i<M; ++i){
        pair<int, int> cur;
        scanf("%d %d", &cur.first, &cur.second);
        cur.first--; cur.second--;
        per.emplace_back(info(0, cur));
    }

    int time = 0;
    while(true){
        move();
        if(time < M){ 
            alloc(time);
        }
        time++;
        break;
    }
    return 0;
}
