#include <bits/stdc++.h>
using namespace std;

void printKey(int key, int value)
{
    cout << key << endl;
}

template <class K, class V>
class BKUTree
{
public:
    class AVLTree;
    class SplayTree;

    class Entry
    {
    public:
        K key;
        V value;

        Entry(K key, V value) : key(key), value(value) {}
    };

private:
    AVLTree *avl = new AVLTree();
    SplayTree *splay = new SplayTree();
    queue<K> keys;
    int maxNumOfKeys;

public:
    BKUTree(int maxNumOfKeys = 5)
    {
        this->maxNumOfKeys = maxNumOfKeys;
    }
    ~BKUTree() { this->clear(); }
    void add(K key, V value)
    {
        typename SplayTree::Node *pSplay = splay->add(key, value);
        typename AVLTree::Node *pAvl = avl->add(key, value);
        pSplay->corr = pAvl;
        pAvl->corr = pSplay;
        // cho vao hang doi
        if ((int)keys.size() == maxNumOfKeys)
            keys.pop();
        keys.push(key);
    }
    void remove(K key)
    {
        avl->remove(key);
        splay->remove(key);
        K temp;
        for (int i = 0; i < keys.size(); i++)
        {
            temp = keys.front();
            keys.pop();
            if (temp == key)
            {
                i--;
                continue;
            }
            else
            {
                keys.push(temp);
            }
        }
    }
    V search(K key, vector<K> &traversedList)
    {

        typename AVLTree::Node *p;
        if (key == splay->root->entry->key) // key trung root cua splay
        {
            //cho vao hang doi
            if ((int)keys.size() == maxNumOfKeys)
                keys.pop();
            keys.push(key);
            return splay->root->entry->value;
        }
        bool find = false;
        K temp;
        for (int i = 0; i < keys.size(); i++)
        {
            temp = keys.front();
            keys.pop();
            if (temp == key)
            {
                find = true;
                keys.push(temp);
                continue;
            }
            else
            {
                keys.push(temp);
            }
        }
        if (find) // neu co trong hang doi thi search splay
        {
            //cho vao hang doi
            if ((int)keys.size() == maxNumOfKeys)
                keys.pop();
            keys.push(key);
            return splay->searchBKU(key, traversedList);
        }
        else // neu k thi search avl
        {
            p = avl->findBKUAVL(splay->root->corr, key, traversedList);
            if (p) //neu tim thay (tim tu rootsplay->corr)
            {
                splay->splayBKU(p->corr); //splay 1 lan tren splay tree
                //cho vao hang doi
                if ((int)keys.size() == maxNumOfKeys)
                    keys.pop();
                keys.push(key);
                return p->entry->value;
            }
            else // neu khong tim thay tim tu goc
            {
                typename AVLTree::Node *pNew;
                pNew = avl->findBKU(splay->root->corr, key, traversedList);
                if (pNew)
                {
                    splay->splayBKU(pNew->corr);
                    //cho vao hang doi
                    if ((int)keys.size() == maxNumOfKeys)
                        keys.pop();
                    keys.push(key);
                    return pNew->entry->value;
                }
            }
        }
        return p->entry->value;
    }

    void traverseNLROnAVL(void (*func)(K key, V value))
    {
        avl->traverseNLR(func);
    }
    void traverseNLROnSplay(void (*func)(K key, V value))
    {
        splay->traverseNLR(func);
    }

    void clear()
    {
        avl->clear();
        splay->clear();
    }
    class SplayTree
    {
    public:
        class Node
        {
        public:
            Entry *entry;
            Node *left;
            Node *right;
            Node *parent;
            typename AVLTree::Node *corr;
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
        Node *add(K key, V value, Node *&root)
        {
            if (root == NULL)
            {
                root = new Node(NULL, NULL, NULL, NULL);
                root->entry = new Entry(key, value);
                return root;
            }
            Node *P = root;
            while (true)
            {

                if (P->entry->key == key)
                {
                    throw std::out_of_range("Duplicate key");
                    return P;
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
            return P;
        }
        Node *add(K key, V value)
        {
            return add(key, value, root);
        }
        Node *add(Entry *entry)
        {
            return add(entry->key, entry->value);
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
            else
            {
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
            if (P->entry->key == key)
            {
                Splay(P);
                return P;
            }
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
        //search cho bku
        void splayBKU(Node *P)
        {
            Node *p = P->parent;
            if (p)
            {
                Node *pp = p->parent;
                if (!pp) //Zig
                {

                    if (p->left == P)
                        rightRotate(p);
                    else
                        leftRotate(p);
                    root = P;
                }
                else if (pp->left == p)
                {
                    Node *ppp = pp->parent;

                    if (p->left == P)
                    { //ZigZig
                        rightRotate(pp);
                        rightRotate(p);
                    }
                    else
                    { //ZigZag
                        leftRotate(p);
                        rightRotate(pp);
                    }
                    if (ppp)
                    {
                        ppp = P;
                    }
                    else
                    {
                        root = P;
                    }
                }
                else
                {
                    Node *ppp = pp->parent;

                    if (p->left == P)
                    { //ZigZag
                        rightRotate(p);
                        leftRotate(pp);
                    }
                    else
                    { //ZigZig
                        leftRotate(pp);
                        leftRotate(p);
                    }
                    if (ppp)
                    {
                        ppp = P;
                    }
                    else
                    {
                        root = P;
                    }
                }
            }
        }
        Node *searchBKUS(K key, vector<K> &traversedList)
        {
            if (!root)
                return NULL;
            Node *P = root;
            while (P)
            {
                if (P->entry->key == key)
                    break;
                traversedList.push_back(P->entry->key);
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
            if (P->entry->key == key)
            {
                splayBKU(P);
                return P;
            }
            return NULL;
        }

        V searchBKU(K key, vector<K> &traversedList)
        {
            Node *p = searchBKUS(key, traversedList);
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
    };
    class AVLTree
    {
    public:
        class Node
        {
        public:
            Entry *entry;
            Node *left;
            Node *right;
            int balance;
            typename SplayTree::Node *corr;

            Node(Entry *entry = NULL, Node *left = NULL, Node *right = NULL)
            {
                this->entry = entry;
                this->left = left;
                this->right = right;
                this->balance = 0;
                this->corr = NULL;
            }
        };

    public:
        Node *root;

        AVLTree() : root(NULL){};
        ~AVLTree() { this->clear(); };
        Node *rotateRight(Node *&root)
        {
            Node *temp = root->left;
            root->left = temp->right;
            temp->right = root;
            return temp;
        }

        Node *rotateLeft(Node *&root)
        {
            Node *temp = root->right;
            root->right = temp->left;
            temp->left = root;
            return temp;
        }

        Node *&leftBalance(Node *&root, bool &taller)
        {
            Node *leftTree = root->left;
            if (leftTree->balance > 0)
            {
                root->balance = 0;
                leftTree->balance = 0;
                root = rotateRight(root);
                taller = false;
            }
            else
            {
                Node *rightTree = leftTree->right;
                if (rightTree->balance > 0)
                {
                    root->balance = -1;
                    leftTree->balance = 0;
                }
                else if (rightTree->balance == 0)
                {
                    root->balance = 0;
                    leftTree->balance = 0;
                }
                else
                {
                    root->balance = 0;
                    leftTree->balance = 1;
                }
                rightTree->balance = 0;
                root->left = rotateLeft(leftTree);
                root = rotateRight(root);
                taller = false;
            }
            return root;
        }

        Node *&rightBalance(Node *&root, bool &taller)
        {
            Node *rightTree = root->right;
            if (rightTree->balance < 0)
            {
                root->balance = 0;
                rightTree->balance = 0;
                root = rotateLeft(root);
                taller = false;
            }
            else
            {
                Node *leftTree = rightTree->left;
                if (leftTree->balance < 0)
                {
                    root->balance = 1;
                    rightTree->balance = 0;
                }
                else if (leftTree->balance == 0)
                {
                    root->balance = 0;
                    rightTree->balance = 0;
                }
                else
                {
                    root->balance = 0;
                    rightTree->balance = -1;
                }
                leftTree->balance = 0;
                root->right = rotateRight(rightTree);
                root = rotateLeft(root);
                taller = false;
            }
            return root;
        }
        Node *add(Node *&root, Node *&newPtr, bool &taller)
        {
            if (root == NULL)
            {
                root = newPtr;
                taller = true;
                return root;
            }
            if (newPtr->entry->key < root->entry->key)
            {
                root->left = add(root->left, newPtr, taller);
                if (taller)
                {
                    if (root->balance > 0)
                        root = leftBalance(root, taller);
                    else if (root->balance == 0)
                        root->balance = 1;
                    else
                    {
                        root->balance = 0;
                        taller = false;
                    }
                }
            }
            else if (newPtr->entry->key > root->entry->key)
            {
                root->right = add(root->right, newPtr, taller);
                if (taller)
                {
                    if (root->balance < 0)
                        root = rightBalance(root, taller);
                    else if (root->balance == 0)
                        root->balance = -1;
                    else
                    {
                        root->balance = 0;
                        taller = false;
                    }
                }
            }
            else
            {
                throw std::out_of_range("Duplicate key");
            }
            return root;
        }
        Node *add(K key, V value)
        {
            Node *newNode = new Node();
            newNode->entry = new Entry(key, value);
            bool taller = true;
            add(root, newNode, taller);
            return newNode;
        }
        Node *add(Entry *entry)
        {
            return add(entry->key, entry->value);
        }
        //=============remove========
        Node *rotR(Node *&root)
        {
            Node *p = root;
            root = root->left;
            p->left = root->right;
            root->right = p;
            return root;
        }
        Node *rotL(Node *&root)
        {
            Node *p = root;
            root = root->right;
            p->right = root->left;
            root->left = p;
            return root;
        }
        Node *removeLeftBalance(Node *&root, bool &shorter)
        {
            if (root->balance < 0)
            {
                root->balance = 0;
            }
            else if (root->balance == 0)
            {
                root->balance = 1;
                shorter = false;
            }
            else
            {
                Node *leftTree = root->left;
                if (leftTree->balance < 0)
                {
                    Node *rightTree = leftTree->right;
                    if (rightTree->balance < 0)
                    {
                        leftTree->balance = 1;
                        root->balance = 0;
                    }
                    else if (rightTree->balance == 0)
                    {
                        root->balance = -1;
                        leftTree->balance = 0;
                    }
                    else
                    {
                        root->balance = -1;
                        leftTree->balance = 0;
                    }
                    rightTree->balance = 0;
                    root->left = rotL(leftTree);
                    //slide thieu
                    root = rotR(root);
                }
                else
                {

                    if (leftTree->balance != 0)
                    {
                        root->balance = 0;
                        leftTree->balance = 0;
                    }
                    else
                    {
                        root->balance = 1;
                        leftTree->balance = -1;
                        shorter = false;
                    }
                    root = rotR(root);
                }
            }
            return root;
        }

        /*
	 * The (sub)tree is shorter after a deletion on the left branch. Adjust the balance factors and if necessary balance the tree by rotating left.
	 */
        Node *removeRightBalance(Node *&root, bool &shorter)
        {
            if (root->balance > 0)
            {
                root->balance = 0;
            }
            else if (root->balance == 0)
            {
                root->balance = -1;
                shorter = false;
            }
            else
            {
                Node *rightTree = root->right;
                if (rightTree->balance > 0)
                {
                    Node *leftTree = rightTree->left;
                    if (leftTree->balance > 0)
                    {
                        rightTree->balance = -1;
                        root->balance = 0;
                    }
                    else if (leftTree->balance == 0)
                    {
                        root->balance = 1;
                        rightTree->balance = 0;
                    }
                    else
                    {
                        root->balance = 1;
                        rightTree->balance = 0;
                    }
                    leftTree->balance = 0;
                    root->right = rotR(rightTree);

                    root = rotL(root);
                }
                else
                {
                    if (rightTree->balance != 0)
                    {
                        root->balance = 0;
                        rightTree->balance = 0;
                    }
                    else
                    {
                        root->balance = -1;
                        rightTree->balance = 1;
                        shorter = false;
                    }
                    root = rotL(root);
                }
            }
            return root;
        }
        Node *remove(Node *&root, K key, bool &shorter, bool &success)
        {
            if (root == NULL)
            {
                success = false;
                shorter = false;
                return NULL;
            }
            if (key < root->entry->key)
            {
                root->left = remove(root->left, key, shorter, success);
                if (shorter)
                    root = removeRightBalance(root, shorter);
            }
            else if (key > root->entry->key)
            {
                root->right = remove(root->right, key, shorter, success);
                if (shorter)
                    root = removeLeftBalance(root, shorter);
            }
            else
            {
                if (root->right == NULL)
                {
                    Node *newRoot = root->left;
                    success = true;
                    shorter = true;
                    delete root;
                    root = newRoot;
                    return root;
                }
                else if (root->left == NULL)
                {
                    Node *newRoot = root->right;
                    success = true;
                    shorter = true;
                    delete root;
                    root = newRoot;
                    return root;
                }
                else
                {
                    Node *tempPtr = root->left;
                    while (tempPtr->right != NULL)
                        tempPtr = tempPtr->right;
                    root->entry->value = tempPtr->entry->value;
                    root->entry->key = tempPtr->entry->key;
                    root->left = remove(root->left, tempPtr->entry->key, shorter, success);

                    if (shorter)
                        root = removeRightBalance(root, shorter);
                }
            }
            return root;
        }
        void remove(K key)
        {
            bool shorter = true;
            bool success = true;
            remove(root, key, shorter, success);
        }
        V findAVL(Node *root, K key)
        {
            if (root == nullptr)
                throw std::out_of_range("Not found");
            else
            {
                if (root->entry->key == key)
                {
                    return root->entry->value;
                }
                else if (root->entry->key > key)
                    return findAVL(root->left, key);
                else
                    return findAVL(root->right, key);
            }
        }
        V search(K key)
        {
            return findAVL(root, key);
        }
        // search BKU
        //tim kiem bku avl tu node p
        Node *findBKUAVL(Node *p, K key, vector<K> &traversedList) // tim tu node p
        {
            if (p == nullptr)
                return NULL;
            else
            {
                if (p->entry->key == key)
                {
                    return p;
                }
                traversedList.push_back(p->entry->key);
                if (p->entry->key > key)
                    return findBKUAVL(p->left, key, traversedList);
                else
                    return findBKUAVL(p->right, key, traversedList);
            }
        }
        //tim kiem bku tu root
        Node *findBKUaddfunct(Node *root, Node *p, K key, vector<K> &traversedList)
        { // tim tu root gap p thi tra ve ket qua kr tim thay
            if (root == nullptr || root == p)
                return NULL;
            else
            {
                if (root->entry->key == key)
                {
                    return root;
                }
                traversedList.push_back(root->entry->key);
                if (p->entry->key > key)
                    return findBKUaddfunct(root->left, p, key, traversedList);
                else
                    return findBKUaddfunct(root->right, p, key, traversedList);
            }
        }
        Node *findBKU(Node *p, K key, vector<K> &traversedList)
        {
            return findBKUaddfunct(root, p, key, traversedList);
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
    };
};
int main()
{
    BKUTree<int, int>* tree = new BKUTree<int, int>();
int keys[] = {1, 3, 5, 7, 9, 2, 4};
for (int i = 0; i < 7; i++) tree->add(keys[i], keys[i]);
tree->traverseNLROnSplay(printKey);
    return 0;
}