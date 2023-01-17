#include <stdio.h>
#include <pcl/io/pcd_io.h>

// Structure to represent node of kd tree
struct Node
{
	std::vector<float> point;
	int id;
	Node* left;
	Node* right;
};


constexpr size_t MAX_NODE=100000;
Node node_pool[MAX_NODE];

int node_cnt;

Node* new_node(std::vector<float> point, int id){
    node_pool[node_cnt].id = id;
    node_pool[node_cnt].point = point;
    node_pool[node_cnt].left = nullptr;
    node_pool[node_cnt].right = nullptr;
    return &node_pool[node_cnt++];
}

class KdTree
{

public:
    KdTree() = default;
	Node* root;

    void init(){
        node_cnt=0;
        root = nullptr;
    }
	void insert(std::vector<float> point, int id)
	{
        if(root == nullptr) root = new_node(point, id);
        else{
            root = insert_rec(root, point, id, 0);
        }
	}

	// return a list of point ids in the tree that are within distance of target
	std::vector<int> search(std::vector<float> target, float distanceTol)
	{
		std::vector<int> ids;
        search_rec(target, root, 0, distanceTol, ids);
		return ids;
	}

private:
    Node* insert_rec(Node* node, std::vector<float> point, int id, int depth) const{
        if(node == nullptr){
            return new_node(point, id);
        }

        if(point[depth%node->point.size()] > node->point[depth%node->point.size()]){
            node->right = insert_rec(node->right, point, id, depth+1);
        }
        else if(point[depth%node->point.size()] < node->point[depth%node->point.size()]){
            node->left = insert_rec(node->left, point, id, depth+1);
        }
        else{
            if(point[(depth+1)%node->point.size()] > node->point[(depth+1)%node->point.size()]){
                node->right = insert_rec(node->right, point, id, depth+1);
            }
            else if(point[(depth+1)%node->point.size()] < node->point[(depth+1)%node->point.size()]){
                node->left = insert_rec(node->left, point, id, depth+1);
            }
        }
        return node;
    }

    void search_rec(std::vector<float> target, Node* node, int depth, float distanceTol, std::vector<int>& ids)
    {
        if (node==nullptr) return;
        bool flag=true;
        for(int i=0; i<node->point.size(); ++i){
            if(node->point[i] - target[i] >= -distanceTol && node->point[i] - target[i] <= distanceTol)
                continue;
            flag=false;
        }

        if(flag){
            float distance=0;
            for(int i=0; i<node->point.size(); ++i){
                distance += (node->point[i] - target[i]) * (node->point[i] - target[i]);
            }
            distance = sqrt(distance);
            if(distance <= distanceTol)
                ids.push_back(node->id);
        }

        if(node->point[depth%node->point.size()] - target[depth%node->point.size()] >= -distanceTol)
            search_rec(target, node->left, depth+1, distanceTol, ids);
        if(node->point[depth%node->point.size()] - target[depth%node->point.size()] <= distanceTol)
            search_rec(target, node->right, depth+1, distanceTol, ids);
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
