#include <iostream>
using namespace std;

template <typename T>
class Node
{
public:
    Node<T> *next;
    T val;
    Node(T &x) : val(x), next(nullptr) {}
};

template <typename T>
class LinkedList
{
private:
    Node<T> *head;
    int size;

public:
    LinkedList() : head(nullptr), size(0) {}
    ~LinkedList()
    {
        Node<T> *cur = head;
        while (cur != nullptr)
        {
            Node<T> *temp = cur;
            cur = cur->next;
            delete temp;
        }
    }

    void pushfront(T x) // 头插
    {
        Node<T> *new_node = new Node<T>(x);
        new_node->next = head;
        head = new_node;
        size++;
    }

    void popfront(){// 头删
        if(head == nullptr){
            cout << "Empty ListNode"<<endl;
            return;
        }
        else{
            Node<T> * temp = head;
            head = head->next;
            size--;
            delete temp;
        }
    }

    void pushback(T x)
    { // 尾插法
        Node<T> *new_node = new Node<T>(x);
        if (head == nullptr)
        {
            head = new_node;
        }
        else
        {
            Node<T> *cur = head;
            while (cur->next != nullptr)
            {
                cur = cur->next;
            }

            cur->next = new_node;
        }
        size++;
    }

    void popback(){
        if(head == nullptr){
            cout << "Empty ListNode" << endl;
            return;
        }

        if (head->next = nullptr)
        {
            delete head;
            head = nullptr;
        }
        
        else{
            Node<T> *cur = head;
            while(cur->next->next!=nullptr){
                cur = cur->next;
            }
            delete cur->next;
            cur->next = nullptr;
            size --;
        }
    }

    void printListnode()
    {
        Node<T> *cur = head;
        while (cur != nullptr)
        {
            cout << cur->val << " ";
            cur = cur->next;
        }
    }

    void insert(int i, T x){//第i个节点插入x
        if (i<1||i>size+1)
        {
            cout << "Node does not exist" <<endl;
            return;
        }

        if (head == nullptr)
        {
            Node<T>* new_node = new Node(x);
            new_node->next = head;
            head = new_node;  
        }
        else{
            int count = 1;
            Node<T> * cur = head;
            while (count < i-1)
            {
                cur = cur->next;
                count++;
            }
            Node<T>* new_node = new Node(x);
            new_node->next = cur->next;
            cur->next = new_node;
        }
        size++;
    }

    void deleteNode(int i){//删除第i个节点
        if (i<1||i>size||head == nullptr)
        {
            cout << "Node does not exist" << endl;
            return;
        }
        
        if(i==1){
            Node<T>* temp = head;  // 临时保存头节点
            head = head->next;     // 更新头指针
            delete temp;
        }

        int count = 1;
        Node<T> * cur = head;
        while (count<i-1)
        {
            cur = cur->next;
            count++;
        }

        Node<T> *temp = cur->next;
        cur->next = cur->next->next;
        delete temp;
        size--;        
    }

    void modify(int i,T x){//修改第i个节点的值为x
        if (i<1||i>size||head == nullptr)
        {
            cout << "Node does not exist" << endl;
        }

        int count = 1;
        Node<T> * cur = head;
        while (count<i)
        {
            cur = cur->next;
            count ++;
        }
        cur->next = x;
    }

    T getVal(int i){
        if (i<1||i>size||head == nullptr)
        {
            cout << "Node does not exist" << endl;
        }

        Node<T> *cur = head;
        int count = 1;
        while (count < i)
        {
            cur = cur->next;
            count ++;
        }
        return cur->val;
    }

    int getOrder(T x){
        if (size == 0)
        {
            cout << "LinkedList is empty" << endl;
            return -1;
        }

        Node<T> *cur = head;
        int count = 1;
        while (cur!=nullptr)
        {   
            if (cur->val == x)
            {
                return count;
            }
            cur = cur->next;
            count ++;
        }

        cout << "Value not found in LinkedList" << endl;
        return -1;
    }



    int getSize(){
        return size;
    }

    void reverse(){
        Node<T>* prev = nullptr;   // 前一个节点
        Node<T>* cur = head;       // 当前节点
        Node<T>* next = nullptr; 

        while (cur!=nullptr)
        {
            next = cur->next;
            cur->next = prev;
            prev = cur;
            cur = next;
        }
        head  = prev;
        
    }

    template <typename U>
    friend ostream &operator<<(ostream &os, const LinkedList<U> &l);
};

template <typename T>//重载左移运算符直接打印
ostream &operator<<(ostream &os, const LinkedList<T> &l)
{
    Node<T> *cur = l.head;
    while (cur != nullptr)
    {
        os << cur->val << " ";
        cur = cur->next;
    }
    return os;
}

int main()
{
    LinkedList<int> l;
    l.pushfront(10);
    l.pushfront(20);
    l.pushfront(30);
    l.printListnode();
    l.pushback(10);
    cout << endl;
    l.insert(0,2);
    cout << l;
    l.reverse();
    cout << endl;
    cout << l;
    return 0;
}