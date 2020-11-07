#include <sstream>
#include <string>
#include <iostream>
#include <type_traits>
using namespace std;

#ifndef ILIST_H
#define ILIST_H

template <class T>
class IList
{
public:
    virtual void add(const T& element) = 0;
    virtual void add(int index, const T& element) = 0;
    virtual T& removeAt(int index) = 0;
    virtual bool removeItem(const T& item) = 0;
    virtual bool empty() = 0;
    virtual int size() = 0;
    virtual void clear() = 0;
    virtual T& get(int index) = 0;
    virtual void set(int index, const T& element) = 0;
    virtual int indexOf(const T& item) = 0;
    virtual bool contains(const T& item) = 0;
    virtual string toString() = 0;
};

#endif

// STUDENT ANSWER
#ifndef FRAGMENT_LINKED_LIST
#define FRAGMENT_LINKED_LIST
template <class T>
class FragmentLinkedList : IList<T>
{
public:
    class Node;
    class Iterator;

protected:
    Node** fragmentPointers;
    int fragmentMaxSize;
    int count;

public:
    FragmentLinkedList(int fragmentMaxSize = 5)
    {
        this->count = 0;
        this->fragmentMaxSize = fragmentMaxSize;
        this->fragmentPointers = new Node * [2];
        this->fragmentPointers[0] = NULL;
        this->fragmentPointers[1] = NULL;
    }
    virtual ~FragmentLinkedList() {
        fragmentPointers->clear();
    }
    virtual void add(const T& element){
        if (count % fragmentMaxSize == 0)
        {
            Node** newfragmentPointers = new Node * [count / fragmentMaxSize + 2];
            for (int i = 0; i < (count / fragmentMaxSize); i++)
            {
                newfragmentPointers[i] = fragmentPointers[i];
            }
            Node* pNew = new Node(element);
            newfragmentPointers[count / fragmentMaxSize]->next = pNew;
            pNew->prev = newfragmentPointers[count / fragmentMaxSize];
            newfragmentPointers[count / fragmentMaxSize] = pNew;
            newfragmentPointers[(count / fragmentMaxSize) + 1] = newfragmentPointers[count / fragmentMaxSize];
            delete[] fragmentPointers;
            fragmentPointers = newfragmentPointers;
            this->count++;
        }
        else
        {
            Node* pNew = new Node(element);
            fragmentPointers[(count / fragmentMaxSize) + 1]->next = pNew;
            pNew->prev = fragmentPointers[(count / fragmentMaxSize) + 1];
            fragmentPointers[count / fragmentMaxSize] = pNew;
            count++;
        }
    }
    virtual void add(int index, const T& element){}
    virtual T& removeAt(int index){
        Node* head = new Node;
        T ketqua = 0;
        head = this->fragmentPointers[0];
        if (index == 0) {
            ketqua = head->data;
            head = head->next;
            delete head->prev;
            head->prev = NULL;
        }
        else {
            int pos = 1;
            Node* p = head;
            while (pos < index && pos << this->count) {
                pos++;
                p = p->next;
            }
            ketqua = p->next->data;
            Node* xoa = p->next;
            p->next = xoa->next;
            if (index < this->count - 1) {
                p = p->next;
                p->prev = xoa->prev;
            }
            delete xoa;
        }

        this->count--;
        int numfrag = (this->count - 1) / this->fragmentMaxSize;
        Node** newFrag = new Node * [numfrag + 2];
        newFrag[0] = head;
        Node* p = new Node;
        p = head;
        int pos = 0;
        while (pos < this->count) {
            if (pos % this->fragmentMaxSize == 0) {
                newFrag[pos / this->fragmentMaxSize] = p;
            }
            p = p->next;
            pos++;
            if (pos == this->count - 1) newFrag[numfrag + 1] = p;
        }
        delete[] this->fragmentPointers;
        this->fragmentPointers = newFrag;
        return ketqua;
    }
    virtual bool removeItem(const T& item){
        bool kiemtra = false;
        int findpos = 0;
        Node* pfind = this->fragmentPointers[0];
        while (findpos < this->count) {
            if (item == pfind->data)
            {
                kiemtra = true;
                pfind = pfind->next;
                this->removeAt(findpos);
            }
            else {
                findpos++;
                pfind = pfind->next;
            }
        }
        return kiemtra;
    }
    virtual bool empty(){
        return !count;
    }
    virtual int size(){
        return count;
    }
    virtual void clear(){
    
    }
    virtual T& get(int index){
        Node* p = this->fragmentPointers[0];
        while (index--) {
            p = p->next;
        }
        return p->data;
    }
    virtual void set(int index, const T& element){
        Node* p = this->fragmentPointers[0];
        int a = 0;
        while (p != NULL && a != index) {
            p = p->next;
            a++;
        }
        p->data = element;        
    }
    virtual int indexOf(const T& item){
        Node* p = this->fragmentPointers[0];
        int a = 0;
        while (p != NULL) {
            a++;
            if (p->data == item)
                return a;
        }
        return -1;
    }
    virtual bool contains(const T& item){
        Node* p = this->fragmentPointers[0];
        while (p != NULL) {
            if (p->data == item)
                return true;
            p = p->next;
        }
        return false;
    }
    virtual string toString(){}
    Iterator begin(int index = 0){}
    Iterator end(int index = -1){}

public:
    class Node
    {
    private:
        T data;
        Node* next;
        Node* prev;
        friend class FragmentLinkedList<T>;

    public:
        Node()
        {
            next = 0;
            prev = 0;
        }
        Node(Node* next, Node* prev)
        {
            this->next = next;
            this->prev = prev;
        }
        Node(T data, Node* next, Node* prev)
        {
            this->data = data;
            this->next = next;
            this->prev = prev;
        }
    };

    class Iterator
    {
    private:
        FragmentLinkedList<T>* pList;
        Node* pNode;

    public:
        Iterator(FragmentLinkedList<T>* pList = 0, bool begin = true){}
        Iterator(FragmentLinkedList<T>* pList = 0, int fragmentIndex = 0, bool begin = true){}
        Iterator& operator=(const Iterator& iterator){}
        T& operator*(){}
        bool operator!=(const Iterator& iterator){}
        void remove(){}
        void set(const T& element){}
        Iterator& operator++(){}
        Iterator operator++(int){}
    };
};

template <class T>
string FragmentLinkedList<T>::toString()
{
    stringstream ss;
    ss << "[";
    Node* ptr = this->fragmentPointers[0];

    if (this->count == 0)
        ss << "]";

    // TODO

    // END: TODO

    return ss.str();
}

#endif
// END: STUDENT ANSWER

int main()
{
    // TESTCASE INPUT
    // === Example
    FragmentLinkedList<int> fList;
     for(int i = 0; i < 20 ; i++)
         fList.add(i, i * i);

     for(FragmentLinkedList<int>::Iterator it = fList.begin(); it != fList.end(); it++)
         cout << *it << " ";
     cout << endl;
    // === END: Example
    // END: TESTCASE INPUT

    return 0;
}
