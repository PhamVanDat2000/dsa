#inclcude<iostream>

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
    void    add(T e);
    void    add(int index, T e);
    int     size();
    bool    empty();
    void    clear();
    T       get(int index);
    void    set(int index, T e);
    int     indexOf(T item);
    bool    contains(T item);
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

//==========================================
template <class T>
T SLinkedList<T>::removeAt(int index)
{
    /* Remove element at index and return removed value */
    int pos = 0;
    Node* p = head;
    T ketqua;
    if(count == 0){
    return -1;
    }
    else if (count == 1 && index==0) {
        ketqua =  head->data;
        delete head;
        delete tail;
        count--;
        return ketqua;
    }
    else {
        if (index == 0) {
            ketqua = head->data;
            head = head->next;
            delete p;
            count--;
            return ketqua;
        }
        else if (index < count){
            while (pos != (index - 1)) {
                pos++;
                p = p->next;
            }
            Node* pDel = p->next;
            ketqua = pDel->data;
            p->next = pDel->next;
            delete pDel;
            count--;
            return ketqua;
        }
    }
}
template <class T>
bool SLinkedList<T>::removeItem(const T& item) {
    /* Remove the first apperance of item in list and return true, otherwise return false */
    Node* p = head;
    if (head->data == item) {
        if (count == 1 ) {
            delete head;
            delete tail;
            count--;
            return true;
        }
        else{
            head = head->next;
            delete p;
            count--;
            return true;
        }
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