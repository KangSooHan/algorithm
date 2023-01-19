#include <stdio.h>

struct Node{
    char data;
    Node *left, *right;
};

Node node_pool[201];

Node* new_node(int node_num, char data)
{
    node_pool[node_num].data = data;
    node_pool[node_num].left = nullptr;
    node_pool[node_num].right = nullptr;
    return &node_pool[node_num];
}

class BST{
    Node* root;

public:
    BST() = default;

    void init(){
        root = nullptr;
    }

    bool insert(int node_num, char data, int left, int right)
    {
        Node* node = new_node(node_num, data);
        node->left = &node_pool[left];
        node->right = &node_pool[right];


        if(data-'0' >= 0&& data-'0'<=9) return false;
        else return true;
    }

    bool insert(int node_num, char data, int left)
    {
        Node* node = new_node(node_num, data);
        node->left = &node_pool[left];

        return false;
    }

    bool insert(int node_num, char data)
    {
        Node* node = new_node(node_num, data);

        if(data-'0' >= 0&& data-'0'<=9) return true;
        else return false;
        
    }
};

BST bst {};


int main()
{
    freopen("input.txt", "r", stdin);
    for(int test=1; test<=10; ++test)
    {
        bst.init();
        int N;
        scanf("%d", &N);

        bool flag = true;
        for(int i=0; i<N; ++i)
        {
            int idx;
            char c;
            scanf("%d %c", &idx, &c);

            if(idx * 2 < N)
            {
                int left, right;
                scanf("%d %d", &left, &right);
                flag *= bst.insert(idx, c, left, right);
            }
            else if(idx*2 == N)
            {
                int left;
                scanf("%d", &left);
                flag *= bst.insert(idx, c, left);
                
            }
            else{
                flag *= bst.insert(idx, c);
            }
        }   

        printf("#%d %d\n", test, flag);
    }

    return 0;
}

