#include <iostream>
#include <string>
#include <algorithm>
#include <sstream>
#include <queue>
using namespace std;

template <class K, class V>
class BinaryTree
{
public:
    class Node;

private:
    Node *root;

public:
    BinaryTree() : root(nullptr) {}
    ~BinaryTree()
    {
        // You have to delete all Nodes in BinaryTree. However in this task, you can ignore it.
    }
    class Node
    {
    private:
        K key;
        V value;
        Node *pLeft, *pRight;
        friend class BinaryTree<K, V>;

    public:
        Node(K key, V value) : key(key), value(value), pLeft(NULL), pRight(NULL) {}
        ~Node() {}
    };
    void addNode(string posFromRoot, K key, V value)
    {
        if (posFromRoot == "")
        {
            this->root = new Node(key, value);
            return;
        }
        Node *walker = this->root;
        int l = posFromRoot.length();
        for (int i = 0; i < l - 1; i++)
        {
            if (!walker)
                return;
            if (posFromRoot[i] == 'L')
                walker = walker->pLeft;
            if (posFromRoot[i] == 'R')
                walker = walker->pRight;
        }
        if (posFromRoot[l - 1] == 'L')
            walker->pLeft = new Node(key, value);
        if (posFromRoot[l - 1] == 'R')
            walker->pRight = new Node(key, value);
    }
    //=============BAI 2=====================
    // STUDENT ANSWER BEGIN
    int isBinaryST(Node *node)
    {
        if (node == NULL)
            return 1;

        /* false if left is > than node */
        if (node->pLeft != NULL && node->pLeft->value > node->value)
            return 0;

        /* false if right is < than node */
        if (node->pRight != NULL && node->pRight->value < node->value)
            return 0;

        /* false if, recursively, the left or right is not a BST */
        if (!isBinaryST(node->pLeft) || !isBinaryST(node->pRight))
            return 0;

        /* passing all that, it's a BST */
        return 1;
    }
    bool isBST()
    {
        // TODO: return true if a tree is a BST; otherwise, return false.
        return isBinaryST(root);
    }
    // STUDENT ANSWER END

    //===================BAI 3================
    int tree_height(Node *root)
    {
        // Get the height of the tree
        if (!root)
            return 0;
        else
        {
            // Find the height of both subtrees
            // and use the larger one
            int left_height = tree_height(root->pLeft);
            int right_height = tree_height(root->pRight);
            if (left_height >= right_height)
                return left_height + 1;
            else
                return right_height + 1;
        }
    }
    int getHeight()
    {
        return tree_height(this->root);
        // TODO: return height of the binary tree.
    }
    string preOrderRec(Node *root)
    {
        stringstream ss;
        if (root != nullptr)
        {
            ss << root->value << " ";
            ss << preOrderRec(root->pLeft);
            ss << preOrderRec(root->pRight);
        }
        return ss.str();
    }
    string preOrder()
    {
        // TODO: return the sequence of values of nodes in pre-order.
        return preOrderRec(this->root);
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
    string postOrderRec(Node *root)
    {
        stringstream ss;
        if (root != nullptr)
        {
            ss << postOrderRec(root->pLeft);
            ss << postOrderRec(root->pRight);
            ss << root->value << " ";
        }
        return ss.str();
    }
    string postOrder()
    {
        // TODO: return the sequence of values of nodes in post-order.
        return postOrderRec(this->root);
    }

    // STUDENT ANSWER END

    //=================BAI 1==================
    // STUDENT ANSWER BEGIN
    // You can define other functions here to help you.
    void BreadthFirstTravseral(Node *root)
    {
        std::queue<Node *> q;
        if (root)
        {
            q.push(root);
            cout << root->value;
        }
        while (!q.empty())
        {
            const Node *const temp_node = q.front();
            q.pop();

            if (temp_node->pLeft)
            {
                q.push(temp_node->pLeft);
                cout << " " << temp_node->pLeft->value;
            }

            if (temp_node->pRight)
            {
                q.push(temp_node->pRight);
                cout << " " << temp_node->pRight->value;
            }
        }
    }
    void BFS()
    {
        BreadthFirstTravseral(this->root);
    }
    // STUDENT ANSWER END
};

int main()
{
    BinaryTree<int, int> binaryTree;
    binaryTree.addNode("", 2, 4);  // Add to root
    binaryTree.addNode("L", 3, 6); // Add to root's left node
    binaryTree.addNode("R", 5, 9); // Add to root's right node
    binaryTree.BFS();
    return 0;
}