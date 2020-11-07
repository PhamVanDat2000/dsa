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
	virtual void add(const T &element) = 0;
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

	virtual ~FragmentLinkedList()
	{
		this->clear();
		delete[] fragmentPointers;
	}

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
	void indao();
	Iterator begin(int index = 0);
	Iterator end(int index = -1);

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

	public:
		Iterator(FragmentLinkedList<T> *pList = 0, bool begin = true);
		Iterator(FragmentLinkedList<T> *pList = 0, int fragmentIndex = 0, bool begin = true);
		Iterator &operator=(const Iterator &iterator);
		T &operator*();
		bool operator!=(const Iterator &iterator);
		void remove();
		void set(const T &element);
		Iterator &operator++();
		Iterator operator++(int);
	};
};
template <class T>
FragmentLinkedList<T>::Iterator::Iterator(FragmentLinkedList<T> *pList, bool begin)
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
}
template <class T>
FragmentLinkedList<T>::Iterator::Iterator(FragmentLinkedList<T> *pList = 0, int fragmentIndex = 0, bool begin = true)
{
	this->fragmentIndex = fragmentIndex;
	this->pList = pList;
	if (begin)
	{
		if (pList)
			this->pNodes = pList->fragmentPointers[0];
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
}
template <class T>
typename FragmentLinkedList<T>::Iterator &FragmentLinkedList<T>::Iterator::operator=(const Iterator &iterator)
{
	this->pNode = iterator.pNode;
	this->pList = iterator.pList;
	this->index = iterator.index;
	return *this;
}
template <class T>
T &FragmentLinkedList<T>::Iterator::operator*()
{
	if (!this->pNode)
		throw std::out_of_range("Segmentation fault!");
	else
		return this->pNode->data;
}
template <class T>
bool FragmentLinkedList<T>::Iterator::operator!=(const Iterator &iterator)
{
	if ((this->pNode == iterator.pNode) && (this->index == iterator.index))
		return false;
	else
		return true;
}
template <class T>
void FragmentLinkedList<T>::Iterator::remove()
{
	if (!this->pNode)
		throw std::out_of_range("Segmentation fault!");
	else
	{
		Node *temp = this->pList->fragmentPointers[0];
		if (temp == this->pNode)
		{
			this->pNode = NULL;
			this->index = -1;
		}
		else
		{
			while (temp->next != this->pNode)
				temp = temp->next;
			temp->next = this->pNode->next;
			this->pList->count--;
			this->index--;
			delete this->pNode;
			this->pNode = temp;
		}
	}
}
template <class T>
void FragmentLinkedList<T>::Iterator::set(const T &element)
{
	if (!this->pNode)
		throw std::out_of_range("Segmentation fault!");
	else
		this->pNode->data = element;
}
template <class T>
typename FragmentLinkedList<T>::Iterator &FragmentLinkedList<T>::Iterator::operator++()
{
	if (this->pNode == NULL)
	{
		if (this->index == -1)
		{
			this->pNode = this->pList->fragmentPointers[0];
			this->index = this->pList->count;
			return *this;
		}
		else
			throw std::out_of_range("Segmentation fault!");
	}
	else
	{
		this->pNode = this->pNode->next;
		this->index = this->pList->count;
		return *this;
	}
}
template <class T>
typename FragmentLinkedList<T>::Iterator FragmentLinkedList<T>::Iterator::operator++(int)
{
	Iterator temp = *this;
	if (this->pNode == NULL)
	{
		if (this->index == -1)
		{
			this->pNode = this->pList->fragmentPointers[0];
			this->index = this->pList->count;
		}
		else
			throw std::out_of_range("Segmentation fault!");
	}
	else
	{
		this->pNode = this->pNode->next;
		this->index = this->pList->count;
	}
	return temp;
}
//-------------------------------------------------------------------
//-------------------------------------------------------------------
//-------------------------------------------------------------------
//-------------------------------------------------------------------
//-------------------------------------------------------------------
//-------------------------------------------------------------------

template <class T>
void FragmentLinkedList<T>::add(const T &element)
{
	Node *pNew = new Node{element, NULL, NULL};
	int numfrag = this->count / this->fragmentMaxSize;
	if (this->count == 0)
	{
		this->fragmentPointers[0] = pNew;
		this->fragmentPointers[1] = pNew;
	}
	else
	{
		if (this->count % this->fragmentMaxSize != 0)
		{
			this->fragmentPointers[numfrag + 1]->next = pNew;
			pNew->prev = this->fragmentPointers[numfrag + 1];
			this->fragmentPointers[numfrag + 1] = pNew;
		}
		else if (this->count % this->fragmentMaxSize == 0)
		{
			Node **newFrag = new Node *[numfrag + 2];
			for (int i = 0; i < numfrag + 1; i++)
				newFrag[i] = this->fragmentPointers[i];
			newFrag[numfrag]->next = pNew;
			pNew->prev = newFrag[numfrag];
			newFrag[numfrag] = pNew;
			newFrag[numfrag + 1] = pNew;
			delete[] this->fragmentPointers;
			this->fragmentPointers = newFrag;
		}
	}
	this->count++;
}
//-----------------------------------------------------------------------------------

template <class T>
void FragmentLinkedList<T>::add(int index, const T &element)
{
	Node *head = new Node;
	head = this->fragmentPointers[0];
	if (index == 0)
	{
		Node *pNew = new Node;
		pNew->data = element;
		pNew->prev = NULL;
		pNew->next = head;
		head->prev = pNew;
		head = pNew;
	}
	else
	{
		Node *p = new Node;
		p = head;
		int pos = 1;
		while (pos < index && pos < this->count)
		{
			pos++;
			p = p->next;
		}
		Node *pNew = new Node;
		pNew->data = element;
		pNew->next = p->next;
		pNew->prev = p;
		p->next = pNew;
		if (index < this->count)
		{
			p = pNew->next;
			p->prev = pNew;
		}
	}
	this->count++;

	int numfrag = (this->count - 1) / this->fragmentMaxSize;
	Node **newFrag = new Node *[numfrag + 2];
	newFrag[0] = head;
	Node *p = new Node;
	p = head;
	int pos = 0;
	while (pos < this->count)
	{
		if (pos % this->fragmentMaxSize == 0)
		{
			newFrag[pos / this->fragmentMaxSize] = p;
		}
		p = p->next;
		pos++;
		if (pos == this->count - 1)
			newFrag[numfrag + 1] = p;
	}
	delete[] this->fragmentPointers;
	this->fragmentPointers = newFrag;
}
//-----------------------------------------------------------------------------------

template <class T>
T FragmentLinkedList<T>::removeAt(int index)
{
	Node *head = new Node;
	T ketqua = 0;
	head = this->fragmentPointers[0];
	if (index == 0)
	{
		ketqua = head->data;
		head = head->next;
		delete head->prev;
		head->prev = NULL;
	}
	else
	{
		int pos = 1;
		Node *p = head;
		while (pos < index && pos << this->count)
		{
			pos++;
			p = p->next;
		}
		ketqua = p->next->data;
		Node *xoa = p->next;
		p->next = xoa->next;
		if (index < this->count - 1)
		{
			p = p->next;
			p->prev = xoa->prev;
		}
		delete xoa;
	}

	this->count--;
	int numfrag = (this->count - 1) / this->fragmentMaxSize;
	Node **newFrag = new Node *[numfrag + 2];
	newFrag[0] = head;
	Node *p = new Node;
	p = head;
	int pos = 0;
	while (pos < this->count)
	{
		if (pos % this->fragmentMaxSize == 0)
		{
			newFrag[pos / this->fragmentMaxSize] = p;
		}
		p = p->next;
		pos++;
		if (pos == this->count - 1)
			newFrag[numfrag + 1] = p;
	}
	delete[] this->fragmentPointers;
	this->fragmentPointers = newFrag;
	return ketqua;
};
//-----------------------------------------------------------------------------------

template <class T>
bool FragmentLinkedList<T>::removeItem(const T &item)
{
	bool kiemtra = false;
	int findpos = 0;
	Node *pfind = this->fragmentPointers[0];
	while (findpos < this->count)
	{
		if (item == pfind->data)
		{
			kiemtra = true;
			pfind = pfind->next;
			this->removeAt(findpos);
		}
		else
		{
			findpos++;
			pfind = pfind->next;
		}
	}
	return kiemtra;
}
//-----------------------------------------------------------------------------------

template <class T>
bool FragmentLinkedList<T>::empty()
{
	if (this->count == 0)
		return true;
	else
		return false;
}
//-----------------------------------------------------------------------------------

template <class T>
int FragmentLinkedList<T>::size()
{
	return this->count;
};
//-----------------------------------------------------------------------------------

template <class T>
void FragmentLinkedList<T>::clear()
{
	Node *p = this->fragmentPointers[0];
	while (p->next != NULL)
	{
		p = p->next;
		delete p->prev;
	}
	delete p;
	delete[] this->fragmentPointers;

	this->fragmentPointers = new Node *[2];
	this->fragmentPointers[0] = NULL;
	this->fragmentPointers[1] = NULL;
	this->count = 0;
}
//-----------------------------------------------------------------------------------

template <class T>
T FragmentLinkedList<T>::get(int index)
{
	int pos = 0;
	Node *p = this->fragmentPointers[0];
	while (pos < index)
	{
		pos++;
		p = p->next;
	}
	return p->data;
}
//-----------------------------------------------------------------------------------

template <class T>
void FragmentLinkedList<T>::set(int index, const T &element)
{
	int pos = 0;
	Node *p = this->fragmentPointers[0];
	while (pos < index)
	{
		pos++;
		p = p->next;
	}
	p->data = element;
};

//-----------------------------------------------------------------------------------

int indexOf(const T &item)
{
	int pos = 0;
	Node *p = this->fragmentPointers[0];
	while (p != NULL)
	{
		if (p->data == item)
			return pos;
		pos++;
		p = p->next;
	}
	return -1;
};
//-----------------------------------------------------------------------------------
bool contains(const T &item)
{
	Node *p = this->fragmentPointers[0];
	while (p != NULL)
	{
		if (p->data == item)
			return true;
		p = p->next;
	}
	return false;
};
//-----------------------------------------------------------------------------------
template <class T>
string FragmentLinkedList<T>::toString()
{
	stringstream ss;
	ss << "[";
	Node *ptr = this->fragmentPointers[0];

	if (this->count == 0)
		ss << "]";

	// TODO
	else
	{
		int dem = 0;
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
//-----------------------------------------------------------------------------------

template <class T>
void FragmentLinkedList<T>::indao()
{
	Node *ptail = this->fragmentPointers[(this->count - 1) / this->fragmentMaxSize + 1];
	while (ptail != NULL)
	{
		cout << ptail->data << "->";
		ptail = ptail->prev;
	}
}

//---------------------------------------------------------------
#endif
// END: STUDENT ANSWER

int main()
{
	// TESTCASE INPUT
	// === Example
	FragmentLinkedList<int> fList;

	// for(FragmentLinkedList<int>::Iterator it = fList.begin(); it != fList.end(); it++)
	//     cout << *it << " ";
	// cout << endl;
	// === END: Example
	// END: TESTCASE INPUT
	fList.add(1);
	fList.add(2);
	fList.add(3);
	fList.add(4);
	fList.add(5);
	fList.add(2, 4);
	cout << fList.get(5) << endl;
	cout << fList.indexOf(3) << endl;
	cout << fList.toString();
	return 0;
}
