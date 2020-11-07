#include <sstream>
#include <string>
#include <iostream>
#include <type_traits>
using namespace std;
template <class T>
class DLinkedList
{
public:
    class Iterator; //forward declaration
    class Node;     //forward declaration
protected:
    Node *head;
    Node *tail;
    int count;

public:
    DLinkedList() : head(NULL), tail(NULL), count(0){};
    ~DLinkedList();
    void add(const T &e);
    void add(int index, const T &e);
    T removeAt(int index);
    bool removeItem(const T &item);
    bool empty();
    int size();
    void clear();
    T get(int index);
    void set(int index, const T &e);
    int indexOf(const T &item);
    bool contains(const T &item);
    string toString();
    Iterator begin()
    {
        return Iterator(this, true);
    }
    Iterator end()
    {
        return Iterator(this, false);
    }

public:
    class Node
    {
    private:
        T data;
        Node *next;
        Node *prev;
        friend class DLinkedList<T>;

    public:
        Node()
        {
            next = 0;
        }
        Node(Node *next)
        {
            this->next = next;
        }
        Node(T data, Node *next = NULL)
        {
            this->data = data;
            this->next = next;
        }
    };
    class Iterator
    {
    private:
        DLinkedList<T> *pList;
        Node *current;
        int index; // is the index of current in pList
    public:
        Iterator(DLinkedList<T> *pList, bool begin);
        Iterator &operator=(const Iterator &iterator);
        void set(const T &e);
        T &operator*();
        bool operator!=(const Iterator &iterator);
        void remove();
        Iterator &operator++();
        Iterator operator++(int);
    };
};
/*
 * TODO: Implement class Iterator's method
 * Note: method remove is different from SLinkedList, which is the advantage of DLinkedList
 */
template <class T>
DLinkedList<T>::Iterator::Iterator(DLinkedList<T> *pList, bool begin)
{
    if (begin == true)
    {
        this->pList = pList;
        this->index = 0;
        this->current = pList->head;
    }
    else
    {
        this->pList = pList;
        this->index = pList->count;
        this->current = pList->tail->next;
    }
};

template <class T>
typename DLinkedList<T>::Iterator &DLinkedList<T>::Iterator::operator=(const DLinkedList<T>::Iterator &iterator)
{
    this->current = iterator.current;
    this->pList = iterator.pList;
    this->index = iterator.index;
    return *this;
};

template <class T>
void DLinkedList<T>::Iterator::set(const T &e)
{
    if (this->current)
        this->current->data = e;
};

template <class T>
T &DLinkedList<T>::Iterator::operator*()
{
    if (this->current)
        return this->current->data;
    return this->current->data;
}

template <class T>
void DLinkedList<T>::Iterator::remove()
{
    /*
    * TODO: delete Node in pList which Node* current point to. 
    *       After that, Node* current point to the node before the node just deleted.
    *       If we remove first node of pList, Node* current point to nullptr.
    *       Then we use operator ++, Node* current will point to the head of pList.
    */
    if (this->current)
    {
        Node *temp = this->pList->head;
        if (temp == this->current)
        {
            this->current = NULL;
            this->index = -1;
        }
        else
        {
            while (temp->next != this->current)
                temp = temp->next;
            temp->next = this->current->next;
            this->pList->count--;
            this->index--;
            delete this->current;
            this->current = temp;
        }
    }
};

template <class T>
bool DLinkedList<T>::Iterator::operator!=(const DLinkedList::Iterator &iterator)
{
    if ((this->current == iterator.current) && (this->index == iterator.index))
        return false;
    else
        return true;
};

template <class T>
typename DLinkedList<T>::Iterator &DLinkedList<T>::Iterator::operator++()
{
    if (this->index >= -1 && this->index <= pList->count - 1)
    {
        if (this->index == -1)
        {
            Iterator x(pList, true);
            *this = x;
        }
        else if (index == -1)
        {
            current = head;
            index++;
        }
        else
        {
            current = current->next;
            index++;
        }
    }
    return *this;
};

template <class T>
typename DLinkedList<T>::Iterator DLinkedList<T>::Iterator::operator++(int)
{
    Iterator temp = *this;
    if (this->current != NULL)
    {
        this->current = this->current->next;
        this->index = this->pList->count;
    }
    else
    {
        if (this->index == -1)
        {
            this->current = this->pList->head;
            this->index = this->pList->count;
        }
    }
    return temp;
};
//==============================

template <class T>
DLinkedList<T>::~DLinkedList()
{
    this->clear();
}

template <class T>
T DLinkedList<T>::get(int index)
{
    /* Give the data of the element at given index in the list. */

    int idx = 0;
    Node *p = head;
    while (idx != index)
    {
        idx++;
        p = p->next;
    }
    return p->data;
}

template <class T>
void DLinkedList<T>::set(int index, const T &e)
{
    /* Assign new value for element at given index in the list */
    if (index == 0)
    {
        head->data = e;
    }
    else if (index >= count)
    {
        tail->data = e;
    }
    else
    {
        Node *p = head->next;
        int pos = 1;
        while (pos != index)
        {
            pos++;
            p = p->next;
        }
        p->data = e;
    }
}

template <class T>
bool DLinkedList<T>::empty()
{
    /* Check if the list is empty or not. */
    return !count;
}

template <class T>
int DLinkedList<T>::indexOf(const T &item)
{
    /* Return the first index wheter item appears in list, otherwise return -1 */
    Node *p = head;
    int pos = 0;
    while (p->data != item)
    {
        pos++;
        p = p->next;
        if (pos >= count)
            return -1;
    }
    return pos;
}

template <class T>
bool DLinkedList<T>::contains(const T &item)
{
    /* Check if item appears in the list */
    Node *p = head;
    int pos = 0;
    while (p->data != item)
    {
        pos++;
        p = p->next;
        if (pos >= count)
            return false;
    }
    return true;
}
//====================================bai2
//====================================
//====================================
//====================================

template <class T>
void DLinkedList<T>::add(const T &e)
{
    /* Insert an element into the end of the list. */
    Node *pNew = new Node(e);
    if (count == 0)
    {
        head = tail = pNew;
        count++;
    }
    else
    {
        tail->next = pNew;
        pNew->prev = tail;
        tail = pNew;
        count++;
    }
}

template <class T>
void DLinkedList<T>::add(int index, const T &e)
{
    /* Insert an element into the list at given index. */
    Node *pNew = new Node(e);

    Node *p = head;
    if (index == count || count == 0)
    {
        this->add(e);
    }
    else if (index = 0)
    {
        p->previous = pNew;
        pNew->next = p;
        head = pNew;
        count++;
    }
    else
    {
        int idx = 0;
        while (idx != index)
        {
            p = p->next;
            idx++;
        }

        pNew->previous = p->previous;
        (p->previous)->next = pNew;
        p->previous = pNew;
        pNew->next = p;
        count++;
    }
}

template <class T>
int DLinkedList<T>::size()
{
    /* Return the length (size) of list */
    return count;
}
//========================bai3======================

template <class T>
T DLinkedList<T>::removeAt(int index)
{
    T dulieu = 0;
    int idx = 0;
    if (index == 0)
    {
        if (count == 1)
        {
            dulieu = head->data;
            this->clear();
            return dulieu;
        }
        else
        {
            dulieu = head->data;
            Node *pDel = head;
            head = head->next;
            head->previous = NULL;
            delete pDel;
        }
    }
    else
    {
        Node *p = head;
        while (idx < index)
        {
            idx++;
            p = p->next;
        }
        Node *pre = p->previous;
        dulieu = p->data;
        pre->next = p->next;
        if (p->next != NULL)
        {
            Node *nxt = pre->next;
            nxt->previous = pre;
        }
        delete p;
    }
    count--;
    return dulieu;
}

template <class T>
bool DLinkedList<T>::removeItem(const T &item)
{
    bool kiemtra = false;
    int idx = 0;
    Node *p = head;
    while (idx < count)
    {
        if (item == p->data)
        {
            kiemtra = true;
            this->removeAt(idx);
        }
        idx++;
        p = p->next;
    }
    return kiemtra;
}

template <class T>
void DLinkedList<T>::clear()
{
    if (count != 0)
    {
        Node *p = head;
        int idx = 0;
        while (idx != count - 1)
        {
            idx++;
            p = p->next;
            delete p->prev;
        }
        delete p;
        count = 0;
    }
}

//======================
template <class T>
string DLinkedList<T>::toString()
{
    stringstream ss;
    ss << "[";
    Node *ptr = this->head;

    if (this->count == 0)
        ss << "]";

    // TODO
    else
    {
        ss << ptr->data;
        ptr = ptr->next;
        for (int i = 1; i < count; i++)
        {
            ss << ", ";
            ss << ptr->data;
            ptr = ptr->next;
        }
        ss << "]";
    }
    // END: TODO

    return ss.str();
}
int main()
{
    DLinkedList<int> list;
    int size = 10;
    for (int idx = 0; idx < size; idx++)
    {
        list.add(idx);
    }
    DLinkedList<int>::Iterator it = list.begin();
    for (; it != list.end(); it++)
    {
        cout << *it << " |";
    }
    return 0;
}