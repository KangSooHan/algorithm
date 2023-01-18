#include <stdio.h>
#include <malloc.h>

#define MAX_NODE 10000

enum { ADD_HEAD = 1, ADD_TAIL, ADD_NUM, REMOVE, PRINT, END = 99 };

struct Node {
	int data;
	Node* next;
};

Node node[MAX_NODE];
int nodeCnt;
Node* head;

Node* getNode(int data) {
	node[nodeCnt].data = data;
	node[nodeCnt].next = nullptr;
	return &node[nodeCnt++];
}

void init()
{
    head = (Node*)malloc(sizeof(Node));
    head->next = nullptr;
    nodeCnt=0;
}

void addNode2Head(int data) 
{
    Node* node = getNode(data);
    node->next = head->next;
    head->next = node;
}

void addNode2Tail(int data) 
{

    Node* tail = head;

    while(tail->next != nullptr)
    {
        tail = tail->next;
    }
    Node* node = getNode(data);
    tail->next = node;
}

void addNode2Num(int data, int num) 
{
    Node* tail = head;

    for(int i=1; i<num; ++i)
    {
        tail = tail->next;
    }


    Node* node = getNode(data);
    node->next = tail->next;
    tail->next = node;
}

void removeNode(int data) 
{
    Node* node = head;
    bool flag = false;
    while(node->next != nullptr)
    {

        if(node->next->data == data){
            flag=true;
            break;
        }
        node = node->next;
    }

    if(flag) node->next = node->next->next;
}

int getList(int output[MAX_NODE]) 
{
    Node* node = head;
    int cnt=0;
    while(node->next != nullptr)
    {
        node = node->next;
        output[cnt++] = node->data;
    }
    return cnt;
}


void run() {
	while (1) {
		int cmd, data, num, cnt, i;
		int output[MAX_NODE] = { 0 };

		scanf("%d", &cmd);
		switch (cmd) {
		case ADD_HEAD:
			scanf("%d", &data);
			addNode2Head(data);
			break;
		case ADD_TAIL:
			scanf("%d", &data);
			addNode2Tail(data);
			break;
		case ADD_NUM:
			scanf("%d %d", &data, &num);
			addNode2Num(data, num);
			break;
		case REMOVE:
			scanf("%d", &data);
			removeNode(data);
			break;
		case PRINT:
			cnt = getList(output);
			i = 0;
			while (cnt--)
				printf("%d ", output[i++]);
			printf("\n");
			break;
		case END:
			return;
		}
	}
}

int main(void) {
	//setbuf(stdout, NULL);
	freopen("input.txt", "r", stdin);

	int T;
	scanf("%d", &T);
	for (int t = 1; t <= T; t++) {
		printf("#%d\n", t);
		init();
		run();
		printf("\n");
	}

	return 0;
}
