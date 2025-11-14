#include <iostream>
#include <queue>
#include <stack>
#include <string>
using namespace std;

template <class T>
class node {
public:
    T data;
    node* left;
    node* right;
    node(T val) : data(val), left(nullptr), right(nullptr) {}
};

template <class T>
class binarytree {
public:
    node<T>* root;
    binarytree() : root(nullptr) {}
    
    node<T>* createFromPreIn(const string&, const string&); // 前序中序创建二叉树
    void preorder(node<T>*);  // 先序遍历
    void inorder(node<T>*);   // 中序遍历
    void postorder(node<T>*); // 后序遍历
    void levelorder(node<T>*); // 层次遍历
    void preorder_non_recursive(); // 先序遍历非递归实现
    void inorder_non_recursive();  // 中序遍历非递归实现
    void postorder_non_recursive();// 后续遍历非递归实现
    int countNode(node<T>*);       // 计算结点数
    int countLeaf(node<T>*);       // 计算叶子结点数
    int getWidth();                 // 获取二叉树的宽度
    void insert(T);                 // 按层次顺序插入一个新结点
    node<T>* copy(node<T>*);        // 拷贝辅助函数
    binarytree(const binarytree &); // 拷贝构造函数
    binarytree &operator=(const binarytree &); // 赋值重载运算
    ~binarytree();                  // 析构函数
    void deleteTree(node<T>*);      // 删除整棵树
    bool isMirror(node<T>*, node<T>*); // 判断两棵二叉树是否互为镜像
    bool isMirror_non_recursive(node<T>*, node<T>*);//判断两棵二叉树是否互为镜像
};

template <class T>// 先序遍历
void binarytree<T>::preorder(node<T>* root) {
    if(!root) return;
    cout << root->data << " ";
    preorder(root->left);
    preorder(root->right);
}

template <class T>// 中序遍历
void binarytree<T>::inorder(node<T>* root) {
    if(!root) return;
    inorder(root->left);
    cout << root->data << " ";
    inorder(root->right);
}

template <class T>// 后序遍历
void binarytree<T>::postorder(node<T>* root) {
    if(!root) return;
    postorder(root->left);
    postorder(root->right);
    cout << root->data << " ";
}

template <class T>//层序遍历
node<T>* binarytree<T>::createFromPreIn(const string& pre, const string& in) {
    if(pre.empty() || in.empty()) return nullptr;
    T rootVal = pre[0];
    node<T>* root = new node<T>(rootVal);
    int idx = in.find(pre[0]);
    string preLeft = pre.substr(1, idx);
    string preRight = pre.substr(idx+1);
    string inLeft = in.substr(0, idx);
    string inRight = in.substr(idx+1);
    root->left = createFromPreIn(preLeft, inLeft);
    root->right = createFromPreIn(preRight, inRight);
    return root;
}

template <class T>
void binarytree<T>::preorder_non_recursive(){//先序遍历非递归实现
    stack<node<T> *> s;
    s.push(root);
    while(!s.empty()) {
        node<T>* cur = s.top();
        s.pop();
        cout << cur->data << " ";
        
        if (cur->right)
        {
            s.push(cur->right);
        }

        if (cur->left){
            s.push(cur->left);
        }
        
    }
}

template <class T>
void binarytree<T>::inorder_non_recursive(){//中序遍历非递归实现
    stack<node<T> *> s;
    node<T>* cur = root;
    while (cur!=nullptr || !s.empty())
    {
        while (cur!=nullptr)
        {
            s.push(cur);
            cur = cur->left;
        }
        
        cur = s.top();
        s.pop();

        cout << cur->data <<" ";
        cur = cur->right;
    }
}

template <class T>
void binarytree<T>::postorder_non_recursive(){//后序遍历非递归实现
    stack<node<T> *> s;
    node<T> * cur = root;
    node<T> * lastvisited = nullptr;
    while (!s.empty()||cur)
    {
        while(cur){
            s.push(cur);
            cur = cur->left;
        }

        node<T> * top = s.top();
        if(!top->right || top->right == lastvisited){//已访问右子树
            cout << top->data << " ";
            s.pop();
            lastvisited = top;
        }
        else{
            cur = top->right;
        }
        
    }
    

}



template <class T>
void binarytree<T>::levelorder(node<T>* root) {
    if(!root) return;
    queue<node<T>*> q;
    q.push(root);

    int level = 0;
    while(!q.empty()) {
        int nodesInLevel = 1 << level; // 2^level 个位置
        bool allNull = true;

        for(int i = 0; i < nodesInLevel; i++) {
            node<T>* cur = nullptr;
            if(!q.empty()) {
                cur = q.front();
                q.pop();
            }

            if(cur) {
                cout << cur->data << " ";
                q.push(cur->left);
                q.push(cur->right);
                if(cur->left || cur->right) allNull = false;
            } else {
                cout << "# ";
                q.push(nullptr);
                q.push(nullptr);
            }
        }

        cout << endl;
        level++;
        if(allNull) break; // 整层都是空，停止打印
    }
}




template <class T>
int binarytree<T>::countLeaf(node<T>* root){
    if(!root) return 0;
    if(!root->left && ! root->right){
        return 1;
    }
    return countLeaf(root->left) + countLeaf(root->right);
}

template <class T>
int binarytree<T>::countNode(node<T>* root){//结点数
    if(!root) return 0;
    return 1+countNode(root->left) + countNode(root->right);
}


template <class T>
int binarytree<T>::getWidth() { // 求二叉树的宽度
    if (!root) return 0;

    queue<node<T>*> q;
    q.push(root);
    int maxWidth = 0;

    while (!q.empty()) {
        int levelSize = q.size();     // 当前层节点数
        maxWidth = max(maxWidth, levelSize); // 更新最大宽度

        for (int i = 0; i < levelSize; i++) {
            node<T>* cur = q.front();
            q.pop();
            if (cur->left) q.push(cur->left);
            if (cur->right) q.push(cur->right);
        }
    }

    return maxWidth;
}

template <class T>
void binarytree<T>::insert(T val){//按层序插入结点
    node<T> * new_node = new node(val);

    if(!root){
        root = new_node;
        return ;
    }

    queue<node<T> *> q;
    q.push(root);
    while (!q.empty())
    {
        node<T> * front = q.front();
        q.pop();
        if (!front->left)
        {
            front->left = new_node;
            return;
        }
        if(!front->right){
            front->right = new_node;
            return;
        }
        q.push(front->left);
        q.push(front->right);
    }
}

template <class T>
node<T>* binarytree<T>::copy(node<T>* root){
    if(!root) return nullptr;
    node<T> *new_node = new node(root);
    new_node->left = copy(root->left);
    new_node->right = copy(root->right);

    return new_node;
}


template <class T>
binarytree<T>::binarytree(const binarytree<T> &other){//拷贝构造
    root = copy(other.root);
}

template <class T>
bool binarytree<T>::isMirror(node<T>* root1, node<T>* root2){
    if(!root1||!root2) return false;
    if (root1->data!=root2->data)
    {
        return false;
    }
    
    if (root1->data==root2->data)
    {
        return isMirror(root1->left,root2->right) && isMirror(root1->right,root2->left);
    }
    
}

template <class T>
bool  binarytree<T>::isMirror_non_recursive(node<T>* root1, node<T>* root2){//镜像非递归实现
    queue<node<T> *>  q;

    q.push(root1);
    q.push(root2);

    while (!q.empty())
    {
        node<T> * a = q.front();
        q.pop();

        node<T> * b = q.front();
        q.pop();

        if(a==nullptr && b==nullptr){
            continue;
        }

        if (a == nullptr || b == nullptr) {
            return false;
        }
        
        if (a->data!=b->data)
        {
            return false;;
        }

        else{
            q.push(a->left);
            q.push(b->right);

            q.push(a->right);
            q.push(b->left);
        }
        
    }
    return true;
    
}

template <class T>
binarytree<T>& binarytree<T>::operator=(const binarytree<T> & other){
    if(this == &other) return *this;
    deleteTree();
    root = copy(other.root);
    return *this;

}

template <class T>
void binarytree<T>::deleteTree(node<T>* root) {
    if(root) {
        deleteTree(root->left);
        deleteTree(root->right);
        delete root;
    }
}

template <class T>
binarytree<T>::~binarytree() {
    deleteTree(root);
    root = nullptr;
}

int main() {
    binarytree<char> tree;
    string pre = "ABDHCEF";
    string in  = "DHBACEF";
    tree.root = tree.createFromPreIn(pre, in);
    cout << "先序遍历：" << endl;
    tree.preorder_non_recursive();
    cout << endl;
    cout << "层次遍历：" << endl;
    tree.levelorder(tree.root);
    
    tree.insert('A');
    tree.levelorder(tree.root);

    return 0;
}
