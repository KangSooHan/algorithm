#include <stdio.h>
#include <malloc.h>

struct Node{
    int data;
    Node* next;
};

class singlyLinkedList{
    Node *head;
    int node_cnt;

public:
    singlyLinkedList () = default;

    void init(){
        head = new_node();
        node_cnt = 0;
    }

    void addNode2Head(int data)
    {
        Node* node = new_node(data);
        node->next = head->next;
        head->next = node;
        node_cnt++;
    }

    void addNode2Tail(int data)
    {
        Node* node = head->next;
        while(node->next != nullptr)
        {
            node = node->next;
        }

        node->next = new_node(data);
        node_cnt++;
    }

    void addNode2Num(int data, int num)
    {
        if(node_cnt == num){
            addNode2Tail(data);
        }
        else if(node_cnt > num){
            Node* node = idxFind(num);

            Node* addnode = new_node(data);
            addnode->next = node->next;
            node->next = addnode;
            node_cnt++;
        }
        else return;
   }

    void removeNode(int data)
    {

        Node* node = valFind(data);
        if(node == head) return;
        node->next = node->next->next;
        node--;
    }

    void getList(int output[])
    {
        Node* node = head;
        int cnt = 0;
        while(node->next != nullptr)
        {
            node = node->next;
            output[cnt++] = node->data;
        }
    }

    void print()
    {
        Node* node = head;
        printf("PRINT LIST :");
        while(node->next != nullptr)
        {
            node = node->next;
            printf(" %d", node->data);
        }
        printf("\n");
    }


public:
    Node* new_node()
    {
        Node* node = (Node *)malloc(sizeof(Node));
        node->next = nullptr;

        return node;
    }

    Node* new_node(int data)
    {
        Node* node = (Node *)malloc(sizeof(Node));
        node->next = nullptr;
        node->data = data;
        return node;
    }

    Node* idxFind(int idx)
    {
        Node* node = head;
        for(int i=0; i<idx; ++i)
        {
            node = node->next;
        }
        return node;
    }

    Node* valFind(int data)
    {
        Node* node = head;
        bool flag=false;
        while(node->next != nullptr)
        {
            if(node->next->data == data){
                flag = true;
                break;
            }
            node = node->next;
        }

        if(flag) return node;
        else return head;
    }
};


int main(){
    singlyLinkedList sll {};

    sll.init();

    // 2
    sll.addNode2Head(2);
    sll.print();
    // 1 2
    sll.addNode2Head(1);
    sll.print();
    // 1 2 4
    sll.addNode2Tail(4);
    sll.print();
    // 1 2 4 4
    sll.addNode2Tail(4);
    sll.print();
    // 0 1 2 4 4
    sll.addNode2Num(0, 0);
    sll.print();
    // 0 1 2 3 4 4 
    sll.addNode2Num(3, 3);
    sll.print();
    // 0 1 2 3 4 4 5
    sll.addNode2Num(5, 6); // add by index
    sll.print();
    // 0 1 2 3 4 5
    sll.removeNode(4); // remove by value
    sll.print();

    int output[6];
    sll.getList(output);
    printf("List : ");
    for(int i=0; i<6; ++i)
    {
        printf(" %d", output[i]);
    }
    printf("\n");

    return 0;
}
