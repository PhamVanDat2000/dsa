#include <iostream>
#include <sstream>
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
    SLinkedList()
    {
        this->head = nullptr;
        this->tail = nullptr;
        this->count = 0;
    }
    ~SLinkedList(){};
    void add(T e)
    {
        Node *pNew = new Node(e);

        if (this->count == 0)
        {
            this->head = this->tail = pNew;
        }
        else
        {
            this->tail->next = pNew;
            this->tail = pNew;
        }

        this->count++;
    }
    int size()
    {
        return this->count;
    }
    void printList()
    {
        stringstream ss;
        ss << "[";
        Node *ptr = head;
        while (ptr != tail)
        {
            ss << ptr->data << ",";
            ptr = ptr->next;
        }

        if (count > 0)
            ss << ptr->data << "]";
        else
            ss << "]";
        cout << ss.str() << endl;
    }

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
        Node(T data)
        {
            this->data = data;
            this->next = nullptr;
        }
    };

    void bubbleSort();
};
template <class T>
void SLinkedList<T>::bubbleSort()
{
    int n = count-1;
    if (count > 1)
    {
        Node *max;
        Node *p;
        T temp;
        while (n)
        {
            max = head;
            while (max->next != NULL)
            {
                p = max->next;
                if (p->data < max->data)
                {
                    temp = max->data;
                    max->data = p->data;
                    p->data = temp;
                }
                max = max->next;
            }
            this->printList();
            n--;
        }
    }
}

//=====================main========

int main()
{
    int arr[] = {9, 2, 8, 4, 1};
    SLinkedList<int> list;
    for (int i = 0; i < int(sizeof(arr)) / 4; i++)
        list.add(arr[i]);
    list.bubbleSort();
    return 0;
}