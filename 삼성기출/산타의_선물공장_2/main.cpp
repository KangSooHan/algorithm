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

struct Node{
    int val;
    Node *prev, *next;
};

int pv[100001];

Node node_pool[300003];

int node_cnt;

Node* new_node(int val){
    node_pool[node_cnt].val = val;
    node_pool[node_cnt].prev = nullptr;
    node_pool[node_cnt].next = nullptr;
    return &node_pool[node_cnt++];
}

class DLL{
    Node *head[100001], *tail[100001];

public:
    DLL() = default;

    void init(int n){
        for(int i=0; i<n; ++i){
            head[i] = (Node*)malloc(sizeof(Node));
            tail[i] = (Node*)malloc(sizeof(Node));
            head[i]->next = tail[i];
            head[i]->prev = nullptr;
            tail[i]->next = nullptr;
            tail[i]->prev = head[i];
        }
        node_cnt = 0;
    }

    void insert(int val, int vnum){
        Node* node = new_node(val);
        head[vnum]->val++;
        node->next = tail[vnum];
        node->prev = tail[vnum]->prev;
        tail[vnum]->prev->next = node;
        tail[vnum]->prev = node;

        pv[val] = vnum;
    }

    int move(int src, int dst){
        if(head[src]->next == tail[src]) head[dst]->val;
        Node* srcNodeH = head[src]->next;
        Node* srcNodeT = tail[src]->prev;

        Node* node = head[src]->next;

        while(node!=srcNodeT){
            pv[node->val] = dst;
            node = node->next;
        }

        srcNodeT->next = head[dst]->next;
        srcNodeH->prev = head[dst];
        head[dst]->next->prev = srcNodeT;
        head[dst]->next = srcNodeH;
        head[dst]->val += head[src]->val;

        head[src]->next = tail[src];
        tail[src]->prev = head[src];
        head[src]->val = 0;

        return head[dst]->val;
    }

    int change(int src,int dst){
        if(head[src]->next != tail[src] && head[dst]->next != tail[dst]){
            Node* srcNode1 = head[src]->next;
            Node* srcNode2 = srcNode1->next;


            Node* dstNode1 = head[dst]->next;
            Node* dstNode2 = dstNode1->next;

            pv[srcNode1->val] = dst;
            pv[dstNode1->val] = src;

            srcNode2->prev = dstNode1;
            dstNode2->prev = srcNode1;

            srcNode1->next = dstNode2;
            dstNode1->next = srcNode2;

            srcNode1->prev = head[dst];
            dstNode1->prev = head[src];

            head[src]->next = dstNode1;
            head[dst]->next = srcNode1;
        }

        else if(head[src]->next != tail[src] && head[dst]->next == tail[dst])
        {
            Node* srcNode1 = head[src]->next;
            Node* srcNode2 = srcNode1->next;

            pv[srcNode1->val] = dst;

            tail[dst]->prev = srcNode1;
            srcNode1->next = tail[dst];
            srcNode1->prev = head[dst];
            head[dst]->next = srcNode1;

            head[src]->next = srcNode2;
            srcNode2->prev = head[src];

            head[src]->val--;
            head[dst]->val++;
        }
        else if(head[src]->next == tail[src] && head[dst]->next != tail[dst])
        {
            Node* dstNode1 = head[dst]->next;
            Node* dstNode2 = dstNode1->next;

            pv[dstNode1->val] = src;

            tail[src]->prev = dstNode1;
            dstNode1->next = tail[src];
            dstNode1->prev = head[src];
            head[src]->next = dstNode1;

            head[dst]->next = dstNode2;
            dstNode2->prev = head[dst];

            head[src]->val++;
            head[dst]->val--;
            
        }

        return head[dst]->val;
    }

    int divide(int src,int dst){
        int size = head[src]->val/2;
        if(size == 0) return head[dst]->val;

        Node* nodeH = head[src]->next;
        Node* nodeT = head[src];
        for(int i=0; i<size; ++i)
        {
            nodeT = nodeT->next;
            pv[nodeT->val] = dst;
        }
        Node* nodeN = nodeT->next;

        nodeH->prev = head[dst];
        nodeT->next = head[dst]->next;
        head[dst]->next->prev = nodeT;
        head[dst]->next = nodeH;

        head[dst]->val += size;
        head[src]->val -= size;

        nodeN->prev = head[src];
        head[src]->next = nodeN;

        return head[dst]->val;

    }

    int pinfo(int num){
        Node* node = head[pv[num]]->next;
        while(node->val != num){
            node = node->next;
        }

        int a, b;
        a = node->prev == head[pv[num]] ? -1 : node->prev->val;
        b = node->next == tail[pv[num]] ? -1 : node->next->val;
        return a + 2*b;
    }

    int vinfo(int num){
        int a, b, c;
        a = head[num]->next == tail[num] ? -1 : head[num]->next->val;
        
        b = tail[num]->prev == head[num] ? -1 : tail[num]->prev->val;
        
        c = head[num]->val;
        return a + 2*b + 3*c;
    }

    void print(int n){
        for(int i=0; i<n; ++i){
            printf("i : ");
            Node* node = head[i];
            print_rec(head[i]);
        }
                printf("\n");
    }

private:
    void print_rec(Node* node){
        if(node->next->next == nullptr) return;
        printf("%d->", node->next->val);
        print_rec(node->next);
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
                int n, m;
                scanf("%d %d", &n, &m);
                dll.init(n);
                for(int i=1; i<=m; ++i)
                {
                    int vnum;
                    scanf("%d", &vnum); 
                    dll.insert(i, --vnum);
                }
                break;
            case MOVE:
                scanf("%d %d", &src, &dst);
                printf("%d\n", dll.move(--src, --dst));
                break;
            case CHANGE:
                scanf("%d %d", &src, &dst);
                printf("%d\n", dll.change(--src, --dst));
                break;
            case DIVIDE:
                scanf("%d %d", &src, &dst);
                printf("%d\n", dll.divide(--src, --dst));
                break;
            case PINFO:
                int pnum;
                scanf("%d", &pnum);
                printf("%d\n", dll.pinfo(pnum));
                break;
            case VINFO:
                int num;
                scanf("%d", &num);
                printf("%d\n", dll.vinfo(--num));
                break;
            default:
                break;
        }
    }

    return 0;
}
