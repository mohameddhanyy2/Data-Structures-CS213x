#include <bits/stdc++.h>
using namespace std;

class Node {
public:
    int left[6];
    int right[6];
    int money[3];
    int boat = 0;
    Node *next;
    string history = "";

    Node() {
        for (int i = 0; i < 6; i++) {
            left[i] = 1;
            right[i] = 0;
        }
        for (int i = 0; i < 3; i++) {
            money[i] = 0;
        }
        boat = 0;
        next = nullptr;
    }

    Node(Node *pNode) {
        for (int i = 0; i < 6; i++) {
            left[i] = pNode->left[i];
            right[i] = pNode->right[i];
        }
        for (int i = 0; i < 3; i++) {
            money[i] = pNode->money[i];
        }
        boat = pNode->boat;
        next = nullptr;
        history = pNode->history;
    }

    bool isGoalReached() {
        for (int i = 0; i < 6; i++) {
            if (right[i] == 0) return false;
        }
        return true;
    }

    void display() {
        for (int i = 0; i < 6; i++) {
            cout << left[i] << " ";
        }
        cout << "\n";
        for (int i = 0; i < 6; i++) {
            cout << right[i] << " ";
        }
        cout << "\n------------------" << endl;
    }

    void read() {
        cout << "Enter The Amount of Money for Each Thieve: ";
        for (int i = 0; i < 3; i++) {
            cin >> money[i];
        }
    }
};

class Stack {
public:
    Node *top;
    Stack() {
        top = nullptr;
    }
    void push(Node *n) {
        Node *newNode = new Node (n);
        if (!top) {
            top = newNode;
            newNode->next = nullptr;
        } else {
            newNode->next = top;
            top = newNode;
        }
    }
    Node *pop() {
        if (!top) {
            return nullptr;
        } else {
            Node *temp = top;
            top = top->next;
            return temp;
        }
    }
};

class LinkedList {
public:
    Node *head;
    Node *tail;
    LinkedList() {
        head = nullptr;
        tail = nullptr;
    }
    void append(Node *newNode) {
        Node *newNodeCopy = new Node(newNode);
        if (!head) {
            head = newNodeCopy;
            tail = newNodeCopy;
        } else {
            tail->next = newNodeCopy;
            tail = newNodeCopy;
        }
    }
    int isVisited(Node *thisNode) {
        Node *curr = head;
        while (curr){
            int isSame = 1;
            for (int i = 0; i < 6; i++) {
                if (curr->left[i] != thisNode->left[i] || curr->right[i] != thisNode->right[i]) {
                    isSame = 0;
                    break;
                }
            }
            if (thisNode->boat != curr->boat) isSame = 0;
            if (isSame) return 1;
            curr = curr->next;
        }
        return 0;
    }
    ~LinkedList() {
        Node *temp = head;
        while (temp){
            Node *next = temp->next;
            delete temp;
            temp = next;
        }
    }
};
string decode(int index1, int index2) {
    string s[6] = {"Thief 1", "Thief 2", "Thief 3", "Bag 1", "Bag 2", "Bag 3"};
    if (index1 == index2) {
        return s[index1] + "\n";
    }
    return s[index1] + " and " + s[index2] + "\n";
}

bool isValidState(Node &thisState) {
    int whatLeftDeserve = 0, whatRightDeserve = 0;
    int thievesLeft = 0, thievesRight = 0;
    int whatLeftHave = 0, whatRightHave = 0;
    for (int i = 0; i < 3; i++) {
        if (thisState.left[i + 3] == 1) {
            whatLeftHave += thisState.money[i];
        }
        if (thisState.right[i + 3] == 1) {
            whatRightHave += thisState.money[i];
        }
        if (thisState.left[i] == 1) {
            thievesLeft++;
            whatLeftDeserve += thisState.money[i];
        }
        if (thisState.right[i] == 1) {
            thievesRight++;
            whatRightDeserve += thisState.money[i];
        }
    }
    if (thievesLeft >= 1 && whatLeftDeserve < whatLeftHave) return false;
    if (thievesRight >= 1 && whatRightDeserve < whatRightHave) return false;
    return true;
}

void expandStates(Node *currState, Stack *validStates, LinkedList *visited ) {
    for (int i = 0; i < 3; i++) {
        if (currState->left[i] != currState->boat){
            for (int j = i ; j < 6; j++) {
                if (currState->left[j] != currState->boat) {
                    Node *thisState = new Node(currState);
                    if (i == j) {
                        thisState->left[i] = 1 - currState->left[i];
                        thisState->right[i] = 1 - currState->right[i];
                    }
                    thisState->left[i] = 1 - currState->left[i];
                    thisState->left[j] = 1 - currState->left[j];
                    thisState->right[i] = 1 - currState->right[i];
                    thisState->right[j] = 1 - currState->right[j];
                    thisState->history += decode(i,j);
                    thisState->boat = 1 - thisState->boat;
                    if (isValidState(*thisState)){
                        if(!visited->isVisited(thisState)){
                            validStates->push((thisState));
                            if (thisState->isGoalReached()){
                                cout << thisState->history << "-------------------------------------------"  << endl;
                                validStates->pop();
                            }
                        }
                    }
                }
            }
        }
    }
}
void solve() {
    LinkedList *visited = new LinkedList();
    Stack *validStates = new Stack();
    Node *initialState = new Node();
    initialState->read();
    cout << endl;
    validStates->push(initialState);
    while (validStates->top){
        Node *currState = validStates->pop();
        visited->append(currState);
        expandStates(currState, validStates, visited);
    }
}
int main() {
    solve();
    return 0;
}
