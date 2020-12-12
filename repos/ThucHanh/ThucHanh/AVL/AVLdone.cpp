#include <iostream>
#include <math.h>
#include <queue>
#include <string>
using namespace std;
#define SEPARATOR "#<ab@17943918#@>#"

enum BalanceValue
{
    LH = -1,
    EH = 0,
    RH = 1
};

void printNSpace(int n)
{
    for (int i = 0; i < n - 1; i++)
        cout << " ";
}

void printInteger(int &n)
{
    cout << n << " ";
}

template <class T>
class AVLTree
{
public:
    class Node;

private:
    Node *root;

protected:
    int getHeightRec(Node *node)
    {
        if (node == NULL)
            return 0;
        int lh = this->getHeightRec(node->pLeft);
        int rh = this->getHeightRec(node->pRight);
        return (lh > rh ? lh : rh) + 1;
    }

public:
    AVLTree() : root(nullptr) {}
    ~AVLTree() {}
    int getHeight()
    {
        return this->getHeightRec(this->root);
    }
    void printTreeStructure()
    {
        int height = this->getHeight();
        if (this->root == NULL)
        {
            cout << "NULL\n";
            return;
        }
        queue<Node *> q;
        q.push(root);
        Node *temp;
        int count = 0;
        int maxNode = 1;
        int level = 0;
        int space = pow(2, height);
        printNSpace(space / 2);
        while (!q.empty())
        {
            temp = q.front();
            q.pop();
            if (temp == NULL)
            {
                cout << " ";
                q.push(NULL);
                q.push(NULL);
            }
            else
            {
                cout << temp->data;
                q.push(temp->pLeft);
                q.push(temp->pRight);
            }
            printNSpace(space);
            count++;
            if (count == maxNode)
            {
                cout << endl;
                count = 0;
                maxNode *= 2;
                level++;
                space /= 2;
                printNSpace(space / 2);
            }
            if (level == height)
                return;
        }
    }
    //===========================
    void rotR(Node *&pR)
    {
        Node *p = pR;
        pR = pR->pLeft;
        p->pLeft = pR->pRight;
        pR->pRight = p;
    }
    void rotL(Node *&pR)
    {
        Node *p = pR;
        pR = pR->pRight;
        p->pRight = pR->pLeft;
        pR->pLeft = p;
    }
    void rotLR(Node *&pR)
    {
        rotL(pR->pLeft);
        rotR(pR);
    }
    void rotRL(Node *&pR)
    {
        rotR(pR->pRight);
        rotL(pR);
    }
    bool balanceLeft(Node *&pR)
    {
        if (pR->balance == EH)
        {
            pR->balance = LH;
            return true;
        }
        else if (pR->balance == RH)
        {
            pR->balance = EH;
            return false;
        }
        else
        {
            // L- L
            if ((pR->pLeft->balance == LH))
            {
                rotR(pR);
                pR->balance = pR->pRight->balance = EH;
                return false;
            }
            if ((pR->pLeft->balance == EH))
            {
                rotR(pR);
                pR->balance = RH;
                pR->pRight->balance = LH;
                return true;
            }
            rotLR(pR);
            if (pR->balance == EH)
            {
                pR->pLeft->balance = pR->pRight->balance = EH;
            }
            else if (pR->balance == LH)
            {
                pR->balance = pR->pLeft->balance = EH;
                pR->pRight->balance = RH;
            }
            else
            {
                pR->balance = pR->pRight->balance = EH;
                pR->pRight->balance = LH;
            }
            return false;
        }
    }
    bool balanceRight(Node *&pR)
    {
        if (pR->balance == EH)
        {
            pR->balance = RH;
            return true;
        }
        else if (pR->balance == LH)
        {
            pR->balance = EH;
            return false;
        }
        else
        {
            // L- L
            if (pR->pRight->balance == RH)
            {
                rotL(pR);
                pR->balance = pR->pLeft->balance = EH;
                return false;
            }
            if ((pR->pRight->balance == EH))
            {
                rotR(pR);
                pR->balance = LH;
                pR->pLeft->balance = RH;
                return true;
            }
            rotLR(pR);
            if (pR->balance == EH)
            {
                pR->pRight->balance = pR->pLeft->balance = EH;
            }
            else if (pR->balance == RH)
            {
                pR->balance = pR->pRight->balance = EH;
                pR->pLeft->balance = LH;
            }
            else
            {
                pR->balance = pR->pLeft->balance = EH;
                pR->pRight->balance = RH;
            }
            return false;
        }
    }
    bool insert_T(const T &e, Node *&pR)
    {
        if (pR == nullptr)
        {
            pR = new Node(e);
            return true;
        }
        if (pR->data >= e)
        {
            if (insert_T(e, pR->pLeft))
                return balanceLeft(pR);
        }
        else
        {
            if (insert_T(e, pR->pRight))
                return balanceRight(pR);
        }
        return false;
    }
    void insert(const T &value)
    {
        insert_T(value, root);
    }
    // ====================== BAI 2 REMOVE=======================

    bool removeNode(const T &e, Node *&pR)
    {
        bool removeLeft = true;
        bool ret = false;
        if (pR)
        {
            if (pR->data == e)
            {
                if (pR->pLeft && pR->pRight)
                {
                    Node *p = pR->pRight;
                    while (p->pLeft)
                        pR->data = p->data;

                    removeLeft = false;
                    ret = removeNode(p->data, pR->pRight);
                }
                else if (pR->pLeft)
                {
                    Node *p = pR;
                    pR = pR->pLeft;
                    delete p;
                    return true;
                }
                else if (pR->pRight)
                {
                    Node *p = pR;
                    pR = pR->pRight;
                    delete p;
                    return true;
                }
                else
                {
                    delete pR;
                    pR = nullptr;
                    return true;
                }
            }
            else if (pR->data > e)
            {
                removeLeft = true;
                ret = removeNode(e, pR->pLeft);
            }
            else
            {
                removeLeft = false;
                ret = removeNode(e, pR->pRight);
            }

            if (ret)
            {
                if (removeLeft)
                    return !balanceRight(pR);
                else
                    return !balanceLeft(pR);
            }
        }
        return false;
    }

    void remove(const T &value)
    {
        removeNode(value, root);
    }

    //====================bai 3=============================
    void inOrderRec(Node *root)
    {
        if (root != nullptr)
        {
            inOrderRec(root->pLeft);
            cout << root->data << " ";
            inOrderRec(root->pRight);
        }
    }
    void printInorder()
    {
        inOrderRec(root);
    }

    bool search(const T &value)
    {
        //TODO
        if (root == NULL)
            return false;
        Node *p = root;
        while (p != NULL)
        {
            if (value < p->data)
                p = p->pLeft;
            else if (value > p->data)
                p = p->pRight;
            else
                return true;
        }
        return false;
    }

    class Node
    {
    private:
        T data;
        Node *pLeft, *pRight;
        BalanceValue balance;
        friend class AVLTree<T>;

    public:
        Node(T value) : data(value), pLeft(NULL), pRight(NULL), balance(EH) {}
        ~Node() {}
    };
};
int main()
{
    AVLTree<int> avl;
    int arr[] = {10, 52, 98, 32, 68, 92, 40, 13, 42, 63, 99, 100};
    for (int i = 0; i < 12; i++)
    {
        avl.insert(arr[i]);
    }
    avl.printInorder();
    cout << endl;
    int a = 10;
    avl.remove(a);
    avl.printInorder();
    return 0;
}