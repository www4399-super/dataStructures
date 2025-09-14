#include <iostream>
#include <string>
using namespace std;

template <typename T>
class stack
{
private:
    int top;
    int capacity;
    T * data;
public:
    stack(){
        capacity = 10;
        top = -1;
        data = new T[capacity];
    }

    ~stack(){
        delete[] data; 
    }


    void resize(){
        T *new_data = new T[capacity*2];
        for (int i = 0; i < capacity; i++)
        {
            new_data[i] = data[i];
        }  
        capacity *= 2;
        delete[] data;
        data = new_data;
    }

    bool isEmpty(){
        return top == -1;
    }
        

    void push(T x){
        if (top==capacity-1)
        {
            resize();
        }
        data[++top] = x; 
    }

    T pop(){
        if (isEmpty())
        {
            cout << "stack is empty"<< endl;
            throw out_of_range("stack is empty");
        }  
        return data[top--];
    }

    T peek(){
        if (isEmpty())
        {
            throw out_of_range("stack is empty");
        }  
        return data[top];
    }  

    void print() {
        if (isEmpty()) {
            cout << "Stack is empty" << endl;
            return;
        }
        cout << "Stack contents (bottom -> top): ";
        for (int i = 0; i <= top; i++) {
            cout << data[i] << " ";
        }
        cout << endl;
    }

};        

int main(){
    stack<int> st;
    st.push(1);
    
    return 0;
}