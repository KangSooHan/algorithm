#include <stdio.h>
#include <malloc.h>

struct Node{
    int data;
    Node *next, *prev;
};

class doublyLinkedList{
    Node *head, *tail;
    int node_cnt;

public:
    doublyLinkedList() = default;

    void init(){
        head = new_node();
        tail = new_node();

        head->prev = nullptr;
        head->next = tail;
        tail->prev = head;
        tail->next = nullptr;

        node_cnt = 0;
    }

    void insert(int pos, int cnt, int arr[])
    {
        Node* node = find(pos);

        for(int i=0; i<cnt; ++i)
        {
            Node* insert_node = new_node(arr[i]);

            insert_node->next = node->next;
            insert_node->prev = node;
            node->next = insert_node;

            node = node->next;
            node_cnt++;
        }
    }

    void print(){
        Node* node = head->next;

        for(int i=0; i<10; ++i)
                    {
            printf(" %d", node->data);
            node = node->next;
        }
    }

    void append(int cnt, int arr[])
    {
        for(int i=0; i<cnt; ++i)
        {
            Node* node = new_node(arr[i]);
            tail->prev->next = node;
            node->prev = tail->prev;
            node->next = tail;
            tail->prev = node;
            node_cnt++;
        }
    }

    void remove(int pos, int cnt)
    {
        Node* node = find(pos);

        Node* next_node = node->next;
        for(int i=0; i<cnt; ++i)
        {
            next_node = next_node->next;
            node_cnt--;
        }
        node->next = next_node;
        next_node->prev = node;
    }

    Node* find(int pos)
    {
        if(pos > node_cnt) return tail;

        Node* node = head;
        for(int cnt=1; cnt<=pos; ++cnt)
        {
            node = node->next;
        }

        return node;
    }

private:
    Node* new_node()
     {
        Node* node = (Node*)malloc(sizeof(Node));
        node->next = nullptr;
        node->prev = nullptr;
        return node;
    }

    Node* new_node(int data)
    {
        Node* node = (Node*)malloc(sizeof(Node));
        node->data = data;
        node->next = nullptr;
        node->prev = nullptr;
        return node;
    }
};


int main(){
    freopen("input.txt", "r", stdin);

    doublyLinkedList dll {};
    for(int test=1; test<=10; ++test)
    {
        dll.init();
        int num;
        scanf("%d", &num);
        int *origin = (int*)malloc(sizeof(int) * num);
        for(int i=0; i<num; ++i)
        {
            scanf("%d", &origin[i]);
        }
        dll.append(num, origin);

        int command_cnt;
        scanf("%d", &command_cnt);

        for(int i=0; i<command_cnt; ++i)
        {
            char command;
            scanf(" %c", &command);

            if(command=='I'){
                int x, y;
                scanf("%d %d", &x, &y);
                int *arr = (int*)malloc(sizeof(int) * y);
                                for(int j=0; j<y; ++j)
                {
                    scanf("%d", &arr[j]);
                }

                dll.insert(x, y, arr);
            }
            else if(command=='D'){
                int x, y;
                scanf("%d %d", &x, &y);
                dll.remove(x, y);
            }
            else{
                int y;
                scanf("%d", &y);

                int *arr = (int*)malloc(sizeof(int) * y);
                for(int j=0; j<y; ++j)
                {
                    scanf("%d", &arr[j]);
                }

                dll.append(y, arr);
            }
        }


        printf("#%d", test);
        dll.print();
        printf("\n");
    }

    return 0;
}
