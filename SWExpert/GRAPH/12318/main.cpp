#include <stdio.h>
#include <vector>

int MAP[11][11];
int visit[11][11];
int SIZE;

struct queue{
    std::pair<int, int> pool[101];
    int r, l;

    void init(){
        r = l = 0;
    }

    void push(std::pair<int, int> data)
    {
        pool[r++] = data;
    }

    std::pair<int, int> pop()
    {
        return pool[l++];
    }

    bool empty(){
        return r==l;
    }
};

queue q;


int Dx[4] = {0, 1, 0, -1};
int Dy[4] = {1, 0, -1, 0};

void bfs_init(int map_size, int map[10][10])
{
    SIZE = map_size;
    for(int i=0; i<map_size; ++i) for(int j=0; j<map_size; ++j) 
    {
        MAP[i][j] = map[i][j];
        visit[i][j] = -1;
    }
}

int bfs(int x1, int y1, int x2, int y2)
{
    x1--; y1--; x2--; y2--;

    for(int i=0; i<SIZE; ++i) for(int j=0; j<SIZE; ++j)
    {
        visit[i][j] = -1;
    }

    q.init();
    q.push(std::make_pair(x1, y1));
    visit[y1][x1] = 0;

    while(!q.empty())
    {
        std::pair<int, int> cur = q.pop();
        for(int d=0; d<4; ++d)
        {
            int dx = cur.first + Dx[d];
            int dy = cur.second + Dy[d];

            if(dx < 0 || dx >= SIZE || dy < 0 || dy >= SIZE) continue;
            if(visit[dy][dx] >= 0 ) continue;
            if(MAP[dy][dx] == 1) continue;

            q.push(std::make_pair(dx, dy));
            visit[dy][dx] = visit[cur.second][cur.first] + 1;
        } 
    }

    return visit[y2][x2];
}


int test_bfs() {
	int N;
	int map[10][10];
	scanf("%d", &N);
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j) {
			scanf("%d", &map[i][j]);
		}
	}
	bfs_init(N, map);
	int M;
	int score = 100;
	scanf("%d", &M);
	for (int i = 0; i < M; ++i) {
		int x1, y1, x2, y2;
		scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
		int result = bfs(x1, y1, x2, y2);
		int dist;
		scanf("%d", &dist);
		if (result != dist) score = 0;
	}
	return score;
}

int main() {
    freopen("input.txt", "r", stdin);
	setbuf(stdout, NULL);

	printf("#total score : %d\n", test_bfs());

	return 0;
}
