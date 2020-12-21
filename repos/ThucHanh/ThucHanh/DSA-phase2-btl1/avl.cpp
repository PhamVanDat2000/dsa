#include <bits/stdc++.h>
using namespace std;

void printKey(int key, int value)
{
    cout << key << endl;
}

template <class K, class V>
class AVLTree
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
        int balance;

        Node(Entry *entry = NULL, Node *left = NULL, Node *right = NULL)
        {
            this->entry = entry;
            this->left = left;
            this->right = right;
            this->balance = 0;
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

    //Left subtree is higher than the right subtree
    Node *&leftBalance(Node *&root, bool &taller)
    {
        Node *leftTree = root->left;
        //Left Left case
        if (leftTree->balance > 0)
        {
            //slide sai thu tu
            root->balance = 0;
            leftTree->balance = 0;
            root = rotateRight(root);
            taller = false;
        }
        else
        {
            //Left right case
            Node *rightTree = leftTree->right;
            if (rightTree->balance > 0)
            {
                root->balance = -1;
                leftTree->balance = 0;
            }
            else if (rightTree->balance == 0)
            {
                //slide thieu
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

    //Right subtree is higher than the left subtree
    Node *&rightBalance(Node *&root, bool &taller)
    {
        Node *rightTree = root->right;
        //right right case
        if (rightTree->balance < 0)
        {
            root->balance = 0;
            rightTree->balance = 0;
            root = rotateLeft(root);
            taller = false;
        }
        else
        {
            //right left case
            Node *leftTree = rightTree->left;
            if (leftTree->balance < 0)
            {
                root->balance = 1;
                rightTree->balance = 0;
            }
            else if (leftTree->balance == 0)
            {
                //slide thieu
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
        cout << add(root, newNode, taller)->entry->key;
        return root;
    }
    Node *add(Entry *entry)
    {
        return add(entry->key, entry->value);
    }
    //=============remove========
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

    string printinorder(Node *root)
    {
        stringstream ss;
        if (root != nullptr)
        {
            ss << printinorder(root->left);
            ss << root->entry->value << " ";
            ss << printinorder(root->right);
        }
        return ss.str();
    }
    void printAVL()
    {
        cout << printinorder(root);
    }
};

int main()
{
    AVLTree<int, int> *tree = new AVLTree<int, int>();
    int keys[] = {1, 3, 5, 7, 9, 2, 4};
    for (int i = 0; i < 7; i++)
        tree->add(keys[i], keys[i]);
    cout << endl << "============="<<endl;
    tree->traverseNLR(printKey);
    return 0;
}