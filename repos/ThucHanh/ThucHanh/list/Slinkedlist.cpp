#include <iostream>
using namespace std;

//-------------------------

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
    SLinkedList()
    {
        this->count = 0;
        head = NULL;
        tail = NULL;
    }
    ~SLinkedList() {}
    void add(const T &e);
    void add(int index, const T &e);
    int size();
    bool empty();
    void clear();
    T get(int index);
    void set(int index, const T &e);
    int indexOf(const T &item);
    bool contains(const T &item);
    T removeAt(int index);
    bool removeItem(const T &item);

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

//---------------------------

template <class T>
T SLinkedList<T>::get(int index)
{
    /* Give the data of the element at given index in the list. */
    Node *p = head;
    if (index >= count)
    {
        return tail->data;
    }
    else
    {
        int pos = 0;
        while (pos != index)
        {
            pos++;
            p = p->next;
        }
        return p->data;
    }
    return p->data;
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

//++++++++++++++++++++++++++++++++++++++++++++++

template <class T>
T SLinkedList<T>::removeAt(int index)
{
    /* Remove element at index and return removed value */
    T dulieu = 0;
    if (count != 0)
    {
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
                delete pDel;
            }
        }
        else
        {
            Node *p = head;
            while (idx < index - 1)
            {
                idx++;
                p = p->next;
            }
            Node *pDel = p->next;
            dulieu = pDel->data;
            if (pDel->next != NULL)
            {
                p->next = pDel->next;
            }
            else
            {
                p->next = NULL;
            }
            delete pDel;
        }
    count--;
    }
    return dulieu;
}
template <class T>
bool SLinkedList<T>::removeItem(const T &item)
{
    /* Remove the first apperance of item in list and return true, otherwise return false */
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
void SLinkedList<T>::clear()
{
    /* Remove all elements in list */
    if (count != 0)
    {
        while (count)
        {
            Node *p = head;
            head = head->next;
            delete p;
            count--;
        }
    }
}

//-------------------------------------

class Polynomial;
class Term
{
private:
    double coeff;
    int exp;
    friend class Polynomial;

public:
    Term(double coeff = 0.0, int exp = 0)
    {
        this->coeff = coeff;
        this->exp = exp;
    }
    bool operator==(const Term &rhs) const
    {
        return this->coeff == rhs.coeff && this->exp == rhs.exp;
    }
    friend ostream &operator<<(ostream &os, const Term &term)
    {
        cout << endl;
        cout << "Term: "
             << "(" << term.coeff << " " << term.exp << ")";
        return os;
    }
};
class Polynomial
{
private:
    SLinkedList<Term> *terms;

public:
    Polynomial()
    {
        this->terms = new SLinkedList<Term>();
    }
    ~Polynomial()
    {
        this->terms->clear();
    }
    void insertTerm(const Term &term);
    void insertTerm(double coeff, int exp);
    /*void print() {
            SLinkedList<Term>::Iterator it;
            cout << "[";
            for (it = this->terms->begin(); it != this->terms->end(); it++) {
                cout << (*it);
            }
            cout << endl << "]";
        }*/

    void print(int i)
    {
        cout << terms->get(i).exp << endl;
    }
};
//===============================================
void Polynomial::insertTerm(const Term &term)
{
    // STUDENT ANSWER
    int index = 0;
    while ((terms->get(index)).exp >= term.exp)
    {
        if (index >= terms->size())
            break;
        index++;
    }
    terms->add(index, term);
}
void Polynomial::insertTerm(double coeff, int exp)
{
    // STUDENT ANSWER
    int index = 0;
    Term term(coeff, exp);
    while ((terms->get(index)).exp >= term.exp)
    {
        if (index >= terms->size())
            break;
        index++;
    }
    terms->add(index, term);
}

//-------------------------------------------------MAIN--------------------------
int main()
{
    SLinkedList<int> list;
    list.add(100);
    list.clear();
    cout << "[";
    for (int i = 0; i < list.size(); i++)
        cout << list.get(i) << " ";
    cout << "]";
    return 0;
}