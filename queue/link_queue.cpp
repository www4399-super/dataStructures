#include <iostream>
#include <string>
using namespace std;

template <typename T>
class Node{
    public:
        T  data;
        Node<T> *next;
        Node(T x){
            this->data = x;
            this->next = nullptr;
        }
};

template <typename T>
class queue{
    private:
        Node<T> * front;
        Node<T> * rear;
    public:
        queue(){
            front = rear = nullptr;
        }
        ~queue(){
            while (!this->isEmpty())
            {
                Node<T> * temp = front;
                front = front->next;
                delete temp;
            }
            
        }

        bool isEmpty(){//判断队是否为空
            return front==nullptr;
        }

        void Enqueue(T x){
            Node<T> *new_node = new Node<T>(x);
            if (this->isEmpty())
            {
                /* 队为空 */
                front = rear = new_node;
            }
            else{
                rear->next = new_node;
                rear = new_node;
            }
        }

        void Dequeue(){
            if (isEmpty())
            {
                cout << "Queue is Empty"<< endl;
            }
            else{
                if(front == rear){
                    Node<T> * temp = front;
                    front = rear = nullptr;
                    delete temp;
                }
                else{
                    Node<T> * temp = front;
                    front = front->next;
                    delete temp;
                }
            }
        }

        void print(){
            if(this->isEmpty()){
                cout << "Queue is Empty" << endl;
            }
            else{
                Node<T> *temp = front;
                while (temp!=nullptr)
                {
                    cout << temp->data << " ";
                    temp = temp->next;
                }
            }
        }

        T getFront(){
            if(isEmpty()){
                throw out_of_range("Queue is Empty");
            }
            else{
                return front->data;
            }
        }
};

int main(){
    queue<int> q;
    q.getFront();
    q.Enqueue(3);
    q.Enqueue(4);
    q.Dequeue();
    q.print();
}