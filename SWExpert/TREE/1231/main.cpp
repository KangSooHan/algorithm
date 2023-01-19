#include <stdio.h>

struct Node{
    char data;
    Node *left, *right;
};

Node node_pool[101];

Node* new_node(int node_num, char data)
{
    node_pool[node_num].data = data;
    node_pool[node_num].left = nullptr;
    node_pool[node_num].right = nullptr;

    return &node_pool[node_num];
}

class BST{
    Node *root;

public:
    BST() = default;

    void init(){
        root = nullptr;
    }


    void insert(int node_num, char data, int left, int right)
    {
        Node* node = new_node(node_num, data);
        node->left = &node_pool[left];
        node->right = &node_pool[right];
    }
    void insert(int node_num, char data, int left)
    {
        Node* node = new_node(node_num, data);
        node->left = &node_pool[left];
    }
    void insert(int node_num, char data)
    {
        Node* node = new_node(node_num, data);
    }

    void inorder()
    {
        traversal_rec(&node_pool[1]);
    }

private:
    void traversal_rec(Node* node) const
    {
        if(node == nullptr) return;

        traversal_rec(node->left);
        printf("%c", node->data);
        traversal_rec(node->right);
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

        for(int i=0; i<N; ++i)
        {
            int idx;
            char c;
            scanf("%d %c", &idx, &c);

            if(idx * 2 < N)
            {
                int left, right;
                scanf("%d %d", &left, &right);
                bst.insert(idx, c, left, right);
            }
            else if(idx*2 == N)
            {
                int left;
                scanf("%d", &left);
                bst.insert(idx, c, left);
                
            }
            else{
                bst.insert(idx, c);
            }
        }   

        printf("#%d ", test);
        bst.inorder();
        printf("\n");
    }

    return 0;
}
