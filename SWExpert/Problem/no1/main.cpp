#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>

struct Node{
    int mId;
    int mTeam;
    Node *prev, *next;
};

Node node_pool[100102];
int pool[100102];
int node_cnt;

Node* new_node(int mId, int mTeam){
    node_pool[node_cnt].mId = mId;
    node_pool[node_cnt].mTeam = mTeam;
    node_pool[node_cnt].next = nullptr;
    node_pool[node_cnt].prev = nullptr;
    return &node_pool[node_cnt++];
}

class DLL{
    Node *head[25], *tail[25];

public:
    DLL() = default;

    void init(){
        node_cnt = 0;
        for(int i=0; i<25; ++i){
            head[i] = new_node(0,i);
            tail[i] = new_node(0,i);
            head[i]->next = tail[i];
            tail[i]->prev = head[i];
        }
        for(int i=0; i<100102; ++i){
            pool[i] = -1;
        }
    }

    void push(int mID, int mTeam, int mScore){
        pool[mID] = node_cnt;
        Node* node = new_node(mID, mTeam);
        Node* hNode = head[mTeam*5 + mScore];

        node->prev = hNode;
        node->next = hNode->next;
        hNode->next->prev = node;
        hNode->next = node;
    }

    void remove(int mID){
        Node* node = &node_pool[pool[mID]];
        node->prev->next = node->next;
        node->next->prev = node->prev;
        node->mTeam = -1;
    }

    void updateS(int mID, int mScore){
        Node* node = &node_pool[pool[mID]];
        Node* hNode = head[node->mTeam * 5 + mScore];

        node->prev->next = node->next;
        node->next->prev = node->prev;

        node->next = hNode->next;
        node->prev = hNode;
        hNode->next->prev = node;
        hNode->next = node;
    }

    void updateT(int mTeam, int mChangeScore){
        Node* node = head[mTeam];

        if(mChangeScore == 0) return;
        else if(mChangeScore < 0){
            int val[5];
            for(int i=0; i<5; ++i){
                int score = i+mChangeScore;
                if(score < 0) score = 0;
                val[i] = score;
            }
            for(int i=0; i<5; ++i){
                if(i == val[i]) continue;
                Node* srcHNode = head[mTeam * 5 + i];
                Node* srcTNode = tail[mTeam * 5 + i];
                if(srcHNode->next == srcTNode) continue;
                Node* dstHNode = head[mTeam * 5 + val[i]];

                srcHNode->next->prev = dstHNode;
                srcTNode->prev->next = dstHNode->next;
                dstHNode->next->prev = srcTNode->prev;
                dstHNode->next = srcHNode->next;

                srcHNode->next = srcTNode;
                srcTNode->prev = srcHNode;
            }
        }
        else{
            int val[5];
            for(int i=0; i<5; ++i){
                int score = i+mChangeScore;
                if(score > 4) score = 4;
                val[i] = score;
            }
            for(int i=4; i>=0; --i){
                if(i == val[i]) continue;
                Node* srcHNode = head[mTeam * 5 + i];
                Node* srcTNode = tail[mTeam * 5 + i];

                if(srcHNode->next == srcTNode) continue;
                Node* dstHNode = head[mTeam * 5 + val[i]];

                srcTNode->prev->next = dstHNode->next;
                srcHNode->next->prev = dstHNode;
                dstHNode->next->prev = srcTNode->prev;
                dstHNode->next = srcHNode->next;

                srcHNode->next = srcTNode;
                srcTNode->prev = srcHNode;
            }
        }
    }

    void print(int mTeam){
        for(int i=0; i<5; ++i){
            printf("%d : ", i);
            Node* node = head[mTeam*5 + i];
            while(node->next != tail[mTeam*5+i]){
                node = node->next;
                printf("%d->",node->mId);
            }
            printf("\n");
        }
        printf("\n");
    }

    int find_best(int mTeam){
        int best = 0;
        for(int i=4; i>=0; --i){
            Node* node = head[mTeam*5+i];
            while(node->next != tail[mTeam*5+i]){
                node = node->next;
                if(best < node->mId) best = node->mId;
            }
            if(best!=0) break;
        }
        return best;
    }
};

DLL dll {};

void init(){ 
    dll.init();
}
void hire(int mID, int mTeam, int mScore){
    dll.push(mID, --mTeam, --mScore);
}
void fire(int mID){
    dll.remove(mID);
}
void updateSoldier(int mID, int mScore){
    dll.updateS(mID, --mScore);
}
void updateTeam(int mTeam, int mChangeScore){
    dll.updateT(--mTeam, mChangeScore);
}
int bestSoldier(int mTeam){
    return dll.find_best(--mTeam);
}

#define CMD_INIT 1
#define CMD_HIRE 2
#define CMD_FIRE 3
#define CMD_UPDATE_SOLDIER 4
#define CMD_UPDATE_TEAM 5
#define CMD_BEST_SOLDIER 6

static bool run()
{
    int numQuery;

    int mID, mTeam, mScore, mChangeScore;

    int userAns, ans;

    bool isCorrect = false;

    scanf("%d", &numQuery);

    for (int i = 0; i < numQuery; ++i)
    {
        int cmd;
        scanf("%d", &cmd);
        switch (cmd)
        {
        case CMD_INIT:
            init();
            isCorrect = true;
            break;
        case CMD_HIRE:
            scanf("%d %d %d", &mID, &mTeam, &mScore);
            hire(mID, mTeam, mScore);
            break;
        case CMD_FIRE:
            scanf("%d", &mID);
            fire(mID);
            break;
        case CMD_UPDATE_SOLDIER:
            scanf("%d %d", &mID, &mScore);
            updateSoldier(mID, mScore);
            break;
        case CMD_UPDATE_TEAM:
            scanf("%d %d", &mTeam, &mChangeScore);
            updateTeam(mTeam, mChangeScore);
            break;
        case CMD_BEST_SOLDIER:
            scanf("%d", &mTeam);
            userAns = bestSoldier(mTeam);
            scanf("%d", &ans);
            if (userAns != ans)
            {
                isCorrect = false;
            }
            break;
        default:
            isCorrect = false;
            break;
        }
    }

    return isCorrect;
}

int main()
{
    setbuf(stdout, NULL);
    freopen("input.txt", "r", stdin);

    int T, MARK;
    scanf("%d %d", &T, &MARK);

    for (int tc = 1; tc <= T; tc++)
    {
        int score = run() ? MARK : 0;
        printf("#%d %d\n", tc, score);
    }

    return 0;
}
