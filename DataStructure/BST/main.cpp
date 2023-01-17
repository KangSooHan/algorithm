#include <stdio.h>
#include <cstdlib>

enum CMD
{
    INIT=0,
    RANDINSERT,
    INSERT,
    REMOVE,
    FIND,
    TRAVERSAL
};

enum TYPE
{
    PRE=0,
    IN,
    POST
};

static const char *enumStr [] = 
{"INIT", "RANDINSERT", "INSERT", "REMOVE", "FIND", "TRAVERSAL"};


struct Node{
    int val;
    Node* left, *right;
};

constexpr size_t MAX_NODE = 100000;
Node node_pool[MAX_NODE];

int node_cnt;

Node* new_node(int x){
    node_pool[node_cnt].val = x;
    node_pool[node_cnt].left = nullptr;
    node_pool[node_cnt].right = nullptr;
    return &node_pool[node_cnt++];
}

class BST{
    Node *root;

public:
    BST() = default;

    void init(){
        node_cnt=0;
        root = nullptr;
    }

    void insert(int x){
        // 재귀적 방법
        root = insert_rec(root, x);

        // 비재귀적 방법
        /*
        if(root==nullptr){
            root = new_node(x);
            return;
        }

        for(Node* node = root; node->val!=x;){
            Node** child = x<node->val ? &node->left : &node->right;
            if(*child == nullptr){
                *child = new_node(x);
                return ;
            }
            node = *child;
        }
        */
    }

    void remove(int x){
        root = remove_rec(root, x);

        // 비재귀적 방법
        /*
        Node * parent = nullptr;
        Node * node = root;
        while(node != nullptr && node->val != x){
            parent = node;
            node = x < node->val ? node->left : node->right;
        }

        if(node == nullptr){
            return;
        }

        if(node->left == nullptr && node->right ==nullptr){
            if(parent==nullptr)
                root = nullptr;
            else
                (node == parent->left ? parent->left : parent->right) = nullptr;
        }
        else if(node->left == nullptr)
            *node = *node->right;
        else if(node->right == nullptr)
            *node = *node->left;
        else{
            parent = node;
            Node* successor = node->right;
            while(successor->left != nullptr){
                parent = successor;
                successor = successor->left;
            }
            node->val = successor->val;
            (successor == parent->left ? parent->left : parent->right) = successor->right;
        }
        */

    }

    bool find(int x) const{
        Node* node = root;
        while(node != nullptr){
            if(node->val == x) {
                return true;
            }
            node = x < node->val ? node->left : node->right;
        }
        return false;
    }

    void traversal(int type) const
    {
        printf("Traversal ");
        switch(type)
        {
            case PRE:
                printf("Pre-order\n");
                break;
            case IN:
                printf("In-order\n");
                break;
            case POST:
                printf("Post-order\n");
                break;
            default:
                break;
        }
        traversal_rec(root, type);
        printf("\n");
        return;
    }

private:
    void traversal_rec(Node* node, int type) const
    {
        if(node == nullptr) return;
        if(type == PRE) printf("%d -> ", node->val);
        traversal_rec(node->left, type);
        if(type == IN) printf("%d -> ", node->val);
        traversal_rec(node->right, type);
        if(type == POST) printf("%d -> ", node->val);
    }

    Node* insert_rec(Node* node, int x) const
    {
        if(node == nullptr){
            return new_node(x);
        }

        if(x < node->val) node->left = insert_rec(node->left, x);
        else if(x > node->val) node->right = insert_rec(node->right, x);

        return node;
    }

    Node* remove_rec(Node* node, int x) const
    {
        if(node == nullptr){
            return node;
        }

        if(x < node->val)
            node->left = remove_rec(node->left, x);
        else if(x > node->val)
            node->right = remove_rec(node->right, x);
        else{
            if(node->left == nullptr)
                return node->right;
            else if(node->right == nullptr)
                return node->left;

            const int temp = find_min_val(node->right);
            node->val = temp;
            node->right = remove_rec(node->right, temp);
        }

        return node;
    }

    int find_min_val(Node* node) const{
        while(node->left != nullptr){
            node = node->left;
        }
        return node->val;
    }
};


int main()
{
    int cmd, x;
    BST bst {};
    while(true)
    {
        printf("Please Enter\n");
        for(int i=0; i<=5; ++i)
        {
            printf("%d : %s\n", i, enumStr[i]);
        }
        scanf("%d", &cmd);
        switch(cmd)
        {
            case INIT:
                printf("Init OKAY!\n");
                bst.init();
                break;
            case RANDINSERT:
                printf("How Many Sample Do You Want To Generate Please Type 0 ~ 100\n");
                scanf("%d", &x);
                if(x<0 || x>100)
                {
                    printf("Invalid Input Size! Please Type 0 ~ 100\n");
                    break;
                }
                for(int i=0; i<x; ++i)
                {
                    bst.insert((rand() % 2000)-1000);
                }
                break;
            case INSERT:
                printf("Type Insert Value\n");
                scanf("%d", &x);
                bst.insert(x);
                break;
            case REMOVE:
                printf("Type Remove Value\n");
                scanf("%d", &x);
                bst.remove(x);
                break;
            case FIND:
                printf("Type Find Value\n");
                scanf("%d", &x);
                bst.find(x) ? printf("Found %d\n", x) : printf("Not Found %d\n", x);
                break;
            case TRAVERSAL:
                printf("Type Traversal Value\n");
                printf("0 : Pre-Oreder\n1 :In-Order\n2 : Post-Order\n");
                scanf("%d", &x);
                if(x<0 || x>2)
                {
                    printf("Invalid Traversal Type! Please Type\n0 : Pre-Oreder\n1 :In-Order\n2 : Post-Order\n");
                    break;
                }
                else
                {
                    bst.traversal(x);
                    break;
                }
            default:
                printf("Invalid Command! Please Type\n");
                for(int i=0; i<=5; ++i)
                {
                    printf("%d : %s\n", i, enumStr[i]);
                }
                break;
        }
    }
    return 0;
}
