#ifndef _CRT_SECURE_NO_WARNINGS 
#define _CRT_SECURE_NO_WARNINGS 
#endif

#include <stdio.h>
#include <string.h>

#define CMD_MKDIR 1
#define CMD_RM 2
#define CMD_CP 3
#define CMD_MV 4
#define CMD_FIND 5


#include <vector>
#include <string.h>
#include <malloc.h>

#define NAME_MAXLEN 6
#define PATH_MAXLEN 1999
#define NODE_MAXLEN 50000
#define CHILD_MAXLEN 30

struct Node{
    char name[NAME_MAXLEN+1];
    Node* child[CHILD_MAXLEN+1];
    Node* parent;
    int anc_cnt, child_cnt;
};

Node node_pool[NODE_MAXLEN+1];
int node_cnt;

struct queue
{
    Node* pool[NODE_MAXLEN+1];
    int r,l;

    void init(){
        r=l=0;
    }

    void push(Node* node)
    {
        pool[r++] = node;
    }

    Node* pop()
    {
        return pool[l++];
    }

    bool empty(){
        return r==l;
    }

    Node* last(){
        return pool[r-1];
    }
    int size(){
        return r-l;
    }
};

Node* new_node(char name[NAME_MAXLEN+1], Node* parent){
    strcpy(node_pool[node_cnt].name, name);
    node_pool[node_cnt].anc_cnt = 0;

    bool flag = parent==nullptr ? false : true;
    
    for(int i=0; i<CHILD_MAXLEN+1; ++i){
        if(flag && parent->child[i] == nullptr){
            parent->child[i] = &node_pool[node_cnt];
            node_pool[node_cnt].parent = parent;
            flag = false;
        }
        node_pool[node_cnt].child[i] = nullptr;
    }
    return &node_pool[node_cnt++];
};
    

class Tree{
    Node* root;
    queue s;

public:
    void init(){
        node_cnt = 0;
        char name[NAME_MAXLEN+1] = "/";
        root = new_node(name, nullptr);
    }

    void insert(char path[PATH_MAXLEN+1], char name[NAME_MAXLEN+1])
    {
        Node* node;
        find_node(path);
        while(!s.empty()){
            node = s.pop();
            node->anc_cnt++;
        }
        Node* nNode = new_node(name, node);
    }

    void remove(char path[PATH_MAXLEN+1])
    {
        Node* node;
        find_node(path);
        while(!s.empty())
        {
            node = s.pop();
            node->anc_cnt -= s.last()->anc_cnt+1;
        }
        for(int i=0; i<CHILD_MAXLEN+1; ++i){
            if(node->parent->child[i]==node){
                node->parent->child[i] = nullptr;
                break;
            }
        }
    }

    void cp(char srcPath[PATH_MAXLEN+1], char dstPath[PATH_MAXLEN+1])
    {
        find_node(srcPath);
        Node* node = s.last();
        Node* cpNode = new_node(node->name, nullptr);
        cpNode->anc_cnt = node->anc_cnt;
        cp_rec(node, cpNode);

        find_node(dstPath);
        while(!s.empty())
        {
            node = s.pop();
            node->anc_cnt += cpNode->anc_cnt+1;
        }
        for(int i=0; i<CHILD_MAXLEN+1; ++i){
            if(node->child[i] == nullptr){
                node->child[i] = cpNode;
                break;
            }
        }
        cpNode->parent = node;
    }

    int find(char path[PATH_MAXLEN+1]){
        find_node(path);
        return s.last()->anc_cnt;
    }

private:
    void find_node(char path[PATH_MAXLEN+1]){
        Node* node = root;
        s.init();
        s.push(node);
        int cnt=0;
        char name[NAME_MAXLEN+1];
        int size = strlen(path);
        for(int i=1; i<size; ++i)
        {
            if(path[i] == '/'){
                name[cnt] = '\0';
                cnt = 0;
                for(int j=0; j<CHILD_MAXLEN+1; ++j)
                {
                    if(node->child[j] == nullptr) continue;
                    if(strcmp(name, node->child[j]->name)==0){
                        node=node->child[j];
                        s.push(node);
                        break;
                    }
                }
            }
            else{
                name[cnt++] = path[i];
            }
        }
    }

    void cp_rec(Node* node, Node* cpNode){
        for(int i=0; i<CHILD_MAXLEN+1; ++i)
        {
            if(node->child[i] == nullptr) continue;
            Node* ccpNode = new_node(node->child[i]->name, cpNode);
            ccpNode->anc_cnt = node->child[i]->anc_cnt;
            cp_rec(node->child[i], ccpNode);
        }
    }
};


Tree tree {};


void init(int n){
    tree.init();
}
void cmd_mkdir(char path[PATH_MAXLEN + 1], char name[NAME_MAXLEN + 1]){
    tree.insert(path, name);
}
void cmd_rm(char path[PATH_MAXLEN + 1]){
    tree.remove(path);
}
void cmd_cp(char srcPath[PATH_MAXLEN + 1], char dstPath[PATH_MAXLEN + 1]){
    tree.cp(srcPath, dstPath);
}
void cmd_mv(char srcPath[PATH_MAXLEN + 1], char dstPath[PATH_MAXLEN + 1]){
    tree.cp(srcPath, dstPath);
    tree.remove(srcPath);
}
int cmd_find(char path[PATH_MAXLEN + 1]){
    return tree.find(path);
}

static bool run(int m) {

	bool isAccepted = true;
	int cmd;
	char name[NAME_MAXLEN + 1];
	char path1[PATH_MAXLEN + 1], path2[PATH_MAXLEN + 1];

	while (m--) {

		scanf("%d", &cmd);

		if (cmd == CMD_MKDIR) {
			scanf("%s%s", path1, name);
			cmd_mkdir(path1, name);
		}
		else if (cmd == CMD_RM) {
			scanf("%s", path1);
			cmd_rm(path1);
		}
		else if (cmd == CMD_CP) {
			scanf("%s%s", path1, path2);
			cmd_cp(path1, path2);
		}
		else if (cmd == CMD_MV) {
			scanf("%s%s", path1, path2);
			cmd_mv(path1, path2);
		}
		else {
			int ret;
			int answer;

			scanf("%s", path1);
			ret = cmd_find(path1);
			scanf("%d", &answer);

			isAccepted &= (ret == answer);
		}
	}

	return isAccepted;
}

int main(void) {

	int test, T;
	int n, m;

    freopen("input.txt", "r", stdin);

	setbuf(stdout, NULL);

	scanf("%d", &T);

	for (test = 1; test <= T; ++test){

		scanf("%d%d", &n, &m);

		init(n);

		if (run(m)) {
			printf("#%d 100\n", test);
		}
		else {
			printf("#%d 0\n", test);
		}
	}

	return 0;
}
