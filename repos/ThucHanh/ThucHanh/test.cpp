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
    Node *addRec(Node *root, T value)
    {
    }
    void add(T value);
    // STUDENT ANSWER BEGIN
    bool find(T i)
    {
        // TODO: return true if value i is in the tree; otherwise, return false.
        Node *p = new Node();
        p = root;
        while (p != NULL)
        {
            if (value < p->value)
                p = p->pLeft else if (value > p->value)
                        p = p->pRight else
                {
                    return true;
                }
        }
        return false
    }
    T addBT(Node *root)
    {
        T  sum;
        if (root == NULL)
            return 0;
        Node *p = new Node
        p=root;
        while(p->value < r){
            if(p->value > l)
            sum+= value;
            sum+= 
        }
        return (root->key + addBT(root->left) + addBT(root->right));
    }
    T sum(T l, T r)
    {
        // TODO: return the sum of all element in the tree has value in range [l,r].
        int
    }

    // STUDENT ANSWER END
};