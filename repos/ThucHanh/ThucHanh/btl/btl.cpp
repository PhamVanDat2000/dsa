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
   void virtual  add(const T &element) = 0;
    virtual void add(int index, const T &element) = 0;
    virtual T removeAt(int index) = 0;
    virtual bool removeItem(const T &item) = 0;
    virtual bool empty() = 0;
    virtual int size() = 0;
    virtual void clear() = 0;
    virtual T get(int index) = 0;
    virtual void set(int index, const T &element) = 0;
    virtual int indexOf(const T &item) = 0;
    virtual bool contains(const T &item) = 0;
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
    Node **fragmentPointers;
    int fragmentMaxSize;
    int count;

public:
    FragmentLinkedList(int fragmentMaxSize = 5)
    {
        this->count = 0;
        this->fragmentMaxSize = fragmentMaxSize;
        this->fragmentPointers = new Node *[2];
        this->fragmentPointers[0] = NULL;
        this->fragmentPointers[1] = NULL;
    }

    virtual ~FragmentLinkedList(){};

    virtual void add(const T &element);
    virtual void add(int index, const T &element);
    virtual T removeAt(int index);
    virtual bool removeItem(const T &item);
    virtual bool empty();
    virtual int size();
    virtual void clear();
    virtual T get(int index);
    virtual void set(int index, const T &element);
    virtual int indexOf(const T &item);
    virtual bool contains(const T &item);
    virtual string toString();
    Iterator begin(int index = 0)
    {
        int numfrag = (this->count - 1) / this->fragmentMaxSize + 2;
        if (index >= numfrag||index < 0 )
            throw std::out_of_range("The index is out of range!");
        else
        {
            Iterator x(index, this, true);
            return x;
        }
    };
    Iterator end(int index = -1)
    {
        Iterator x(index, this, false);
        return x;
    };
    

public:
    class Node
    {
    private:
        T data;
        Node *next;
        Node *prev;
        friend class FragmentLinkedList<T>;

    public:
        Node()
        {
            next = 0;
            prev = 0;
        }
        Node(Node *next, Node *prev)
        {
            this->next = next;
            this->prev = prev;
        }
        Node(T data, Node *next, Node *prev)
        {
            this->data = data;
            this->next = next;
            this->prev = prev;
        }
    };

    class Iterator
    {
    private:
        FragmentLinkedList<T> *pList;
        Node *pNode;
        int index;

    public:
        Iterator(FragmentLinkedList<T> *pList = 0, bool begin = true)
        {
            this->pList = pList;
            if (begin)
            {
                if (pList)
                    this->pNode = pList->fragmentPointers[0];
                else
                    this->pNode = NULL;
            }
            else
            {
                this->pNode = NULL;
                if (this->pList)
                    this->index = this->pList->count;
                else
                    this->index = 0;
            }
        };
        Iterator(int fragmentIndex, FragmentLinkedList<T> *pList = 0, bool begin = true)
        {
            if (begin == true)
            {
                this->pList = pList;
                this->index = fragmentIndex;
                this->pNode = pList->fragmentPointers[fragmentIndex];
            }
            else
            {
                this->pList = pList;
                if (fragmentIndex > -1)
                {
                    if (fragmentIndex == ((pList->count - 1) / (pList->fragmentMaxSize) + 1))
                    {
                        this->index = pList->count - 1;
                        pNode = pList->fragmentPointers[fragmentIndex];
                    }
                    else
                    {
                        this->index = fragmentIndex * pList->fragmentMaxSize;
                        int maxpos = this->index + pList->fragmentMaxSize - 1;
                        this->pNode = pList->fragmentPointers[fragmentIndex];
                        while (this->index < maxpos && this->index < pList->count - 1)
                        {
                            this->index++;
                            this->pNode = this->pNode->next;
                        }
                    }
                }
                else if (fragmentIndex == -1)
                {
                    this->index = pList->count - 1;
                    this->pNode = pList->fragmentPointers[(pList->count - 1) / (pList->fragmentMaxSize) + 1];
                }
                this->index++;
                this->pNode = this->pNode->next;
            }
        };
        Iterator &operator=(const Iterator &iterator)
        {
            this->pNode = iterator.pNode;
            this->pList = iterator.pList;
            this->index = iterator.index;
            return *this;
        };
        T &operator*()
        {
            if (this->pNode)
                return this->pNode->data;
            else
                throw std::out_of_range("Segmentation fault!");
        };
        bool operator!=(const Iterator &iterator)
        {
            if ((this->pNode == iterator.pNode) && (this->index == iterator.index))
                return false;
            else
                return true;
        };
        void remove()
        {
            pNode = pNode->prev;
            this->pList->removeAt(this->index);
            index--;
        };
        void set(const T &element)
        {
            this->pNode->data = element;
        };
        Iterator &operator++()
        {
            if (this->index < -1 || this->index > pList->count - 1)
                throw std::out_of_range("Segmentation fault!");
            else
            {
                if (this->index == -1)
                {
                    Iterator x(pList, true);
                    *this = x;
                }
                else if (index == -1)
                {
                    pNode = pList.fragmentPointers[0];
                    index++;
                }
                else
                {
                    pNode = pNode->next;
                    index++;
                }
            }
            return *this;
        };
        Iterator operator++(int)
        {
            Iterator temp = *this;
            if (this->pNode != NULL)
            {
                this->pNode = this->pNode->next;
                this->index = this->pList->count;
            }
            else
            {
                if (this->index == -1)
                {
                    this->pNode = this->pList->fragmentPointers[0];
                    this->index = this->pList->count;
                }
                else
                    throw std::out_of_range("Segmentation fault!");
            }
            return temp;
        };

    };
};
//-------------------------------------------------------------------

template <class T>
void FragmentLinkedList<T>::add(const T &element)
{
    int idxFrag = count / fragmentMaxSize;
    int idxNode = count % fragmentMaxSize;
    Node *pNew = new Node(element, NULL, NULL);
    if (count == 0)
    {
        fragmentPointers[0] = fragmentPointers[1] = pNew;
    }
    else
    {
        if (idxNode == 0)
        {
            Node **newFrag = new Node *[idxFrag + 2];
            for (int i = 0; i < idxFrag + 1; i++)
                newFrag[i] = this->fragmentPointers[i];
            newFrag[idxFrag]->next = pNew;
            pNew->prev = newFrag[idxFrag];
            newFrag[idxFrag] = newFrag[idxFrag + 1] = pNew;
            delete[] this->fragmentPointers;
            this->fragmentPointers = newFrag;
        }
        else
        {

            fragmentPointers[idxFrag + 1]->next = pNew;
            pNew->prev = fragmentPointers[idxFrag + 1];
            fragmentPointers[idxFrag + 1] = pNew;
        }
    }
    count++;
}
//-----------------------------------------------------------------------------------

template <class T>
void FragmentLinkedList<T>::add(int index, const T &element)
{
    int idxFrag = count / fragmentMaxSize;
    int idxNode = count % fragmentMaxSize;
    Node *pNew = new Node(element, NULL, fragmentPointers[1]);

    Node *p = fragmentPointers[0];
    if (index == count || count == 0)
    {
        this->add(element);
    }
    else if (index == 0)
    {
        p->prev = pNew;
        pNew->next = p;
        fragmentPointers[0] = pNew;
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

        pNew->prev = p->prev;
        (p->prev)->next = pNew;
        p->prev = pNew;
        pNew->next = p;
        count++;
    }
    if (idxNode == 0)
    {
        Node **newFrag = new Node *[idxFrag + 1];
        Node *p = fragmentPointers[0];
        newFrag[0] = p;
        int i = 0;
        while (p->next != nullptr)
        {
            p = p->next;
            i++;
            if (i % fragmentMaxSize == 0)
            {
                newFrag[i / fragmentMaxSize] = p;
            }
            if (i == count - 1)
                newFrag[idxFrag + 1] = newFrag[idxFrag];
        }
        delete[] this->fragmentPointers;
        this->fragmentPointers = newFrag;
    }
    else
    {
        int i = index / fragmentMaxSize + 1;
        int j = index % fragmentMaxSize;
        if (j == 0)
            i--;
        while (i < (idxFrag))
        {
            fragmentPointers[i] = fragmentPointers[i]->prev;
            i++;
        }
    }
};

template <class T>
T FragmentLinkedList<T>::removeAt(int index)
{
    if (index < 0 || index > this->count - 1)
        throw std::out_of_range("Segmentation fault!");
    else
    {
        T dulieu = 0;
        int idx = 0;
        if (index == 0)
        {
            if (count == 1)
            {
                dulieu = fragmentPointers[0]->data;
                this->clear();
                return dulieu;
            }
            else
            {
                dulieu = fragmentPointers[0]->data;
                Node *pDel = fragmentPointers[0];
                fragmentPointers[0] = fragmentPointers[0]->next;
                fragmentPointers[0]->prev = NULL;
                delete pDel;
            }
        }
        else
        {
            Node *p = fragmentPointers[0];
            while (idx < index)
            {
                idx++;
                p = p->next;
            }
            Node *pre = p->prev;
            dulieu = p->data;
            pre->next = p->next;
            if (p->next != NULL)
            {
                Node *nxt = pre->next;
                nxt->prev = pre;
            }
            delete p;
        }
        count--;

        idx = 0;
        int numfrag = (count - 1) / fragmentMaxSize + 2;
        Node *p = fragmentPointers[0];
        Node **newFrag = new Node *[numfrag];
        int i = 0;
        while (i < count)
        {
            if (idx % fragmentMaxSize == 0)
            {
                newFrag[idx] = p;
                idx++;
            }
            p = p->next;
            i++;
        }
        newFrag[idx] = p;
        delete[] fragmentPointers;
        fragmentPointers = newFrag;
        return dulieu;
    }
};

template <class T>
bool FragmentLinkedList<T>::removeItem(const T &item)
{
    bool kiemtra = false;
    int idx = 0;
    Node *p = fragmentPointers[0];
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
bool FragmentLinkedList<T>::empty()
{
    return !count;
}

template <class T>
int FragmentLinkedList<T>::size()
{
    return count;
};

template <class T>
void FragmentLinkedList<T>::clear()
{
    if (count > 0)
    {
        Node *p = fragmentPointers[0];
        while (p->next != NULL)
        {
            p = p->next;
            delete p->prev;
        }
        delete p;
        delete[] fragmentPointers;
        fragmentPointers = new Node *[2];
        fragmentPointers[0] = NULL;
        fragmentPointers[1] = NULL;
        count = 0;
    }
}

template <class T>
T FragmentLinkedList<T>::get(int index)
{
    int idx = 0;
    Node *p = fragmentPointers[0];
    while (idx != index)
    {
        idx++;
        p = p->next;
    }
    return p->data;
}

template <class T>
void FragmentLinkedList<T>::set(int index, const T &element)
{
    int idx = 0;
    Node *p = fragmentPointers[0];
    while (idx != index)
    {
        idx++;
        p = p->next;
    }
    p->data = element;
};

template <class T>
int FragmentLinkedList<T>::indexOf(const T &item)
{
    int idx = 0;
    Node *p = fragmentPointers[0];
    while (idx != count)
    {
        if (p->data == item)
            return idx;
        else
        {
            idx++;
            p = p->next;
        }
    }
    return -1;
};

template <class T>
bool FragmentLinkedList<T>::contains(const T &item)
{
    int idx = 0;
    Node *p = fragmentPointers[0];
    while (idx != count)
    {
        if (p->data == item)
            return true;
        else
        {
            idx++;
            p = p->next;
        }
    }
    return false;
};

template <class T>
string FragmentLinkedList<T>::toString()
{
    stringstream ss;
    ss << "[";
    if (this->count == 0)
        ss << "]";

    // TODO
    else
    {
        Node *pNew = this->fragmentPointers[0];
        ss << pNew->data;
        pNew = pNew->next;
        for (int i = 1; i < this->count; i++)
        {
            ss << ", ";
            ss << pNew->data;
            pNew = pNew->next;
        }
        ss << "]";
    }
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
    // cout << endl;
    // === END: Example
    // END: TESTCASE INPUT
    for (int i = 0; i < 10; i++)
    {
        fList.add(i);
    }
    fList.removeAt(3);
    cout << fList.toString();
    return 0;
}
