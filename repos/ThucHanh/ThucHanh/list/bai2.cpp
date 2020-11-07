#include <iostream>
using namespace std;
template <class T>
class SLinkedList
{
public:
    class Node; // Forward declaration
protected:
    Node *head;
    Node *tail;
    int count;

public:
    SLinkedList() : head(NULL), tail(NULL), count(0){};
    ~SLinkedList(){};
    void add(const T &e);
    void add(int index, const T &e);
    int size();
    bool empty();
    T get(int index);
    void set(int index, const T &e);
    int indexOf(const T &item);
    bool contains(const T &item);
    // bai3
    T removeAt(int index);
    bool removeItem(const T &item);
    void clear();

public:
    class Node
    {
    private:
        T data;
        Node *next;
        friend class SLinkedList<T>;

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
};

template <class T>
void SLinkedList<T>::add(const T &e)
{
    /* Insert an element into the end of the list. */
    Node *pNew = new Node(e, NULL);
    if (count == 0)
    {
        head = tail = pNew;
        count++;
    }
    else
    {
        tail->next = pNew;
        tail = pNew;
        count++;
    }
}

template <class T>
void SLinkedList<T>::add(int index, const T &e)
{
    /* Insert an element into the list at given index. */
    Node *pNew = new Node(e, NULL);
    if (count == 0)
    {
        pNew->next = head;
        head = tail = pNew;
        count++;
    }
    else if (index == 0)
    {
        pNew->next = head;
        head = pNew;
        count++;
    }
    else if (index >= count)
    {
        tail->next = pNew;
        tail = pNew;
        count++;
    }
    else
    {
        int pos = 1;
        Node *p = head;
        while (pos < index && pos < this->count)
        {
            pos++;
            p = p->next;
        }
        pNew->next = p->next;
        p->next = pNew;
        count++;
    }
}

template <class T>
int SLinkedList<T>::size()
{
    /* Return the length (size) of list */
    return count;
}

template <class T>
T SLinkedList<T>::get(int index)
{
    /* Give the data of the element at given index in the list. */
    if (index >= count)
    {
        return tail->data;
    }
    else
    {
        Node *p = head;
        int pos = 0;
        while (pos != index)
        {
            pos++;
            p = p->next;
        }
        return p->data;
    }
}

template <class T>
void SLinkedList<T>::set(int index, const T &e)
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
bool SLinkedList<T>::empty()
{
    /* Check if the list is empty or not. */
    return !count;
}

template <class T>
int SLinkedList<T>::indexOf(const T &item)
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
bool SLinkedList<T>::contains(const T &item)
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
// ================== bai 3========================================================================

template <class T>
T SLinkedList<T>::removeAt(int index)
{
    /* Remove element at index and return removed value */
    if(index>=count)
    index=count-1;
    int pos = 0;
    Node *p = head;
    T ketqua;
    if (count == 0)
    {
        return -1;
    }
    else if (count == 1 && index == 0)
    {
        ketqua = head->data;
        delete head;
        delete tail;
        count--;
        return ketqua;
    }
    else
    {
        if (index == 0)
        {
            ketqua = head->data;
            head = head->next;
            delete p;
            count--;
            return ketqua;
        }
        else if (index < count)
        {
            while (pos != (index - 1))
            {
                pos++;
                p = p->next;
            }
            Node *pDel = p->next;
            ketqua = pDel->data;
            p->next = pDel->next;
            delete pDel;
            count--;
            return ketqua;
        }
    }
    return ketqua;
}
template <class T>
bool SLinkedList<T>::removeItem(const T &item)
{
    /* Remove the first apperance of item in list and return true, otherwise return false */
    Node *p = head;
    if (head->data == item)
    {
        if (count == 1)
        {
            delete head;
            delete tail;
            count--;
            return true;
        }
        else
        {
            head = head->next;
            delete p;
            count--;
            return true;
        }
    }
    else
    {
        int pos = 1;
        Node *pDel = p->next;
        while (pDel->data != item)
        {
            pos++;
            p = p->next;
            pDel = p->next;
            if (pos >= count)
                return false;
        }
        if (pDel->data == item)
        {
            p->next = pDel->next;
            delete pDel;
            count--;
            return true;
        }
    }
    return false;
}

template <class T>
void SLinkedList<T>::clear()
{
    /* Remove all elements in list */
    while (count)
    {
        Node *p = head;
        head = head->next;
        delete p;
        count--;
    }
}

int main()
{
    SLinkedList<int> list;
    for (int idx = 0; idx < 11; idx++)
    {
        list.add(idx);
    }
    cout << "kich thuc" << list.size() << endl;
    cout << list.removeAt(8) << endl;
    cout << "kich thuc" << list.size() << endl;
    for (int idx = 0; idx < list.size(); idx++)
    {
        cout << list.get(idx) << "  ";
    }

    return 0;
}
