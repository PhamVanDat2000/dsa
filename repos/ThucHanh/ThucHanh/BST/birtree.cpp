#include <iostream>
#include <string>
#include <sstream>
using namespace std;
#define SEPARATOR "#<ab@17943918#@>#"

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

    //Helping function

    void add(T value)
    {
        if (root == NULL)
        {
            root->value = value;
            root->pLeft = NULL;
            root->pRight = NULL;
        }
        else
        {
            Node *pNew = new Node(value);

            Node *p = new Node();
            p = root;
            Node *parent = new Node();
            while (p != NULL)
            {
                parent = p;
                if (value <= p->value)
                {
                    p = p->pLeft;
                }
                else
                {
                    p = p->pRight;
                }
            }
            if (value <= parent->value)
                parent->pLeft = pNew;
            else
            {
                parent->pRight = pNew;
            }
        }
    }
    bool deleteB(Node *root, T value)
    {
        if (root != nullptr)
        {
            Node *ptr = new Node();
            if (value < root->value)
                return deleteB(root->pLeft, value);
            else if (value > root->value)
                return deleteB(root->pRight, value);
            else
            {
                if (root->pLeft == nullptr)
                {
                    ptr = root;
                    root = root->pRight;
                    delete ptr;
                    return true;
                }
                else if (root->pRight == nullptr)
                {
                    ptr = root;
                    root = root->pLeft;
                    delete[] ptr;
                    return true;
                }
                else
                {
                    ptr = root->pLeft;
                    while (ptr->pRight != NULL)
                    {
                        ptr = ptr->pRight;
                    }
                    root->value = ptr->value;
                    return deleteB(root->pLeft, value);
                }
            }
        }
        return true;
    }
void deleteNode(T value)
{
    deleteB(root, value);
}
string inOrderRec(Node *root)
{
    stringstream ss;
    if (root != nullptr)
    {
        ss << inOrderRec(root->pLeft);
        ss << root->value << " ";
        ss << inOrderRec(root->pRight);
    }
    return ss.str();
}

string inOrder()
{
    return inOrderRec(this->root);
}

class Node
{
private:
    T value;
    Node *pLeft, *pRight;
    friend class BinarySearchTree<T>;

public:
    Node(T value) : value(value), pLeft(NULL), pRight(NULL) {}
    Node() {}
    ~Node() {}
};
}
;

int main()
{
    BinarySearchTree<int> bst;
    bst.add(9);
    bst.add(2);
    bst.add(10);
    bst.deleteNode(9);
    cout << bst.inOrder();
    return 0;
}