#include <bits/stdc++.h>
using namespace std;

void printKey(int key, int value)
{
    cout << key << endl;
}

template <class K, class V>
class SplayTree
{
public:
    class Entry
    {
    public:
        K key;
        V value;

        Entry(K key, V value) : key(key), value(value) {}
    };
    class Node
    {
    public:
        Entry *entry;
        Node *left;
        Node *right;
        Node *parent;
        typename SplayTree::Node *corr;
        Node(Entry *entry = NULL, Node *left = NULL, Node *right = NULL, Node *parent = NULL)
        {
            this->entry = entry;
            this->left = left;
            this->right = right;
            this->parent = parent;
            this->corr = NULL;
        }
    };

public:
    Node *root;

    SplayTree() : root(NULL){};
    ~SplayTree() { this->clear(); };
    // start add function
    void rightRotate(Node *P)
    {
        Node *T = P->left;
        Node *B = T->right;
        Node *D = P->parent;
        if (D)
        {
            if (D->right == P)
                D->right = T;
            else
                D->left = T;
        }
        if (B)
            B->parent = P;
        T->parent = D;
        T->right = P;

        P->parent = T;
        P->left = B;
    }
    void leftRotate(Node *P)
    {
        Node *T = P->right;
        Node *B = T->left;
        Node *D = P->parent;
        if (D)
        {
            if (D->right == P)
                D->right = T;
            else
                D->left = T;
        }
        if (B)
            B->parent = P;
        T->parent = D;
        T->left = P;

        P->parent = T;
        P->right = B;
    }

    void Splay(Node *T)
    {
        while (true)
        {
            Node *p = T->parent;
            if (!p)
                break;
            Node *pp = p->parent;
            if (!pp) //Zig
            {
                if (p->left == T)
                    rightRotate(p);
                else
                    leftRotate(p);
                break;
            }
            if (pp->left == p)
            {
                if (p->left == T)
                { //ZigZig
                    rightRotate(pp);
                    rightRotate(p);
                }
                else
                { //ZigZag
                    leftRotate(p);
                    rightRotate(pp);
                }
            }
            else
            {
                if (p->left == T)
                { //ZigZag
                    rightRotate(p);
                    leftRotate(pp);
                }
                else
                { //ZigZig
                    leftRotate(pp);
                    leftRotate(p);
                }
            }
        }
        root = T;
    }
    //end add function
    void add(K key, V value, Node *&root)
    {
        if (root == NULL)
        {
            root = new Node(NULL, NULL, NULL, NULL);
            root->entry = new Entry(key, value);
            return;
        }
        Node *P = root;
        while (true)
        {

            if (P->entry->key == key)
            {
                throw std::out_of_range("Duplicate key");
                return;
            }
            if (key < (P->entry->key))
            {
                if (P->left)
                    P = P->left;
                else
                {
                    P->left = new Node(NULL, NULL, NULL, P);
                    P->left->entry = new Entry(key, value);
                    P = P->left;
                    break;
                }
            }
            else
            {
                if (P->right)
                    P = P->right;
                else
                {
                    P->right = new Node(NULL, NULL, NULL, P);
                    P->right->entry = new Entry(key, value);
                    P = P->right;
                    break;
                }
            }
        }
        Splay(P);
    }
    void add(K key, V value)
    {
        add(key, value, root);
    }
    void add(Entry *entry)
    {
        add(entry->key, entry->value);
    }
    bool Erase(K key)
    {
        Node *N = searchS(key);
        if (!N)
            throw std::out_of_range("Not found");
        Splay(N); //check once more;
        Node *P = N->left;
        if (N->right && P)
        {
            while (P->right)
                P = P->right;
            root = N->left;
            root->parent = nullptr;
            Splay(P);
            P->right = N->right;
            N->right->parent = P;
            delete[] N;
            N = nullptr;
            return true;
        }
        else if (N->right)
        {
            root = root->right;
            root->parent = nullptr;
            delete[] N;
            N = nullptr;
        }
        else if (P)
        {
            root = root->left;
            root->parent = nullptr;
            delete[] N;
            N = nullptr;
        }
        else{
            delete[] N;
            N = nullptr;
            delete[] root;
            root = nullptr;
        }
        return true;
    }
    void remove(K key)
    {
        Erase(key);
    }
    // search
    Node *searchS(K key)
    {
        if (!root)
            return NULL;
        Node *P = root;
        while (P)
        {
            if (P->entry->key == key)
                break;
            if (key < (P->entry->key))
            {
                if (P->left)
                    P = P->left;
                else
                    break;
            }
            else
            {
                if (P->right)
                    P = P->right;
                else
                    break;
            }
        }
        Splay(P);
        if (P->entry->key == key)
            return P;
        else
            return NULL;
    }
    V search(K key)
    {
        Node *p = searchS(key);
        if (!p)
        {
            throw std::out_of_range("Not found");
        }
        return p->entry->value;
    }
    void traverseNLR(void (*func)(K key, V value), Node *root)
    {
        if (root)
        {
            func(root->entry->key, root->entry->value);
            traverseNLR(func, root->left);
            traverseNLR(func, root->right);
        }
    }
    void traverseNLR(void (*func)(K key, V value))
    {
        traverseNLR(func, root);
    }

    void clear()
    {
        while (root != nullptr)
        {
            remove(root->entry->key);
        }
    }

    // in cái cây ra
    int getHeightRec(Node *node)
    {
        if (node == NULL)
            return 0;
        int lh = this->getHeightRec(node->left);
        int rh = this->getHeightRec(node->right);
        return (lh > rh ? lh : rh) + 1;
    }

    void printNSpace(int n)
    {
        for (int i = 0; i < n - 1; i++)
            cout << " ";
    }

    void printInteger(int &n)
    {
        cout << n << " ";
    }
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
                cout << temp->entry->key;
                q.push(temp->left);
                q.push(temp->right);
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
};
int main()
{
    SplayTree<int, int> *tree = new SplayTree<int, int>();
    int keys[] = {1, 3, 5, 7, 9, 2, 4};
    for (int i = 0; i < 7; i++)
        tree->add(keys[i], keys[i]);
    tree->printTreeStructure();
    cout << "===========" << endl;
    tree->search(7);

    return 0;
}