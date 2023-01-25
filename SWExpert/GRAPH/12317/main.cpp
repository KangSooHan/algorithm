#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>

unsigned int seed = 12345;
unsigned int pseudo_rand(int max) {
	seed = ((unsigned long long)seed * 1103515245 + 12345) & 0x7FFFFFFF;
	return seed % max;
}

#define MAX_N (40)
#define MAX_K (98)
#define MIN_N (2)
#define MAX_CHILD (5)

struct Node{
    int num;
    Node* child[5];
    int child_cnt;
};

Node node_pool[100];
int node_cnt;

struct stack{
    int pool[101];
    int r;

    void init(){
        r=0;
    }
    void push(int data){
        pool[r++] = data;
    }
    int pop(){
        return pool[--r];
    }
    bool empty(){
        return r==0;
    }
};

stack s;

class Tree{
public:
    Tree() = default;

    void init(){
        node_cnt = 0;
        for(int i=0; i<100; ++i){
            node_pool[i].child_cnt = 0;
            node_pool[i].num = i;
        }
    }

    void insert(int p, int c){
        node_pool[p].child[node_pool[p].child_cnt++] = &node_pool[c];
    }

    int dfs(int t)
    {
        s.push(t);

        while(!s.empty())
        {
            int cur = s.pop();
            if(cur > t) return cur;
            for(int i=node_pool[cur].child_cnt-1; i>=0; --i)
            {
                s.push(node_pool[cur].child[i]->num);
            }
        }
        return -1;
    }
};

Tree tree {};

void dfs_init(int N, int path[MAX_N][2])
{
    tree.init();
    for(int i=0; i<N-1; ++i)
    {
        tree.insert(path[i][0], path[i][1]);
    }
}
int dfs(int k){
    s.init();
    return tree.dfs(k);
}

int p[MAX_K+2];
int c[MAX_K+2];
int path[MAX_N][2];
void makeTree(int n) {
	for (int i = 1; i < MAX_K+2; ++i) {
		p[i] = c[i] = -1;
	}
	c[pseudo_rand(MAX_K + 1) + 1] = 0;
	for (int i = 0; i < n; ++i) {
		int pi = pseudo_rand(MAX_K + 1) + 1;
		while (c[pi] < 0 || c[pi] >= MAX_CHILD) {
			++pi;
			if (pi == MAX_K + 2)
				pi = 1;
		}
		int ci = pseudo_rand(MAX_K + 1) + 1;
		while (c[ci] >= 0) {
			++ci;
			if (ci == MAX_K + 2)
				ci = 1;
		}
		p[ci] = pi;
		++c[pi];
		c[ci] = 0;
	}
	bool check[MAX_K + 2] = { false };
	for (int i = 0; i < n; ++i) {
		int e = pseudo_rand(MAX_K + 1) + 1;
		while (check[e] || c[e] < 0 || p[e] == -1) {
			++e;
			if (e == MAX_K + 2)
				e = 1;
		}
		check[e] = true;
		path[i][0] = p[e];
		path[i][1] = e;
	}
}

int main() {
	setbuf(stdout, NULL);
	int T;
	freopen("input.txt", "r", stdin);
	scanf("%d", &T);

	int totalScore = 0;
	for (int tc = 1; tc <= T; tc++) {
		int n, q;

		scanf("%d %d %d", &n, &q, &seed);

		makeTree(n - 1);
		dfs_init(n, path);

		bool check[MAX_K + 2] = { false };
		int score = 100;
		for (int i = 0; i < q; ++i) {
			int k, ret, correct;

			scanf("%d", &k);

			ret = dfs(k);

			scanf("%d", &correct);

			if (ret != correct)
				score = 0;
		}
		printf("#%d : %d\n", tc, score);
		totalScore += score;
	}
	printf("#total score : %d\n", totalScore / T);

	return 0;
}
