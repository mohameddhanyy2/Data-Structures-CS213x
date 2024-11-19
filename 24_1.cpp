#include <bits/stdc++.h>
using namespace std;
class Node{
public:
    int value;
    int k;
    Node* down;
    Node* next;
    Node(){
        value = 0;
        next = nullptr;
        down = nullptr;
    }
    Node(int value, int n){
        this->value = value;
        k = n;
        next = nullptr;
        down = nullptr;
    }
};
class LinkedList{
public:
    Node* head;
    Node* tail;
public:
    LinkedList(){
        head= nullptr;
        tail= nullptr;
    }
    LinkedList(int value){
        Node* newNode = new Node(value, 0);
        head = newNode;
        tail = newNode;

    }
    void printList(){
        Node*curr=head;
        while(curr){
            cout << curr->value << " " << curr->k << "\n";
            curr = curr->next;
        }
    }
    void read(int value){
        int x;
        while (value--){
            cin >> x;
            Append(x);
        }
    }
    void Append(int value){
        Node *newNode = new Node (value,0);
        if(!head){
            head = newNode;
            tail = newNode;
        }else{
            tail->next =newNode;
            tail=newNode;
        }
    }
    void attachAndPointBackToKNode(Node* pnn, int k) {
        tail->next = pnn;
        tail = pnn;
        Node* curr = head;
        Node* before = head;
        int count = 0;
        while (curr->next){
            curr = curr->next;
            count++;
            if (count > k) {
                before = before->next;
            }
        }
        pnn->down = before;
        cout << pnn->down->value;
    }
    ~LinkedList(){
        Node* temp = head;
        while(head){
            head = head->next;
            delete temp;
            temp = head;
        }
    }

};

int main(){
    LinkedList mainList;
    int n; cin >> n;
    mainList.read(n);
    int x; int y;
    cin >> x >> y;
    Node* newNode = new Node(x,y);
    mainList.attachAndPointBackToKNode(newNode, y);
    // mainList.printList();
    return 0;
}

/*

Input
6
33 17 15 23 19 80
25 3

 */
