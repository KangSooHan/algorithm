#include <stdio.h>
#include <vector>

using namespace std;

int N;

struct queue{
    int pool[100002];
    int r, l;
    void init(){r=l=0;}
    void push(int data){pool[r++] = data;}
    int pop(){return pool[l++];}
    bool empty(){return r==l;}
};

queue q;

struct Node{
    int depth;
    int anc[17];
    vector<int> child;
};

Node node_pool[100002];
int node_cnt;

void new_node(int parent){
    node_pool[node_cnt].depth = node_pool[parent].depth+1;
    for(int i=0; i<17; ++i){
        node_pool[node_cnt].anc[i] = 0;
    }
    node_pool[node_cnt].anc[0] = parent;
    node_pool[node_cnt].child.clear();
    node_pool[parent].child.emplace_back(node_cnt);
    node_cnt++;
}

class Tree{
    Node* root;
public:
    Tree() = default;
    void init(){
        node_cnt = 1;
        new_node(0);
    }

    void push(int parent){
        new_node(parent);
    }

    void connect(){
        for(int k=1; k<17; ++k){
            for(int cur=1; cur<node_cnt; ++cur){
                node_pool[cur].anc[k] = node_pool[node_pool[cur].anc[k-1]].anc[k-1];
            }
        }
    }

    long long int bfs(){
        q.init();
        q.push(1);
        long long int ans = 0;
        int prev = 1;
        while(!q.empty()){
            int cur = q.pop();
            int anc = lca(prev, cur);
            ans += node_pool[prev].depth + node_pool[cur].depth - node_pool[anc].depth *2;
            prev = cur;
            for(int i=0; i<node_pool[cur].child.size(); ++i){
                q.push(node_pool[cur].child[i]);
            }
        }

        return ans;
    }

    int lca(int a, int b){
        if(node_pool[a].depth < node_pool[b].depth){
            int temp = a;
            a = b;
            b = temp;
        }

        int diff = node_pool[a].depth - node_pool[b].depth;

        for(int i=0; diff; ++i){
            if(diff%2==1) a = node_pool[a].anc[i];
            diff/=2;
        }

        if(a!=b){
            for(int i=16; i>=0; --i){
                if(node_pool[a].anc[i] != 0 && node_pool[a].anc[i] != node_pool[b].anc[i]){
                    a = node_pool[a].anc[i];
                    b = node_pool[b].anc[i];
                }

            }
            a = node_pool[a].anc[0];
        }

        return a;
    }
};

Tree tree {};

int main(){
    freopen("input.txt", "r", stdin);
    int T;
    scanf("%d", &T);
    for(int test=1; test<=T; ++test)
    {
        scanf("%d", &N);
        tree.init();
        for(int i=2; i<=N; ++i){
            int parent;
            scanf("%d", &parent);
            tree.push(parent);
        }
        tree.connect();

        printf("#%d %lld\n",test, tree.bfs());

    }
    return 0;
}
