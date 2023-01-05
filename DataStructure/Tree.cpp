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
    int key;
    Node* left, *right;
};

constexpr size_t MAX_NODE = 10000;
int node_count = 0;

Node node_pool[MAX_NODE];

Node* new_node(int x)
{
    node_count++;
    node_pool[node_count].key = x;
    node_pool[node_count].left = nullptr;
    node_pool[node_count].right = nullptr;
    return &node_pool[node_count];
}

class Tree{
    Node* root;

public:
    Tree() = default;

    void init()
    {
        root = nullptr;
        node_count = 0;
    }

    void insert(int x)
    {
        if(root == nullptr)
        {
            root = new_node(x);
        }
        else
        {
            Node* node = new_node(x);
            if(node_count%2==0)
            {
                node_pool[node_count/2].left = node;
            }
            else
            {
                node_pool[node_count/2].right = node;
            }
        }
        return;
    }

    void remove(int x)
    {
        for(int idx=1; idx<=node_count; ++idx)
        {
            if(node_pool[idx].key == x)
            {
                node_pool[idx].key = node_pool[node_count].key;
                if(node_count%2==0)
                {
                    node_pool[node_count/2].left=nullptr;
                }
                else
                {
                    node_pool[node_count/2].right=nullptr;
                }
                node_pool[node_count--].key = 0;
                break;
            }
        }
        return;
    }

    bool find(int x) const
    {
        bool flag=false;
        for(int idx=1; idx<=node_count; ++idx)
        {
            if(node_pool[idx].key == x)
            {
                flag=true;
                break;
            }
        }
        return flag;
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
        if(type == PRE) printf("%d -> ", node->key);
        traversal_rec(node->left, type);
        if(type == IN) printf("%d -> ", node->key);
        traversal_rec(node->right, type);
        if(type == POST) printf("%d -> ", node->key);
    }
};


int main()
{
    int cmd, x;
    Tree tree {};
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
                tree.init();
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
                    tree.insert((rand() % 2000)-1000);
                }
                break;
            case INSERT:
                printf("Type Insert Value\n");
                scanf("%d", &x);
                tree.insert(x);
                break;
            case REMOVE:
                printf("Type Remove Value\n");
                scanf("%d", &x);
                tree.remove(x);
                break;
            case FIND:
                printf("Type Find Value\n");
                scanf("%d", &x);
                tree.find(x) ? printf("Found %d\n", x) : printf("Not Found %d\n", x);
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
                    tree.traversal(x);
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
