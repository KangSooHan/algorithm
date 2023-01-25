#include <stdio.h>
#include  <vector>
#include <queue>

std::vector<std::pair<int, int>> core;

int MAP[13][13];
int size;
int ans;

int dx[4] = {0, 1, 0, -1};
int dy[4] = {1, 0, -1, 0};

void remove(int idx, int dir, int cnt)
{
    int x = core[idx].first + dx[dir];
    int y = core[idx].second + dy[dir];

    for(int i=0; i<cnt; ++i)
    {
        MAP[x][y] = 0;
        x += dx[dir];
        y += dy[dir];
    }
}

bool check(int x, int y, int dir){
    x += dx[dir];
    y += dy[dir];
    while(x>=0 && y>=0 && x<size && y<size)
    {
        if(MAP[x][y] == 1){
            return false;
        }
        x += dx[dir];
        y += dy[dir];
    }
    return true;
}


int draw(int idx, int dir){
    int x = core[idx].first + dx[dir];
    int y = core[idx].second + dy[dir];
    int cnt=0;
    while(x>=0 && y>=0 && x<size && y<size)
    {
        if(MAP[x][y] == 1){
            remove(idx, dir, cnt);
            return -1;
        }
        MAP[x][y] = 1;
        x += dx[dir];
        y += dy[dir];
        cnt++;
    }
    return cnt;
}

void dfs(int idx, int dir, int len)
{
    if(idx == core.size())
    {
        if(ans > len) ans = len;
        return;
    }
    int cnt = draw(idx, dir);
    if(cnt>=0)
    {
        for(int d=0; d<4; ++d)
        {
            dfs(idx+1, d, len+cnt);
        }
    }
    remove(idx, dir, cnt);
}


int main(){
    freopen("input.txt", "r", stdin);
    
    int T;
    scanf("%d", &T);
    for(int test=1; test<=T; ++test)
    {
        ans = 9999999;
        core.clear();
        scanf("%d", &size);

        for(int i=0; i<size; ++i)for(int j=0; j<size; ++j){
            scanf("%d", &MAP[i][j]);
        }

        for(int i=0; i<size; ++i)for(int j=0; j<size; ++j)
        {
            if(MAP[i][j] == 1){
                bool flag = true;
                for(int d=0; d<4; ++d)
                {
                    if(check(i, j, d) == true)
                    {
                        flag = false;
                        break;
                    }
                }
                if(!flag) core.emplace_back(std::make_pair(i, j));
            }
        }

        int max = size;
        for(int d=0; d<4; ++d)
        {
            dfs(0, d, 0);
        }
        printf("#%d %d\n", test, ans);
    }
    return 0;
}
