#include<iostream>
using namespace std;
template <class T>
class SLinkedList {
public:
    class Node; // Forward declaration
protected:
    Node* head;
    Node* tail;
    int count;
public:
    SLinkedList();
    ~SLinkedList();
    void    add(const T& e);
    void    add(int index, const T& e);
    int     size();
    bool    empty();
    void    clear();
    T       get(int index);
    void    set(int index, const T& e);
    int     indexOf(const T& item);
    bool    contains(const T& item);
    T       removeAt(int index);
    bool    removeItem(const T& item);
public:
    class Node {
    private:
        T data;
        Node* next;
        friend class SLinkedList<T>;
    public:
        Node() {
            next = 0;
        }
        Node(Node* next) {
            this->next = next;
        }
        Node(T data, Node* next = NULL) {
            this->data = data;
            this->next = next;
        }
    };
};

//---------------------------

template<class T>
T SLinkedList<T>::get(int index) {
    /* Give the data of the element at given index in the list. */
    if (index >= count) {
        return tail->data;
    }
    else {
        Node* p = head;
        int pos = 0;
        while (pos != index) {
            pos++;
            p = p->next;
        }
        return p->data;
    }
}

template <class T>
void SLinkedList<T>::set(int index, const T& e) {
    /* Assign new value for element at given index in the list */
    if (index == 0) {
        head->data = e;
    }
    else if (index >= count) {
        tail->data = e;
    }
    else {
        Node* p = head->next;
        int pos = 1;
        while (pos != index) {
            pos++;
            p = p->next;
        }
        p->data = e;
    }
}

template<class T>
bool SLinkedList<T>::empty() {
    /* Check if the list is empty or not. */
    return !count;
}

template<class T>
int SLinkedList<T>::indexOf(const T& item) {
    /* Return the first index wheter item appears in list, otherwise return -1 */
    Node* p = head;
    int pos = 0;
    while (p->data != item) {
        pos++;
        p = p->next;
        if (pos >= count)
            return -1;
    }
    return pos;
}

template<class T>
bool SLinkedList<T>::contains(const T& item) {
    /* Check if item appears in the list */
    Node* p = head;
    int pos = 0;
    while (p->data != item) {
        pos++;
        p = p->next;
        if (pos >= count)
            return false;
    }
    return true;
}

template <class T>
void SLinkedList<T>::add(const T& e) {
    /* Insert an element into the end of the list. */
    Node* pNew = new Node(e, NULL);
    if (count == 0) {
        head = tail = pNew;
        count++;
    }
    else {
        tail->next = pNew;
        tail = pNew;
        count++;
    }
}

template<class T>
void SLinkedList<T>::add(int index, const T& e) {
    /* Insert an element into the list at given index. */
    Node* pNew = new Node(e, NULL);
    if (count == 0) {
        pNew->next = head;
        head = tail = pNew;
        count++;
    }
    else if (index == 0) {
        pNew->next = head;
        head = pNew;
        count++;
    }
    else if (index >= count) {
        tail->next = pNew;
        tail = pNew;
        count++;
    }
    else {
        int pos = 1;
        Node* p = head;
        while (pos < index && pos < this->count) {
            pos++;
            p = p->next;
        }
        pNew->next = p->next;
        p->next = pNew;
        count++;
    }
}

template<class T>
int SLinkedList<T>::size() {
    /* Return the length (size) of list */
    return count;
}

//++++++++++++++++++++++++++++++++++++++++++++++

template <class T>
T SLinkedList<T>::removeAt(int index)
{
    /* Remove element at index and return removed value */
    int pos = 0;
    Node* p = head;
    T ketqua;
    if (count == 1 || count == 0) {
        head->data = NULL;
        tail->data = NULL;
    }
    else {
        if (index == 0) {
            ketqua = head->data;
            head = head->next;
            delete p;
            count--;
            return ketqua;
        }
        else if (index >= (count - 1)) {
            ketqua = tail->data;
            delete tail;
            for (int i = 1; i < (count - 1); i++) {
                p = p->next;
            }
            p->next = NULL;
            tail = p;
            count--;
            return ketqua;
        }
        else {
            while (pos != (index - 1)) {
                pos++;
                p = p->next;
            }
            Node* pDel = p->next;
            ketqua = pDel->data;
            p->next = pDel->next;
            delete pDel;
            return ketqua;
        }
    }
}
template <class T>
bool SLinkedList<T>::removeItem(const T& item) {
    /* Remove the first apperance of item in list and return true, otherwise return false */
    Node* p = head;
    if (p->data == item) {
        head = head->next;
        delete p;
        count--;
        return true;
    }
    else {
        int pos = 1;
        Node* pDel = p->next;
        while (pDel->data != item && pos < count) {
            pos++;
            p = p->next;
            pDel = p->next;
        }
        if (pos >= count)
            return false;
        else {
            p->next = pDel->next;
            delete pDel;
            count--;
            return true;
        }
    }
}


template<class T>
void SLinkedList<T>::clear() {
    /* Remove all elements in list */
    while (count) {
        Node* p = head;
        head = head->next;
        delete p;
        count--;
    }
}


class Polynomial;
class Term {
private:
    double coeff;
    int exp;
    friend class Polynomial;
public:
    Term(double coeff = 0.0, int exp = 0) {
        this->coeff = coeff;
        this->exp = exp;
    }
    bool operator==(const Term& rhs) const {
        return this->coeff == rhs.coeff && this->exp == rhs.exp;
    }
    friend ostream& operator<<(ostream& os, const Term& term) {
        cout << endl;
        cout << "Term: " << "(" << term.coeff << " " << term.exp << ")";
        return os;
    }
};
class Polynomial {
private:
    SLinkedList<Term>* terms;
public:
    Polynomial() {
        this->terms = new SLinkedList<Term>();
    }
    ~Polynomial() {
        this->terms->clear();
    }
    void insertTerm(const Term& term);
    void insertTerm(double coeff, int exp);
    /*void print() {
        SLinkedList<Term>::Iterator it;
        cout << "[";
        for (it = this->terms->begin(); it != this->terms->end(); it++) {
            cout << (*it);
        }
        cout << endl << "]";
    }*/

    void print(int i) {
        cout << terms->get(i).exp << endl;
    }

};

//===============================================BAI4------------------------------

void Polynomial::insertTerm(const Term& term) {
    // STUDENT ANSWER
    int index = 0;
    while ((terms->get(index)).exp >= term.exp) {
        if (index >= terms->size()) {
            index--;
            break;
        }
        index++;
    }
    terms->add(index, term);

}
void Polynomial::insertTerm(double coeff, int exp) {
    // STUDENT ANSWER
    int index = 0;
    Term term(coeff, exp);
    while ((terms->get(index)).exp >= exp) {
        if (index >= terms->size()) {
            index--;
            break;
        }
        index++;
    }
    terms->add(index, term);
}

//-------------------------------------------------MAIN--------------------------
int main() {
    Polynomial* dathuc = new Polynomial();
    dathuc->insertTerm(1, 3);
    dathuc->insertTerm(1, 1);
    dathuc->insertTerm(1, 2);
    dathuc->insertTerm(1, 8);
    dathuc->insertTerm(1, 4);

    dathuc->print(0);
    dathuc->print(1);
    dathuc->print(2);
    dathuc->print(3);
    dathuc->print(4);





    return 0;
}