#include <iostream>
#include <string>
#include <sstream>

using namespace std;

template <class T>
class AVL
{
public:
    class Node;

protected:
    Node *pRoot;
    int nE;

public:
    BinarySearchTree() : root(nullptr) {}
    ~BinarySearchTree() {}

public:
    class Node
    {
        T data;
        Node *pLeft, *pRight;
        int b;

        friend class AVL;
    };
    void clear() {}

    Node* rotR(Node *&pR)
    {
        Node* p = pR;
        pR = pR->pLeft;
        p->pLeft = pR->pRight;
        pR->pRight = p;
        return pR;
    }
    Node* rotL(Node *&pR)
    {
        Node* p = pR;
        pR = pR->pRight;
        p->pRight = pR->pLeft;
        pR->pLeft = p;
        return pR;
    }
    Node* rotRL(Node *&pR)
    {
        rotR(pR->pRight);
        return rotL(pR);
    }
    Node* rotLR(Node *&pR)
    {
        rotL(pR->pLeft);
        return rotR(pR);
    }
    
    bool balanceLeft(Node *&pR)
    {
        if (pR->b == EH)
        {
            pR->b = LH;
            return true;
        }
        else if (pR->b == RH)
        {
            pR->b = EH;
            return false;
        }
        else
        {
            // L- L
            if ((pR->pLeft->b == LH))
            {
                rotR(&pR);
                pR->b = pR->pRight->b = EH;
                return false;
            }
            if ((pR->pLeft->b == EH))
            {
                rotR(&pR);
                pR->b = RH;
                pR->pRight->b = LH;
                return true;
            }
            rotLR(&pR);
            if (pR->b == EH)
            {
                pR->pLeft->b = pR->pRight->b = EH;
            }
            else if(pR->b == LH){
                pR->b= pR->pLeft->b = EH;
                pR->pRight->b = RH
            }
            else{
                pR->b = pR->pRight->b = EH;
                pR->pRight->b= LH;
            }
            return false;
        }
    }
    bool balanceRight(Node *&pR)
    {
        if (pR->b == EH)
        {
            pR->b = RH;
            return true;
        }
        else if (pR->b == LH)
        {
            pR->b = EH;
            return false;
        }
        else
        {
            // L- L
            if ((pR->pLeft->b == RH))
            {
                rotR(&pR);
                pR->b = pR->pLeft->b = EH;
                return false;
            }
            if ((pR->pRight->b == EH))
            {
                rotR(&pR);
                pR->b = LH;
                pR->pLeft->b = RH;
                return true;
            }
            rotLR(&pR);
            if (pR->b == EH)
            {
                pR->pRight->b = pR->pLeft->b = EH;
            }
            else if(pR->b == RH){
                pR->b= pR->pRight->b = EH;
                pR->pLeft->b = LH
            }
            else{
                pR->b = pR->pLeft->b = EH;
                pR->pRight->b= RH;
            }
            return false;
        }
    }
    bool insert(const T &e, Node *&pR)
    {
        if (pR == nullptr)
        {
            pR = new Node(e);
            return true;
        }
        if (pR->data > e)
        {
            if (insert(e, pR->pLeft))
                return balanceLeft(pR);
        }
        else
        {
            if (insert(e, pR->pRight))
                return balanceRight(pR);
        }
        return false;
    }
    bool remove(const T &e, Node *&pR) {
        bool removeLeft=true;
        bool ret;
        if(pR){
            if(pR->data ==e){
                if (pr->pLeft && pR->pRight){
                    Node *p = pR->pRight;
                    while(p->pLeft)
                    pR->data=p->data;

                    removeLeft = false;
                    ret = remove(p->data, pR->pRight);
                }
                else if(pR->pLeft){
                    Node *p = pR;
                    pR = p->pLeft;
                    delete p;
                    nE--;
                    return true;
                }
                else if(pR->pRight){
                    Node* p=pR;
                    pR = pR->pRight;
                    delete p;
                    nE--;
                    return true;
                }
                else{
                    delete pR;
                    pR = nullptr;
                    nE--;
                    return true;
                }
            }
            else if(pR->data>e){
                removeLeft = true;
                ret = remove(e, pR->pLeft;)
            }
            else{
                removeLeft = false;
                ret = remove(e, pR->pRight)
            }

            if(ret){
                if(removeLeft) 
                retrurn !balanceRight(& pR);
                else !balanceRight(&pR);
            }
        }
        return false;
    }
};

int main()
{
    AVLTree<int> avl;
int arr[] = {10,52,98,32,68,92,40,13,42,63,99,100};
for (int i = 0; i < 12; i++){
	avl.insert(arr[i]);
}
avl.printInorder();
cout << endl;
cout << avl.search(10);
}