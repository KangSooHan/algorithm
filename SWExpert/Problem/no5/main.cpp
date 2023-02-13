#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>

#define CMD_INIT 100
#define CMD_UPDATE_SCORE 200
#define CMD_UNION_TEAM 300
#define CMD_GET_SCORE 400

#include <vector>

struct Node{
    int score;
    Node* parent;
};

Node node_pool[2000005];
int node_cnt;

Node* new_node(){
    node_pool[node_cnt].score = 0;
    node_pool[node_cnt].parent = nullptr;
    return &node_pool[node_cnt++];
}

void init(int N){
    node_cnt = 1;
    for(int i=0; i<N; ++i){
        Node* node = new_node();
    }

    for(int i=1; i<=N; ++i){
        Node* root = new_node();
        node_pool[i].parent = root;
    }
}

void updateScore(int mWinnerID, int mLoserID, int mScore){
    Node* wNode = &node_pool[mWinnerID];
    Node* lNode = &node_pool[mLoserID];

    while(wNode->parent != nullptr){
        wNode = wNode->parent;
    }
    while(lNode->parent != nullptr){
        lNode = lNode->parent;
    }

    wNode->score += mScore;
    lNode->score -= mScore;
}

void unionTeam(int mPlayerA, int mPlayerB){
    Node* aNode = &node_pool[mPlayerA];
    Node* bNode = &node_pool[mPlayerB];

    int acnt=0;
    while(aNode->parent != nullptr){
        acnt++;
        aNode = aNode->parent;
    }

    int bcnt=0;
    while(bNode->parent != nullptr){
        bcnt++;
        bNode = bNode->parent;
    }

    if(acnt > bcnt){
        bNode->parent = aNode;
        bNode->score -= aNode->score;
    }
    else{
        aNode->parent = bNode;
        aNode->score -= bNode->score;

    }
}

int getScore(int mID){
    Node* node = &node_pool[mID];

    int score = 0;
    while(node->parent != nullptr){
        node = node->parent;
        score += node->score;
    }
    return score;
}

void check(){
    for(int i=1; i<=6; ++i){
        printf("%d->%d\t", i, getScore(i));
    }
    printf("\n");
}

static bool run()
{
	int queryCnt, cmd;
	int ans, res;
	bool okay = false;

	scanf("%d", &queryCnt);
	for (int i = 0; i < queryCnt; i++)
	{
		scanf("%d", &cmd);
		switch (cmd)
		{
		case CMD_INIT:
			int N;
			scanf("%d", &N);
			init(N);
			okay = true;
			break;
		case CMD_UPDATE_SCORE:
			int mWinnerID, mLoserID, mScore;
			scanf("%d%d%d", &mWinnerID, &mLoserID, &mScore);
			updateScore(mWinnerID, mLoserID, mScore);
			break;
		case CMD_UNION_TEAM:
			int mPlayerA, mPlayerB;
			scanf("%d%d", &mPlayerA, &mPlayerB);
			unionTeam(mPlayerA, mPlayerB);
			break;
		case CMD_GET_SCORE:
			int mID;
			scanf("%d", &mID);
			res = getScore(mID);
			scanf("%d", &ans);
			if (ans != res)
			{
				okay = false;
			}
			break;
		}
	}

	return okay;
}

int main()
{
	setbuf(stdout, NULL);
	freopen("input.txt", "r", stdin);

	int T, MARK;
	scanf("%d%d", &T, &MARK);

	for (int tc = 1; tc <= T; tc++)
	{
		int score = run() ? MARK : 0;
		printf("#%d %d\n", tc, score);
	}

	return 0;
}
