#include <iostream>
#include <string>
#include <sstream>

using namespace std;

template<class T>
class BinarySearchTree
{
public:
    class Node;

private:
    Node* root;

public:
    BinarySearchTree() : root(nullptr) {}
    ~BinarySearchTree()
    {
        // You have to delete all Nodes in BinaryTree. However in this task, you can ignore it.
    }

    class Node
    {
    private:
        T value;
        Node* pLeft, * pRight;
        friend class BinarySearchTree<T>;

    public:
        Node(T value) : value(value), pLeft(NULL), pRight(NULL) {}
        ~Node() {}
    };
    Node* addRec(Node* root, T value){
		Node* pNew = new Node(value);
		if (root==NULL) root = pNew;
		else{
			if (value<root->value) root->pLeft = addRec(root->pLeft,value);
			else root->pRight = addRec(root->pRight,value);
		}
		return root;
	};
    // STUDENT ANSWER BEGIN
	
	T getMin(){
			T min = root->value;
			Node*p = root;
			while (p->pLeft!=NULL){
				p = p->pLeft;
				min = min<p->value?min:p->value;
			}
			return min;
	}
	
	T getMax(){
		T max = root->value;
		Node*p = root;
		while (p->pRight!=NULL){
			p = p->pRight;
			max = max>p->value?max:p->value;
		}
		return max;
	}
    // STUDENT ANSWER END
	
	void add(T value){
        //TODO
		root = addRec(root,value);
    }
   
    Node* Delete(Node* root, T value){
		if (root==NULL) return root;
		if (value<root->value) root->pLeft = Delete(root->pLeft,value);
		else if (value>root->value) root->pRight = Delete(root->pRight,value);
		else{
			if (root->pLeft==NULL){
				Node* pNew = root->pRight;
				free(root);
				return pNew;
			}
			if (root->pRight==NULL){
				Node* pNew = root->pLeft;
				free(root);
				return pNew;
			}
			
			Node *p = root->pRight;
			while (p->pLeft!=NULL) p=p->pLeft;
			root->value = p->value;
			root->pRight = Delete(root->pRight,root->value);
		}
		return root;
	}
   
    void deleteNode(T value){
        //TODO
		root = Delete(root,value);
    }
	
	bool find(T i) {
		// TODO: return true if value i is in the tree; otherwise, return false.
		if (root==NULL) return false;
		Node *p = root;
		while (p!=NULL){
			if (i<p->value) p = p->pLeft;
			else if (i>p->value) p = p->pRight;
			else return true;
		}
		return false;
	}
	
    string inOrderRec(Node* root) {
        stringstream ss;
        if (root != nullptr) {
            ss << inOrderRec(root->pLeft);
            ss << root->value << " ";
            ss << inOrderRec(root->pRight);
        }
        return ss.str();
    }
    
    string inOrder(){
        return inOrderRec(this->root);
    }
	
	T sum(Node* root, T l, T r){
		if (root==NULL) return 0;
		if (root->value>r) return sum(root->pLeft,l,r);
		else if (root->value<l) return sum(root->pRight,l,r);
		else return root->value + sum(root->pLeft,l,root->value) + sum(root->pRight,root->value,r);
	}
	
	T sum(T l, T r) {
    // TODO: return the sum of all element in the tree has value in range [l,r].
		return sum(root,l,r);
	}
};

int main(){
    BinarySearchTree<int> bst;
    bst.add(9);
    bst.add(2);
    bst.add(2);
    bst.add(10);
    cout << bst.inOrder() << endl;

    bst.add(11);
    bst.deleteNode(9);
    cout << bst.inOrder();
    return 0;
}