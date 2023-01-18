#include <stdio.h>
#include <malloc.h>

#define MAX_NODE 10000

enum { ADD_HEAD = 1, ADD_TAIL, ADD_NUM, FIND, REMOVE, PRINT, PRINT_REVERSE, END = 99 };

struct Node {
	int data;
	Node *prev, *next;
};

Node node[MAX_NODE];
int nodeCnt, Cnt;
Node *head, *tail;

Node* getNode(int data) {
    Cnt++;
	node[nodeCnt].data = data;
	node[nodeCnt].prev = nullptr;
	node[nodeCnt].next = nullptr;
	return &node[nodeCnt++];
}

void init()
{
    head = (Node*)malloc(sizeof(Node));
    tail = (Node*)malloc(sizeof(Node));

    head->prev = nullptr;
    head->next = tail;
    tail->prev = head;
    tail->next = nullptr;

    nodeCnt=0, Cnt=0;
}

void addNode2Head(int data) 
{
    Node* node = getNode(data);
    head->next->prev = node;
    node->next = head->next;
    node->prev = head;
    head->next = node;
}

void addNode2Tail(int data) 
{
    Node* node = getNode(data);
    tail->prev->next = node;
    node->next = tail;
    node->prev = tail->prev;
    tail->prev = node;
}

void addNode2Num(int data, int num) 
{

    Node* node;
    if(Cnt/2 > num)
    {
        node = head;
        for(int i=1; i<num; ++i)
        {
            node = node->next;
        }
    }
    else{
        node = tail->prev;
        for(int i=Cnt; i>=num; --i)
        {
            node = node->prev;
        }
    }

    Node* nNode = getNode(data);
    nNode->next = node->next;
    nNode->prev = node;
    node->next->prev = nNode;
    node->next = nNode;
}

void removeNode(int data) 
{
    Node* node = head;
    bool flag = false;
    while(node->next != nullptr)
    {
        if(node->data == data){
            flag=true;
            break;
        }
        node = node->next;
    }

    if(flag) {
        Cnt--;
        node->prev->next = node->next;
        node->next->prev = node->prev;
    }
}

int findNode(int data)
{
    Node* node = head;

    int cnt=0;
    while(node->next != nullptr)
    {
        cnt++;
        node = node->next;
        if(node->data == data) return cnt;
    }
    return -1;
}

int getList(int output[MAX_NODE]) 
{
    Node* node = head;
    int cnt=0;
    while(node->next != tail)
    {
        node = node->next;
        output[cnt++] = node->data;
    }
    return cnt;
}

int  getReversedList(int output[MAX_NODE])
{
    Node* node = tail;
    int cnt=0;
    while(node->prev != head)
    {
        node = node->prev;
        output[cnt++] = node->data;
    }
    return cnt;
}


void run() {
	while (1) {
		int cmd, data, num, cnt, i = 0;
		int output[MAX_NODE] = { 0 };

		scanf("%d", &cmd);
		switch (cmd) {
		case ADD_HEAD: // 1
			scanf("%d", &data);
			addNode2Head(data);
			break;
		case ADD_TAIL: // 2
			scanf("%d", &data);
			addNode2Tail(data);
			break;
		case ADD_NUM: // 3
			scanf("%d %d", &data, &num);
			addNode2Num(data, num);
			break;
		case FIND: // 4
			scanf("%d", &data);
			num = findNode(data);
			printf("%d\n", num);
			break;
		case REMOVE: // 5
			scanf("%d", &data);
			removeNode(data);
			break;
		case PRINT: // 6
			cnt = getList(output);
			while (cnt--)
				printf("%d ", output[i++]);
			printf("\n");
			break;
		case PRINT_REVERSE: // 7
			cnt = getReversedList(output);
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
