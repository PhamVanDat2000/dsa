#include <iostream>
#include <string>
#include <sstream>

using namespace std;

template <class T>
class BinarySearchTree
{
public:
    class Node;

private:
    Node *root;

public:
    BinarySearchTree() : root(nullptr) {}
    ~BinarySearchTree()
    {
        // You have to delete all Nodes in BinaryTree. However in this task, you can ignore it.
    }

    class Node
    {
    private:
        T value;
        Node *pLeft, *pRight;
        friend class BinarySearchTree<T>;

    public:
        Node(T value) : value(value), pLeft(NULL), pRight(NULL) {}
        ~Node() {}
    };
    Node *addRec(Node *root, T value);
    void add(T value);
    // STUDENT ANSWER BEGIN
    T getMin()
    {
        //TODO: return the minimum values of nodes in the tree.
        
        Node *p =new Node(root->value);
        p =root;
        Node *pF =new Node(root->value);
        while(p->pLeft!=NULL){
            pF= p;
            p=p->pLeft;
        }
        return *pF;
    }

    T getMax()
    {
        Node *p =new Node(root->value);
        p =root;
        Node *pF =new Node(root->value);
        while(p->pRight!=NULL){
            pF= p;
            p=p->pRight;
        }
        return *pF;
    }

    // STUDENT ANSWER END
};
int main()
{
    BinarySearchTree<int> bst;
    for (int i = 0; i < 10; ++i)
    {
        bst.add(i);
    }
    cout << bst.getMin() << endl;
    cout << bst.getMax() << endl;
    return 0;
}