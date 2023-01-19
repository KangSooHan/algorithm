#include <stdio.h>

struct Node{
    int data;
    Node *parent;
    Node *left, *right;
};

Node node_pool[10002];

struct queue{
    Node* pool[10002];
    int r, l;

    void init(){
        r = 0, l = 0;
    }

    void insert(Node* node)
    {
        pool[r++] = node;
    }

    Node* pop(){
        return pool[l++];
    }

    bool empty(){
        return r==l;
    }

    int size(){
        return r-l;
    }
};

queue s1, s2;

class BST{
    Node* root;

public:
    BST() = default;

    void init(){
        s1.init();
        s2.init();
        root = nullptr;
        for(int i=0; i<10002; ++i)
        {
            node_pool[i].parent = nullptr;
            node_pool[i].left = nullptr;
            node_pool[i].right = nullptr;
        }
    }

    void insert(int parent, int child)
    {
        node_pool[child].data = child;
        node_pool[parent].data = parent;
        node_pool[child].parent = &node_pool[parent];
        if(node_pool[parent].left == nullptr)
        {
            node_pool[parent].left = &node_pool[child];
        }
        else{
            node_pool[parent].right = &node_pool[child];
        }
    }

    int subtree(int node_num)
    {
        s1.init();
        int cnt=0;
        s1.insert(&node_pool[node_num]);
        cnt++;

        while(!s1.empty())
        {
            Node* node = s1.pop();

            if(node->left != nullptr){
                s1.insert(node->left);
                cnt++;
            }
            if(node->right != nullptr){
                s1.insert(node->right);
                cnt++;
            }
        }
        return cnt;
    }

    int ancestor(int a, int b)
    {
        s1.init();
        s2.init();

        Node* node1 = &node_pool[a];
        Node* node2 = &node_pool[b];

        while(node1 != nullptr)
        {
            s1.insert(node1);
            node1 = node1->parent;
        }
        while(node2 != nullptr)
        {
            s2.insert(node2);
            node2 = node2->parent;
        }

        while(s1.size() != s2.size())
        {
            if(s1.size() > s2.size()) s1.pop();
            else if(s1.size() < s2.size()) s2.pop();
            else break;
        }
        while(!s1.empty() && !s2.empty())
        {
            Node* na = s1.pop();
            Node* nb = s2.pop();
            if(na==nb) return na->data;
        }
        return -1;
    }
};

BST bst {};

int main(){
    freopen("input.txt", "r", stdin);

    int T;
    scanf("%d", &T);
    for(int test=1; test<=T; ++test)
    {
        bst.init();
        int V, E, a, b;
        scanf("%d %d %d %d", &V, &E, &a, &b);

        for(int i=0; i<E; ++i)
        {
            int parent, child;
            scanf("%d %d", &parent, &child);
            bst.insert(parent, child);
        }

        int anc = bst.ancestor(a, b);
        printf("#%d %d %d\n", test, anc, bst.subtree(anc));
    }

}
