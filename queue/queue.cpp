#include <iostream>
using namespace std;

template <typename T>
class Deque{
    private:
        T* data;
        int front;
        int rear;
        int capacity;
    public:
        Deque(int cap){
            capacity = cap+1;
            front = 0;
            rear = 0;
            data = new T[capacity];
        }
        ~Deque(){
            delete[] data;
        }

        bool isFull(){
            return (rear+1)%capacity == front;
        }

        bool isEmpty(){
            return front==rear;
        }
        void Enqueue(const T x){
            if (this->isFull())
            {
                throw out_of_range("queue is full");
            }
            else{
                data[rear] = x;
                rear = (rear+1)%capacity;
            }
        }

        T GetFront(){
            if (this->isEmpty())
            {
                throw out_of_range("queue is empty");
            }
            else{
                return data[this->front];
            }
            
        }

        void Dequeue(){
            if (this->isEmpty())
            {
                throw out_of_range("queue is empty");
            }
            else{
                front = (front+1)%capacity;
            }
        }
};

int main(){
    Deque<int> queue(3);
    cout << queue.isFull()<<endl;
    queue.Enqueue(1);
    cout << queue.GetFront()<<endl;
    queue.Enqueue(2);
    queue.Enqueue(3);
    cout << queue.isFull() << endl;
    queue.Dequeue();
    cout << queue.GetFront();
}