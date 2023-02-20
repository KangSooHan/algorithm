#include <stdio.h>
#include <malloc.h>

enum command{
    INIT = 100,
    MOVE = 200,
    CHANGE = 300,
    DIVIDE = 400,
    PINFO = 500,
    VINFO = 600
};
int n, m;

struct Node{
    int id;
    Node* prev, *next;
};

int node_cnt;
Node node_pool[300053];

Node* new_node(int id){
    node_pool[id].id = id;
    node_pool[id].next = nullptr;
    node_pool[id].prev = nullptr;
    return &node_pool[id];
}

int cnt[100001];

class DLL{
    Node *head[100001], *tail[100001];

public:
    DLL() = default;

    void init(){
        node_cnt = 0;
        for(int i=0; i<n; ++i){
            cnt[i] = 0;

            head[i] = &node_pool[100001 + i];
            tail[i] = &node_pool[100001*2 + i];
            head[i]->id = -1;
            tail[i]->id = -1;
            head[i]->next = tail[i];
            head[i]->prev = nullptr;
            tail[i]->next = nullptr;
            tail[i]->prev = head[i];
        }
    }

    void insert(int id, int bnum){
        bnum--;
        cnt[bnum]++;
        Node* node = new_node(id);
        tail[bnum]->prev->next = node;
        node->next = tail[bnum];
        node->prev = tail[bnum]->prev;
        tail[bnum]->prev = node;
    }

    int move(int src, int dst){
        src--, dst--;
        if(cnt[src] == 0) return cnt[dst];

        cnt[dst] += cnt[src];
        cnt[src] = 0;

        head[src]->next->prev = head[dst];
        tail[src]->prev->next = head[dst]->next;
        head[dst]->next->prev = tail[src]->prev;
        head[dst]->next = head[src]->next;

        head[src]->next = tail[src];
        head[src]->prev = nullptr;
        tail[src]->next = nullptr;
        tail[src]->prev = head[src];
        return cnt[dst];
    }

    void pop_front(int bnum){
        head[bnum]->next = head[bnum]->next->next;
        head[bnum]->next->prev = head[bnum];
    }

    void push_front(int bnum, Node* node){
        head[bnum]->next->prev = node;
        node->next = head[bnum]->next;
        node->prev = head[bnum];
        head[bnum]->next = node;
    }

    int change(int src, int dst){
        src--, dst--;
        Node* sNode = head[src]->next; 
        Node* dNode = head[dst]->next; 

        if(sNode!=tail[src] && dNode!=tail[dst]){
            pop_front(src);
            pop_front(dst);
            push_front(dst, sNode);
            push_front(src, dNode);
        }
        else if(sNode==tail[src] && dNode!=tail[dst]){
            pop_front(dst);
            push_front(src, dNode);
            cnt[dst]--;
            cnt[src]++;
        }
        else if(sNode!=tail[src] && dNode==tail[dst]){
            pop_front(src);
            push_front(dst, sNode);
            cnt[src]--;
            cnt[dst]++;
        }
        
        return cnt[dst];
    }

    int divide(int src, int dst){
        src--, dst--;

        int move_cnt = cnt[src]/2;

        cnt[src] -= move_cnt;
        cnt[dst] += move_cnt;

        if(move_cnt==0) return cnt[dst];

        Node* sNode = head[src]->next;
        Node* dNode = head[src];
        while(move_cnt--){
            dNode = dNode->next;
        }

        head[src]->next = dNode->next;
        head[src]->next->prev = head[src];

        dNode->next = head[dst]->next;
        head[dst]->next->prev = dNode;
        head[dst]->next = sNode;
        sNode->prev = head[dst];

        return cnt[dst];
    }

    int pinfo(int pnum){
        return node_pool[pnum].prev->id + 2*node_pool[pnum].next->id;
    }

    int vinfo(int vnum){
        vnum--;
        return head[vnum]->next->id + 2*tail[vnum]->prev->id + 3*cnt[vnum];
    }

    void print(){
        for(int i=0; i<n; ++i){
            printf("%d : ", i);
            Node *node = head[i];
            while(node->next != tail[i]){
                node = node->next;
                printf("%d->", node->id);
            }
            printf("\n");
        }
        printf("\n");
    }


};

DLL dll {};

int main(){
    freopen("input.txt", "r", stdin);
    int q;
    scanf("%d", &q);

    while(q--)
    {
        int cmd, src, dst;
        scanf("%d", &cmd);
        switch(cmd){
            case INIT:
                scanf("%d %d", &n, &m);
                dll.init();
                for(int i=1; i<=m; ++i)
                {
                    int bnum;
                    scanf("%d", &bnum); 
                    dll.insert(i, bnum);
                }
                break;
            case MOVE:
                scanf("%d %d", &src, &dst);
                printf("%d\n", dll.move(src, dst));
                break;
            case CHANGE:
                scanf("%d %d", &src, &dst);
                printf("%d\n", dll.change(src, dst));
                break;
            case DIVIDE:
                scanf("%d %d", &src, &dst);
                printf("%d\n", dll.divide(src, dst));
                break;
            case PINFO:
                int pnum;
                scanf("%d", &pnum);
                printf("%d\n", dll.pinfo(pnum));
                break;
            case VINFO:
                int num;
                scanf("%d", &num);
                printf("%d\n", dll.vinfo(num));
                break;
            default:
                break;
        }
    }

    return 0;
}
