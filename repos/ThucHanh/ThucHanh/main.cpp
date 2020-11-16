#include <iostream>
#include <string>
#include <sstream>
using namespace std;
// #define SEPARATOR "#<ab@17943918#@>#"

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
            Node *p = new Node(value);
            root = p;
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
    bool del(Node *root, T value)
    {
        if (root != nullptr)
        {
            Node *ptr = new Node();
            ptr = root;
            if (value < root->value)
                return remove(root->pLeft, value);
            else if (value > root->value)
                return remove(root->pRight, value);
            else
            {
                // if (root->pLeft == nullptr&& root->pRight == nullptr){
                //     Node *p= root;
                //     delete p;
                //     p=nullptr;

                // }
                if (root->pLeft == nullptr)
                {
                    ptr = root;
                    root = root->pRight;
                    delete ptr;
                    ptr = nullptr;
                    return true;
                }
                else if (root->pRight == nullptr)
                {
                    ptr = root;
                    root = root->pLeft;
                    delete ptr;
                    ptr = nullptr;
                    return true;
                }
                else
                {
                    ptr = root->pLeft;
                    while (ptr->pRight != nullptr)
                    {
                        ptr = ptr->pRight;
                    }
                    root->value = ptr->value;
                    return remove(root->pLeft, ptr->value);
                }
            }
        }
        return false;
    }
    
    bool remove(Node *root, T value)
    {
        if (root)
        {
            if(root->value==value)
                {
                    if(root->pLeft && root->pRight){
                    Node *ptr = root->pRight;
                    while (ptr->pLeft)
                    {
                        ptr = ptr->pRight;
                    }
                    root->value = ptr->value;
                    remove(root->pRight, ptr->value);
                }
                else if(root->pLeft){
                    Node *p =root;
                    root = root->pLeft;
                    delete p;
                    p = nullptr;
                }
                else if(root->pRight){
                    Node *p =root;
                    root = root->pRight;
                    delete p;
                    p = nullptr;
                }
                else{
                    delete root;
                    root = nullptr;
                }
            }
        }
        return false;
    }
    
    void deleteNode(T value)
    {
        remove(root, value);
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
};

int main()
{
    BinarySearchTree<int> bst;
    bst.add(9);
    bst.add(2);
    bst.add(10);
    bst.add(8);
    bst.add(11);
    cout << bst.inOrder() << endl;
    bst.deleteNode(9);
    cout << bst.inOrder();
    return 0;
}