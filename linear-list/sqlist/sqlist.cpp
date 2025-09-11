#include <iostream>
#include <vector>
#define InitSize 10
using namespace std;

typedef struct{
    int *data;//指向动态分配数组的指针
    int MaxSize;//当前分配的数组容量
    int length;//当前长度
}Sqlist;

void InitList(Sqlist &L) {
    L.data = new int[InitSize];
    L.MaxSize = InitSize;
    L.length = 0;
}

void DestoryList(Sqlist &L){
    delete[] L.data;
    L.data = NULL;
    L.length = 0;
    L.MaxSize = 0;
}

void IncreaseSize(Sqlist &L,int newSize){//扩容顺序表的容量
    int *p = L.data;
    L.data = new int[L.MaxSize+newSize];
    for(int i=0;i<L.length;++i){
        L.data[i] = p[i];//拷贝原数组元素
    }
    L.MaxSize = L.MaxSize+newSize;//更新最大容量
    delete[] p;

}

bool ListInsert(Sqlist &L,int i,int e){// 在L上的第i个位置插入元素e
    if(i<1||i>L.length+1){
        return false;
    }
    if(L.length>=L.MaxSize){
        IncreaseSize(L,10);
    }
    for(int j = L.length;j>=i;--j){
        L.data[j] = L.data[j-1];
    }
    L.data[i-1] = e;
    L.length++;
    return true;
}

bool ListDelete(Sqlist &L,int i,int &e){// 在L上的第i个位置删除元素e
    if(i>L.length||i<1){
        return false;
    }

    e = L.data[i-1];
    for(int j = i;j<L.length;++j){
        L.data[j-1] = L.data[j];
    }
    L.length--;
    return true;
}

int GetElem(Sqlist L,int i){//返回L上第i个位置上的元素
    if(i<1 || i>L.length){
        cout<<"Position Wrong";
        return -1;
    }
    return L.data[i-1];
}

int LocateElem(Sqlist &L,int e){//按值查找
    for(int i = 0;i<L.length;++i){
        if (L.data[i] == e)
            return i+1;    
    }
    return -1;
}

int main() {
   return 0;
}