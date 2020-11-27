#include <iostream>
#include <sstream>
#include <string>

using namespace std;

template <class K, class D, int M> // K: key, D: data, M: degree of BTree
class BTree
{
    /// Convention: Left sub-tree < Root's key <= Right sub-tree

public:
    class Entry;
    class Node;

private:
    Node *root;

public:
    BTree() : root(0){};
    ~BTree() {}

public:
    class Entry
    {
    private:
        K key;
        D data;
        Node *rightPtr;

        friend class BTree<K, D, M>;

    public:
        Entry(K key = K{}, D value = D{}) : key(key), data(value), rightPtr(0) {}
        ~Entry() {}

        string toString()
        {
            stringstream ss;
            ss << "<"
               << this->key << ","
               << this->data
               << ">";
            return ss.str();
        }
    };

public:
    class Node
    {
    private:
        Node *firstPtr;
        int numEntries;
        Entry entries[M - 1];

        friend class BTree<K, D, M>;

    public:
        Node() : firstPtr(0), numEntries(0){};
        ~Node() {}

        bool isFull()
        {
            return (numEntries >= M - 1);
        }
        //==============BAI1================================================================================================================
        /// BEGIN STUDENT CODE
        string toString()
        {
            stringstream ss;
            // Fill your code here
            ss << "[(" << numEntries << ")";
            for (int i = 0; i < numEntries; i++)
            {
                ss << entries[i].toString();
            }
            ss << "]";
            return ss.str();
        }
    };
    void testPrintNode(K *keys, D *data, int size)
    {
        Node node;

        for (int idx = 0; idx < size; idx++)
        {
            node.entries[idx].key = keys[idx];
            node.entries[idx].data = data[idx];
        }
        node.numEntries = size;
        cout << node.toString() << endl;
    }
    string toStringPreOrder(Node* root){
        stringstream ss;
        ss << root->toString();
        ss << " ";
        ss << toStringPreOrder(root->firstPtr);
        for(int i = 0; i < root->numEntries; i++){
        ss << toStringPreOrder(root->entries[i].rightPtr);
        }
        return ss.str();
    }
    string toStringPreOrder()
    {
        stringstream ss;
        ss <<  toStringPreOrder(root);
        return ss.str();
    }
    //bài3
    /// BEGIN STUDENT CODE
    /// ======================================================
    // You may need some helping functions here

    bool search(Node *root, const K &key, Node *&outNodePtr, int &outEntryIdx)
    {
        if (root == NULL)
            return false;
        for (int i = root->numEntries - 1; i >= 0; i--)
        {
            if (key == root->entries[i].key)
            {
                outNodePtr = root;
                outEntryIdx = i;
                return true;
            }
            if (key > root->entries[i].key)
            {
                return search(root->entries[i].rightPtr, key, outNodePtr, outEntryIdx);
            }
        }
        return false;
    }

    bool search(const K &key, Node *&outNodePtr, int &outEntryIdx)
    {
        return search(root, key, outNodePtr, outEntryIdx);
    }
    /// END STUDENT CODE
};

int main()
{
    int keys[] = {3, 5, 7};
    int data[] = {33, 55, 77};
    int size = sizeof(keys) / sizeof(int);
    BTree<int, int, 5>().testPrintNode(keys, data, size);
    cout << endl;
    BTree<int, int, 5>().toStringPreOrder();


    return 0;
}