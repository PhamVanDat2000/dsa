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
    Node *addNode(Node *root, T value)
    {
        if (root == nullptr)
            root = new Node(value);
        else
        {
            if (value < root->value)
                root->pLeft = addNode(root->pLeft, value);
            else
                root->pRight = addNode(root->pRight, value);
        }
        return root;
    }

    void add(T value)
    {
        root = addNode(root, value);
    }

    Node *deleteB(Node *root, T value)
    {
        if (root == nullptr)
            return root;
        if (value < root->value)
            root->pLeft = deleteB(root->pLeft, value);
        else if (value > root->value)
            root->pRight = deleteB(root->pRight, value);
        else
        {
            if (root->pLeft == nullptr && root->pRight == nullptr)
            {
                delete root;
                root = nullptr;
                return nullptr;
            }
            else if (root->pLeft == nullptr)
            {
                Node *pNew = root->pRight;
                delete root;
                root = nullptr;
                return pNew;
            }
            else if (root->pRight == nullptr)
            {
                Node *pNew = root->pLeft;
                delete root;
                root = nullptr;
                return pNew;
            }
            else{
                Node* p= root->pRight;
                while(p->pLeft) p = p->pLeft;
                root->value = p ->value;
                root->pRight = deleteB(root->pRight, root->value);
            }
        }
        return root;
    }

    void deleteNode(T value)
    {
        root = deleteB(root, value);
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
    cout << bst.inOrder() << endl;

    bst.add(11);
    bst.deleteNode(9);
    cout << bst.inOrder();
    return 0;
}