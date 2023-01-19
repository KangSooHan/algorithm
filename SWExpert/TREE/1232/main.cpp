#include <stdio.h>
#include <string>

struct Node{
    char data[10];
    Node *left, *right;
};

Node node_pool[1001];

Node* new_node(int node_num, char data[10])
{
    for(int i=0; i<10; ++i){
        node_pool[node_num].data[i] = data[i];
    }
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

    void insert(int node_num, char data[10], int left, int right)
    {
        Node* node = new_node(node_num, data);
        node->left = &node_pool[left];
        node->right = &node_pool[right];
    }

    void insert(int node_num, char data[10])
    {
        Node* node = new_node(node_num, data);
    }

    int calculate(){
        return traversal_rec(&node_pool[1]);
    }
private:
    int traversal_rec(Node* node) const{
        if(node->data[0] - '0' >= 0 && node->data[0] - '0' <= 9) return std::atoi(node->data);
        int left, right;
        left = traversal_rec(node->left);
        right = traversal_rec(node->right);

        if(node->data[0] == '*') return left * right;
        else if(node->data[0] == '/') return left / right;
        else if(node->data[0] == '+') return left + right;
        else if(node->data[0] == '-') return left - right;
        else return 0;
    };
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
            char str[10];
            scanf("%d%s", &idx, str);
            if(str[0] - '0' >= 0 && str[0] - '0' <= 9)
            {
                bst.insert(idx, str);
            }
            else{
                int left, right;
                scanf("%d %d", &left, &right);
                bst.insert(idx, str, left, right);
            }
        }

        printf("#%d %d\n", test, bst.calculate());
    }

    return 0;
}

